/*
 * bsp.c
 *
 *  Created on: Jul 13, 2024
 *      Author: Jennyston
 */

#include "bsp.h"
#include "main.h"
#include "app.h"

#include "devices/as5048a.h"
#include "devices/as5048a_interface.h"
#include "devices/as5600.h"
#include "devices/as5600_interface.h"

#include "devices/bts7960.h"
#include "devices/bts7960_interface.h"
//#include "devices/bts7960_current_sensor.h"
//#include "peripherals/internal_adc.h"
//#include "peripherals/internal_adc_interface.h"
#include "devices/ads1256.h"
#include "devices/ads1256_interface.h"
#include "peripherals/internal_adc.h"
#include "peripherals/internal_adc_interface.h"
#include "current_sensor.h"
#include <string.h>
#include <stddef.h>
#include <stdio.h>

// External variables
Encoder_t pitchEncoder;
Encoder_t rollEncoder;

Motor_t pitchMotor;
Motor_t rollMotor;

GPIO_t gpioAccept;
GPIO_t gpioStatus;

LoadCell_t pitchLoadCell;

// External debug variables
float pidTunerSetPoint;
bool pidTunerUpdateFlag = false;
int pidTunerSyncLostCount;

// Private variables
AS5048A_t pitchAS5048A;
AS5600_t rollAS5600;

BTS7960_t pitchDriver;
BTS7960_t rollDriver;

//BTS7960CurrentSensor_t pitchCurrentSensor;

ADS1256_t pitchADS1256;

InternalADC_t internalADC;
AnalogSensor_t analogSensor;
AnalogSensor_t pitchAnalogCurrentSensor;

CurrentSensor_t pitchCurrentSensor;

bool bspInitialized;

bool pitchEncoderUpdateFlag;

int tickCounter;
// PID Tuner variables
uint8_t uartRxDmaBuffer[17];
uint8_t uartTxDmaBuffer[sizeof(uint8_t) + sizeof(int) + sizeof(float)*2];

// TODO: Remove, debug code
float motorCurrentReading = 0;
float motorFCurrentReading = 0;
float motorRCurrentReading = 0;

float loadCellReading = 0;

// Private function prototypes
void SetupMotors(void);
void SetupCurrentSensors(void);
void SetupLoadCells(void);
void SetupEncoders(void);
void SetupButtons(void);
void SetupLEDs(void);

void HandleADCError(ADS1256_t *device);
void HandleEncoderError(AS5600_t *device);
void HandleSPIEncoderError(AS5048A_t *device);

void StartPIDTuner(void);

void BspInit(void) {

	tickCounter = 0;
	pidTunerSetPoint = 0;

	bspInitialized = false;

	HAL_Delay(1);

	SetupCurrentSensors();
	SetupMotors();
	SetupLoadCells();
	SetupEncoders();
	SetupButtons();
	SetupLEDs();

	// --- Timer setup ----
	// Internal ADC trigger timer
	HAL_TIM_OC_Start(&htim1, TIM_CHANNEL_1);
	// Motor PWM timer
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
	// Update timer
	HAL_TIM_Base_Start_IT(&htim10);
	// Fast control loop timer
	HAL_TIM_Base_Start_IT(&htim11);
	//BTS7960CurrentSensorCalibrate(&pitchCurrentSensor);
	HAL_ADC_Start_IT(&hadc1);
	//MotorSetPower(&pitchMotor, -1000);
	bspInitialized = true;
	//Calibrate load cell and current sensor
	HAL_Delay(500);
	for(int i = 0; i < 100; i++) {
		LoadCellUpdate(&pitchLoadCell);
		LoadCellGetValue(&pitchLoadCell);
		HAL_Delay(1);
	}
	LoadCellSetOffset(&pitchLoadCell, -LoadCellGetValue(&pitchLoadCell));
//	CurrentSensorSetOffset(&pitchCurrentSensor,
//			-CurrentSensorGetValue(&pitchCurrentSensor));
//	while(1) {
//		loadCellReading = LoadCellGetValue(&pitchLoadCell);
////		motorFCurrentReading =
////				BTS7960CurrentSensorReadForward(&pitchCurrentSensor);
////		motorRCurrentReading =
////				BTS7960CurrentSensorReadReverse(&pitchCurrentSensor);
////		motorCurrentReading = BTS7960CurrentSensorRead(&pitchCurrentSensor);
////		if(GPIOGetState(&gpioAccept) == GPIO_LOW) {
////			MotorSetPower(&pitchMotor, 0);
////		}
////		else {
////			MotorSetPower(&pitchMotor, -1000);
////		}
//	}

	StartPIDTuner();
}

