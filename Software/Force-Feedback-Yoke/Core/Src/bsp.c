/*
 * bsp.c
 *
 *  Created on: Jul 4, 2025
 *      Author: Jennyston
 */

#include "bsp.h"
#include "config.h"

#include "delay.h"
#include "delay_us.h"

#include "devices/drv8301.h"
#include "devices/drv8301_interface.h"

#include "devices/mt6835.h"
#include "devices/mt6835_interface.h"

#include "devices/ads1256.h"
#include "devices/ads1256_interface.h"

#include "peripherals/internal_injected_adc.h"
#include "peripherals/internal_injected_adc_interface.h"

#include "analog_sensor.h"

#include "bldc_motor.h"
#include "bldc_motor_interface.h"

#include "motor.h"

#include <stm32h7xx_hal.h>
#include <string.h>



// Private variables
static MT6835_t pitchMt6835;
static MT6835_t rollMt6835;

static InternalInjectedADC_t pitchCurrentSensorADC;
static ADS1256_t adsADC;

static AnalogSensor_t pitchCurrentChA;
static AnalogSensor_t pitchCurrentChB;
static AnalogSensor_t pitchCurrentChC;

static AnalogSensor_t pitchLoadCellCh;

static DRV8301_t pitchDrv8301;

static struct {
	void (*MotorControlLoopIT)(Motor_t *motor, Encoder_t *encoder,
			float deltaTimeMs);
	void (*SerialDAQTxIT)(SerialDAQ_t *serialDaq);
	void (*SerialDAQRxIT)(SerialDAQ_t *serialDaq);
	void (*FFBControlLoopIT)(float deltaTimeMs);
	void (*LoadCellReadCpltIT)(void);
} callbacks;

// Debug variables

// Variables to be exported
bool bspInitialized = false;
uint8_t serialTxBuffer[SERIAL_TX_BUFFER_SIZE];
uint8_t serialRxBuffer[SERIAL_RX_BUFFER_SIZE];

CurrentSensor_t pitchCurrentA;
CurrentSensor_t pitchCurrentB;
CurrentSensor_t pitchCurrentC;

BLDCDriver_t pitchDriver;
BLDCMotor_t pitchBLDCMotor;
Motor_t pitchMotor;
Encoder_t pitchEncoder;
LoadCell_t pitchLoadCell;

Encoder_t rollEncoder;

GPIO_t statusLedGpio;
GPIO_t probeGpio;
GPIO_t eStopGpio;



SerialDAQ_t daq;

// Forward function prototypes
static void Bsp_EStopInit(void);
static void Bsp_DelayInit(void);
static void Bsp_ProbeInit(void);
static void Bsp_LedInit(void);
static void Bsp_EncodersInit(void);
static void Bsp_CurrentSensorsInit(void);
static void Bsp_MotorsInit(void);
static void Bsp_LoadCellInit(void);
static void Bsp_StartADCs(void);
static void Bsp_StartTimers(void);
static void Bsp_DaqInit(void);

static int pitchEncoderSPIAngle;
static int pitchEncoderAngle;

void Bsp_Init(void) {
	memset(&callbacks, 0, sizeof(callbacks));

	Bsp_EStopInit();
	Bsp_ProbeInit();

	Bsp_DelayInit();

	Bsp_LedInit();
	Bsp_EncodersInit();
	Bsp_CurrentSensorsInit();
	Bsp_MotorsInit();
	Bsp_LoadCellInit();

	Bsp_DaqInit();

	Bsp_StartADCs();
	Bsp_StartTimers();

//	while(true) {
//		pitchEncoderSPIAngle = MT6835_ReadAngle(&pitchMt6835) >> 5;
//		pitchEncoderAngle = Encoder_GetHardCount(&pitchEncoder);
//	}

	bspInitialized = true;
}

void Bsp_EStopIT(void) {
	if(GPIOGetState(&eStopGpio) == GPIO_LOW) {
		// E-Stop is enabled, disarm motors, and turn off status LED
		BLDCMotor_SetEStop(&pitchBLDCMotor, true);
		GPIOSetState(&statusLedGpio, GPIO_HIGH);
	}
	else {
		//E-Stop is disabled, arm motors, and turn on status LED
		BLDCMotor_SetEStop(&pitchBLDCMotor, false);
		GPIOSetState(&statusLedGpio, GPIO_LOW);
	}
}