void BspSetEStop(bool eStop) {
	BTS7960SetDriverEStop(&pitchDriver, eStop);
	BTS7960SetDriverEStop(&rollDriver, eStop);

	// Indicate e stop activated
	GPIOSetState(&gpioStatus, GPIO_LOW);
}

void StartPIDTuner(void) {
	pidTunerSyncLostCount = 0;
	HAL_UART_Receive_DMA(&huart1, uartRxDmaBuffer, sizeof(uartRxDmaBuffer));

}

void BspDumpCogData(float *cogMap, int cogMapLength, const char *title) {
	printf("%s\r\n", title);
	for(int i = 0; i < cogMapLength; i++) {
		printf("%f,\r\n", cogMap[i]);
	}

	printf("\r\n%s\r\n", "Done!");
}

void BspUpdatePIDTuner(float actual, float data, PID_t *pid) {

	uint8_t *bufferAddr = uartRxDmaBuffer;

	if(*bufferAddr == 0x55) {
		pidTunerSyncLostCount = 0;

		bufferAddr += sizeof(uint8_t);
		pidTunerSetPoint = *(float *)bufferAddr;

		if(pid != NULL) {
			bufferAddr += sizeof(float);
			float gain = *(float *)bufferAddr;
			PIDSetKP(pid, gain);

			bufferAddr += sizeof(float);
			gain = *(float *)bufferAddr;
			PIDSetKI(pid, gain);

			bufferAddr += sizeof(float);
			gain = *(float *)bufferAddr;
			PIDSetKD(pid, gain);
		}

		float bufferTx[] = {actual, data};

		memcpy(uartTxDmaBuffer+sizeof(uint8_t)+sizeof(uint32_t), bufferTx,
				sizeof(bufferTx));

	}
	else {
		memset(uartTxDmaBuffer, 0, sizeof(uartTxDmaBuffer));
		pidTunerSyncLostCount++;
		if(pidTunerSyncLostCount > 10)
		{
			PIDSetKP(pid, 0);
			PIDSetKI(pid, 0);
			PIDSetKD(pid, 0);

			BTS7960SetDriverEStop(&pitchDriver, true);
		}
	}

	// Sync
	*uartTxDmaBuffer = 0x55;

	uint32_t systick_value = SysTick->VAL;
	memcpy(uartTxDmaBuffer+sizeof(uint8_t), &systick_value, sizeof(systick_value));

	HAL_UART_Transmit_DMA(&huart1, uartTxDmaBuffer, sizeof(uartTxDmaBuffer));
}

void BspUARTRxUpdate(UART_HandleTypeDef *huart) {
	if(huart == &huart1) {
		pidTunerUpdateFlag = true;
	}
}

void BspUARTTxUpdate(UART_HandleTypeDef *huart) {
	if(huart == &huart1) {
		HAL_UART_Receive_DMA(huart, uartRxDmaBuffer, sizeof(uartRxDmaBuffer));
	}
}

void BspADCUpdate(ADC_HandleTypeDef *hadc) {
	if(hadc == &hadc1) {
//		InternalADCUpdateIT(&internalADC);
		InternalADCStartDMA(&internalADC);
		CurrentSensorCalibrationUpdate(&pitchCurrentSensor);
		MotorCurrentCalibrationUpdate(&pitchMotor);
	}
}

void BspEXTIUpdate(uint16_t GPIO_Pin) {
	if(!bspInitialized) {
		return;
	}

	if(GPIO_Pin == ADC_DRDY_Pin) {
//		ADS1256StartDMA(&pitchADS1256);
		ADS1256StartDMA(&pitchADS1256);
	}
}

void BspSPIITUpdate(SPI_HandleTypeDef *hspi) {
	if(hspi == &hspi1) {
		pitchEncoderUpdateFlag = true;
	}
	else if(hspi == &hspi2) {
		ADS1256Update(&pitchADS1256);
	}
}

void BspTIMITUpdate(TIM_HandleTypeDef *htim) {
	if(htim == &htim11) {
		ApplicationHighPriorityUpdate(100);
	}
	else if(htim == &htim10) {
		ApplicationProcessWatchDog();
		ApplicationSetFastUpdateFlag(1000);
		tickCounter++;
		if(tickCounter == 5) {
			ApplicationSetUpdateFlag(5000);
			tickCounter = 0;
		}
	}
}

void BspUpdateDeviceData() {
	CurrentSensorUpdate(&pitchCurrentSensor);
}

void SetupEncoders(void) {
	// Pitch
	GPIO_t pitchEncNCS;
	GPIOInit(&pitchEncNCS, nCS1_1_GPIO_Port, nCS1_1_Pin);
	AS5048AInit(&pitchAS5048A, &hspi1, pitchEncNCS);
	AS5048ARegisterErrorCallback(&pitchAS5048A, HandleSPIEncoderError);
	EncoderInterface_t pitchEncoderI;
	AS5048AInterfaceInit(&pitchEncoderI, &pitchAS5048A);
	EncoderInit(&pitchEncoder, pitchEncoderI);
	pitchEncoderUpdateFlag = false;
//	// Roll
//	AS5600Init(&rollAS5600, &hi2c3);
//	AS5600RegisterErrorCallback(&rollAS5600, HandleEncoderError);
//	EncoderInterface_t rollEncoderI;
//	AS5600InterfaceInit(&rollEncoderI, &rollAS5600);
//	EncoderInit(&rollEncoder, rollEncoderI);
}

void SetupMotors(void) {
	// Pitch
	// Initialize driver
	//BTS7960InitPowerBrake(&pitchDriver, &htim3,
	//	TIM_PITCH_F_CH, TIM_PITCH_R_CH);
	GPIO_t pitchEn;
	GPIOInit(&pitchEn, MOTOR_PITCH_EN_GPIO_Port, MOTOR_PITCH_EN_Pin);
	BTS7960InitEn(&pitchDriver, &htim3, TIM_PITCH_F_CH, TIM_PITCH_R_CH, pitchEn);

	// Set up interface
	MotorInterface_t pitchMotorI;
	BTS7960InterfaceInit(&pitchMotorI, &pitchDriver);

	// Initialize motor
	MotorInit(&pitchMotor, pitchMotorI);
	MotorSetCurrentSensor(&pitchMotor, &pitchCurrentSensor);

	// Enable motor
	BTS7960SetDriverEStop(&pitchDriver, false);

	// Roll
	// Initialize driver
	GPIO_t rollEn;
	GPIOInit(&rollEn, MOTOR_ROLL_EN_GPIO_Port, MOTOR_ROLL_EN_Pin);
	BTS7960InitEn(&rollDriver, &htim3, TIM_ROLL_F_CH, TIM_ROLL_R_CH, rollEn);

	// Set up interface
	MotorInterface_t rollMotorI;
	BTS7960InterfaceInit(&rollMotorI, &rollDriver);

	// Initialize motor
	MotorInit(&rollMotor, rollMotorI);

	// Enable motor
	BTS7960SetDriverEStop(&rollDriver, false);
}