void Bsp_MotorControlLoopIT(Motor_t *motor, Encoder_t *encoder,
		float deltaTimeMs) {
	if(pitchDrv8301.dutyU == 1.0f || pitchDrv8301.dutyV == 1.0f ||
			pitchDrv8301.dutyW == 1.0f) {
		//__BKPT(255);
	}
	if(callbacks.MotorControlLoopIT != NULL) {
		callbacks.MotorControlLoopIT(motor, encoder, deltaTimeMs);
	}
}

void Bsp_FFBControlLoopIT(float deltaTimeMs) {
	if(callbacks.FFBControlLoopIT != NULL) {
		callbacks.FFBControlLoopIT(deltaTimeMs);
	}
}

void Bsp_SerialDAQTxIT(void) {
	if(callbacks.SerialDAQTxIT != NULL) {
		callbacks.SerialDAQTxIT(&daq);
	}
}

void Bsp_SerialDAQRxIT(void) {
	if(callbacks.SerialDAQRxIT != NULL) {
		callbacks.SerialDAQRxIT(&daq);
	}
}

void Bsp_ADCWatchDogIT(ADC_HandleTypeDef *hadc) {
	// Motor over-current or current sense error detected
	// Disable motors
	Motor_SetEnable(&pitchMotor, false);
	// Turn status LED on to indicate error
	GPIOSetState(&statusLedGpio, GPIO_LOW);

}

void Bsp_ADS1256DrdyUpdate(uint16_t pin) {
	if(!bspInitialized) {
		return;
	}

	if(pin == ADC1_DRDY_Pin) {
		ADS1256_StartDMA(&adsADC);
	}
}

void Bsp_ADS1256Update(void) {
	ADS1256_Update(&adsADC);
	if(callbacks.LoadCellReadCpltIT != NULL) {
		callbacks.LoadCellReadCpltIT();
	}
}

void Bsp_RegisterMotorControlLoopITCallback(void (*MotorControlLoopIT)
		(Motor_t *motor, Encoder_t *encoder, float deltaTimeMs)) {
	callbacks.MotorControlLoopIT = MotorControlLoopIT;
}

void Bsp_RegisterFFBControlLoopITCallback(void (*FFBControlLoopIT)
		(float deltaTimeMs)) {
	callbacks.FFBControlLoopIT = FFBControlLoopIT;
}

void Bsp_RegisterSerialDAQTxCallback(void (*SerialDAQTxIT)
		(SerialDAQ_t *serialDaq)) {
	callbacks.SerialDAQTxIT = SerialDAQTxIT;
}

void Bsp_RegisterSerialDAQRxCallback(void (*SerialDAQRxIT)
		(SerialDAQ_t *serialDaq)) {
	callbacks.SerialDAQRxIT = SerialDAQRxIT;
}

void Bsp_RegisterLoadCellReadCpltCallback(void (*LoadCellReadCpltIT)) {
	callbacks.LoadCellReadCpltIT = LoadCellReadCpltIT;
}

// Private functions

static void Bsp_EStopInit(void) {
	GPIOInit(&eStopGpio, E_STOP_GPIO_Port, E_STOP_Pin);
}

static void Bsp_DelayInit(void) {
	DelayUs_Init(&US_TIM);
	delayUsInit(&DelayUs_Delay);
	delayMsInit(&HAL_Delay);
}

static void Bsp_ProbeInit(void) {
	GPIOInit(&probeGpio, PROBE_OUT_GPIO_Port, PROBE_OUT_Pin);
	GPIOSetState(&probeGpio, GPIO_LOW);
}

static void Bsp_LedInit(void) {
	GPIOInit(&statusLedGpio, STATUS_LED_GPIO_Port, STATUS_LED_Pin);
}

static void Bsp_EncodersInit(void) {

	// Set up nCS pin for pitch encoder
	GPIO_t gpioPitchNcs;
	GPIOInit(&gpioPitchNcs, E1_NCS_GPIO_Port, E1_NCS_Pin);

	// Initialize pitch encoder
	MT6835_Init(&pitchMt6835, &ENCODER_PITCH_SPI, gpioPitchNcs);
	MT6835_SetABTim(&pitchMt6835, &ENCODER_PITCH_TIM);

	EncoderInterface_t pitchEncoderI;
	MT6835Interface_Init(&pitchEncoderI, &pitchMt6835);

	Encoder_Init(&pitchEncoder, pitchEncoderI);
	Encoder_SetCountPerRev(&pitchEncoder, ENCODER_PITCH_COUNTS_PER_REV);
	Encoder_SetReverse(&pitchEncoder, false);

	// Initialize roll encoder
	GPIO_t gpioRollNcs;
	GPIOInit(&gpioRollNcs, E2_NCS_GPIO_Port, E2_NCS_Pin);

	// Initialize roll encoder
	MT6835_Init(&rollMt6835, &ENCODER_ROLL_SPI, gpioRollNcs);
	MT6835_SetABTim(&rollMt6835, &ENCODER_ROLL_TIM);

	EncoderInterface_t rollEncoderI;
	MT6835Interface_Init(&rollEncoderI, &rollMt6835);

	Encoder_Init(&rollEncoder, rollEncoderI);
	Encoder_SetCountPerRev(&rollEncoder, ENCODER_ROLL_COUNTS_PER_REV);
	Encoder_SetReverse(&rollEncoder, true);
}