void SetupCurrentSensors(void) {
//	BTS7960CurrentSensorInit(&pitchCurrentSensor, &hadc1, ADC_PITCH_F_RANK,
//			ADC_PITCH_R_RANK, &pitchDriver);
//	//BTS7960CurrentSensorSetConvConstants(&pitchCurrentSensor, 0.26/10, 0.15/33);
//	BTS7960CurrentSensorSetConvConstants(&pitchCurrentSensor, 1, 1);
//	BTS7960CurrentSensorStart(&pitchCurrentSensor);

	// Initialize internal ADC
	InternalADCInit(&internalADC, &hadc1);

	// Set up interface
	AnalogSensorInterface_t analogSensorI;
	InternalADCInterfaceInit(&analogSensorI, &internalADC);

	AnalogSensorInit(&pitchAnalogCurrentSensor, analogSensorI);

	// Initialize current sensor
	CurrentSensorInit(&pitchCurrentSensor, &pitchAnalogCurrentSensor,
			ADC_PITCH_CURRENT_SENSOR_CHANNEL);
	CurrentSensorSetOffset(&pitchCurrentSensor, 2180.71045f);
	// Start internal ADC
//	InternalADCStartIT(&internalADC);
	InternalADCStartDMA(&internalADC);
}

void SetupLoadCells(void) {

	// Initialize ADC
	GPIO_t nCS, nDRdy;
	GPIOInit(&nCS, ADC_CS_GPIO_Port, ADC_CS_Pin);
	GPIOInit(&nDRdy, ADC_DRDY_GPIO_Port, ADC_DRDY_Pin);

	ADS1256Init(&pitchADS1256, &hspi2, nCS, nDRdy);
	ADS1256RegisterErrorCallback(&pitchADS1256, HandleADCError);
	ADS1256StartReading(&pitchADS1256);

	// Set up interface
	AnalogSensorInterface_t analogSensorI;
	ADS1256InterfaceInit(&analogSensorI, &pitchADS1256);

	AnalogSensorInit(&analogSensor, analogSensorI);

	//----------------------------------------------------------

//	// Initialize ADC
//	InternalADCInit(&adc, &hadc1);
//	InternalADCStartDMA(&adc);
//
//	// Set up interface
//	AnalogSensorInterface_t analogSensorI;
//	InternalADCInterfaceInit(&analogSensorI, &adc);
//
//	AnalogSensorInit(&analogSensor, analogSensorI);

	// Pitch
	LoadCellInit(&pitchLoadCell, &analogSensor, ADC_PITCH_LOAD_CELL_CHANNEL);

}

void SetupButtons(void) {
	GPIOInit(&gpioAccept, BUTTON_ACCEPT_GPIO_Port, BUTTON_ACCEPT_Pin);
}

void SetupLEDs(void) {
	GPIOInit(&gpioStatus, STATUS_LED_GPIO_Port, STATUS_LED_Pin);
}

void HandleADCError(ADS1256_t *device) {
	if(device == &pitchADS1256) {
		BTS7960SetDriverEStop(&pitchDriver, true);
	}

	// Indicate error
	GPIOSetState(&gpioStatus, GPIO_LOW);
}

void HandleSPIEncoderError(AS5048A_t *device) {
	if(device == &pitchAS5048A) {
		BTS7960SetDriverEStop(&pitchDriver, true);
	}

	// Indicate error
	GPIOSetState(&gpioStatus, GPIO_LOW);
}

void HandleEncoderError(AS5600_t *device) {
//	if(device == &pitchAS5600) {
//		BTS7960SetDriverEStop(&pitchDriver, true);
//	}
//	else
	if(device == &rollAS5600) {
		BTS7960SetDriverEStop(&rollDriver, true);
	}

	// Indicate error
	GPIOSetState(&gpioStatus, GPIO_LOW);
}