static void Bsp_CurrentSensorsInit(void) {

	// Set up pitch current sensors
	InternalInjectedADC_Init(&pitchCurrentSensorADC, &CURRENT_SENSE_PITCH_ADC,
			CURRENT_SENSE_PITCH_ADC_VREF);

	// Pitch current sensor ADC
	ADCInterface_t adcI;
	InternalInjectedADCInterface_Init(&adcI, &pitchCurrentSensorADC);

	// Current sensor A
	AnalogSensor_Init(&pitchCurrentChA, adcI, CURRENT_SENSE_PITCH_A_CH,
			CURRENT_SENSE_PITCH_ADC_COUNTS-1);
	AnalogSensor_SetDifferential(&pitchCurrentChA, CURRENT_SENSE_PITCH_REF_CH);
	CurrentSensor_Init(&pitchCurrentA, &pitchCurrentChA,
			CURRENT_SENSE_PITCH_MAX_CURRENT);
	CurrentSensor_SetLowPassAlpha(&pitchCurrentA,
			CURRENT_SENSE_PITCH_LPF_ALPHA);

	// Current sensor B
	AnalogSensor_Init(&pitchCurrentChB, adcI, CURRENT_SENSE_PITCH_B_CH,
			CURRENT_SENSE_PITCH_ADC_COUNTS-1);
	AnalogSensor_SetDifferential(&pitchCurrentChB, CURRENT_SENSE_PITCH_REF_CH);
	CurrentSensor_Init(&pitchCurrentB, &pitchCurrentChB,
			CURRENT_SENSE_PITCH_MAX_CURRENT);
	CurrentSensor_SetLowPassAlpha(&pitchCurrentB,
			CURRENT_SENSE_PITCH_LPF_ALPHA);

	// Current sensor C
	AnalogSensor_Init(&pitchCurrentChC, adcI, CURRENT_SENSE_PITCH_C_CH,
			CURRENT_SENSE_PITCH_ADC_COUNTS-1);
	AnalogSensor_SetDifferential(&pitchCurrentChC, CURRENT_SENSE_PITCH_REF_CH);
	CurrentSensor_Init(&pitchCurrentC, &pitchCurrentChC,
			CURRENT_SENSE_PITCH_MAX_CURRENT);
	CurrentSensor_SetLowPassAlpha(&pitchCurrentC,
			CURRENT_SENSE_PITCH_LPF_ALPHA);

	// TODO: Set up roll current sensors
}

static void Bsp_MotorsInit(void) {

	// Initialize pitch driver
	// Set up driver enable pin for pitch driver
	GPIO_t gpioDriverEn;
	GPIOInit(&gpioDriverEn, M1_DRIVER_EN_GPIO_Port, M1_DRIVER_EN_Pin);

	DRV8301_Init(&pitchDrv8301, gpioDriverEn, &DRIVER_PITCH_TIM,
			DRIVER_PITCH_PHASE_U_CHANNEL,
			DRIVER_PITCH_PHASE_V_CHANNEL,
			DRIVER_PITCH_PHASE_W_CHANNEL, DRIVER_PITCH_BUS_VOLTAGE);

	BLDCDriverInterface_t bldcDriverI;
	DRV8301Interface_Init(&bldcDriverI, &pitchDrv8301);

	BLDCDriver_Init(&pitchDriver, bldcDriverI);

	// Initialize pitch motor and assign current sensors
	BLDCMotor_Init(&pitchBLDCMotor, &pitchDriver, &pitchEncoder,
			MOTOR_PITCH_POLE_PAIRS);
	BLDCMotor_SetCurrentSensors(&pitchBLDCMotor, &pitchCurrentA,
			&pitchCurrentB, &pitchCurrentC);
	BLDCMotor_SetTorqueConstant(&pitchBLDCMotor, MOTOR_PITCH_KT);

	// Set pitch motor PID parameters
	FOC_t *pitchFoc = BLDCMotor_GetFOC(&pitchBLDCMotor);
	PID_SetGains(FOC_GetIdPID(pitchFoc), MOTOR_PITCH_ID_KP, MOTOR_PITCH_ID_KI,
			MOTOR_PITCH_ID_KD);
	PID_SetIntegralLimit(FOC_GetIdPID(pitchFoc), MOTOR_PITCH_ID_INTEGRAL_LIMIT);

	PID_SetGains(FOC_GetIqPID(pitchFoc), MOTOR_PITCH_IQ_KP, MOTOR_PITCH_IQ_KI,
			MOTOR_PITCH_IQ_KD);
	PID_SetIntegralLimit(FOC_GetIqPID(pitchFoc), MOTOR_PITCH_IQ_INTEGRAL_LIMIT);

	MotorInterface_t pitchMotorI;
	BLDCMotorInterface_Init(&pitchMotorI, &pitchBLDCMotor);

	Motor_Init(&pitchMotor, pitchMotorI);
	// TODO: Initialize roll driver
}

static void Bsp_LoadCellInit(void) {
	// ADC1 pin setup
	GPIO_t nCS, nDRdy;
	GPIOInit(&nCS, ADC1_NCS_GPIO_Port, ADC1_NCS_Pin);
	GPIOInit(&nDRdy, ADC1_DRDY_GPIO_Port, ADC1_DRDY_Pin);

	ADS1256_Init(&adsADC, &ADS1256_SPI, nCS, nDRdy);
	ADS1256_StartReading(&adsADC);

	// Set up interface
	ADCInterface_t adcI;
	ADS1256InterfaceInit(&adcI, &adsADC);

	AnalogSensor_Init(&pitchLoadCellCh, adcI, 0, ADS1256_ADC_COUNTS);

	LoadCell_Init(&pitchLoadCell, &pitchLoadCellCh);
}

static void Bsp_DaqInit(void) {
	SerialDAQ_Init(&daq, &huart2);
}

static void Bsp_StartADCs(void) {
	InternalInjectedADC_StartIT(&pitchCurrentSensorADC);
	// TODO: Start roll current sensor ADC
}

static void Bsp_StartTimers(void) {
	// Microsecond Timer
	HAL_TIM_Base_Stop(&US_TIM);

	// Motor Driver Timers
	// Freeze timers when paused during debug for safety
	__HAL_DBGMCU_FREEZE_TIM1();
	__HAL_DBGMCU_FREEZE_TIM8();

	HAL_TIM_Base_Start(&DRIVER_PITCH_TIM);

	HAL_TIM_PWM_Start(&DRIVER_PITCH_TIM, DRIVER_PITCH_PHASE_U_CHANNEL);
	HAL_TIMEx_PWMN_Start(&DRIVER_PITCH_TIM, DRIVER_PITCH_PHASE_U_CHANNEL);

	HAL_TIM_PWM_Start(&DRIVER_PITCH_TIM, DRIVER_PITCH_PHASE_V_CHANNEL);
	HAL_TIMEx_PWMN_Start(&DRIVER_PITCH_TIM, DRIVER_PITCH_PHASE_V_CHANNEL);

	HAL_TIM_PWM_Start(&DRIVER_PITCH_TIM, DRIVER_PITCH_PHASE_W_CHANNEL);
	HAL_TIMEx_PWMN_Start(&DRIVER_PITCH_TIM, DRIVER_PITCH_PHASE_W_CHANNEL);

	HAL_TIM_OC_Start_IT(&DRIVER_PITCH_TIM, DRIVER_PITCH_OC_ADC_SYNC_CHANNEL);

	// TODO: Start roll driver timer and PWM channels

	// Encoder Timers
	HAL_TIM_Encoder_Start(&ENCODER_PITCH_TIM, TIM_CHANNEL_1);
	HAL_TIM_Encoder_Start(&ENCODER_PITCH_TIM, TIM_CHANNEL_2);

	HAL_TIM_Encoder_Start(&ENCODER_ROLL_TIM, TIM_CHANNEL_1);
	HAL_TIM_Encoder_Start(&ENCODER_ROLL_TIM, TIM_CHANNEL_2);

	// FFB Control Loop Timer
	HAL_TIM_Base_Start_IT(&FFB_CONTROL_LOOP_TIM);
}

void Bsp_ADCUpdate(void) {
	InternalInjectedADC_UpdateIT(&pitchCurrentSensorADC);
}


uint32_t Bsp_GetTick(void) {
	return HAL_GetTick();
}
