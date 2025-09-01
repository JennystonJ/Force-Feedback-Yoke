/*
 * app.c
 *
 *  Created on: Jul 7, 2025
 *      Author: Jennyston
 */

#include "app.h"
#include "bsp.h"

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "utilities/utilities.h"
#include "pid_tuner.h"
#include "motor.h"
#include "encoder.h"
#include "config.h"
#include "force_feedback/force_feedback_controller.h"
#include "force_feedback_config.h"
#include "delay.h"

#include <usb_device.h>
#include "usb_report.h"
#include <usbd_customhid.h>

#include "ffb_hid.h"

#define HID_PITCH 0
#define HID_ROLL 1

bool appInitialized = false;
bool appRunning = false;

extern USBD_HandleTypeDef hUsbDeviceFS;
uint8_t reportTxBuffer[5];
uint8_t txBuffer[64];
uint8_t report_buffer_rx[64];
uint8_t flag_rx = 0;
uint32_t usbPacketCount = 0;

UsbReport_t usbReport;

void ProcessFFBHid(FFBHid_t *hid);
void ProcessUsbControlData(UsbReport_t *usbReport);
void ProcessUsbFFBData(UsbReport_t *usbReport);


// Private function prototypes

static void ProcessFFBHidForce(FFBHid_t *hid);
static void ProcessFFBHidControl(FFBHid_t *hid);
static void ProcessFFBHidDataUpdate(FFBHid_t *hid);

static void MotorControlCallback(Motor_t *motor, Encoder_t *encoder,
		int adcId, float deltaTimeMs);
static void FFBControlCallback(float deltaTimeMs);

static void SerialDAQTxCallback(SerialDAQ_t *serialDaq);
static void SerialDAQRxCallback(SerialDAQ_t *serialDaq);

static void LoadCellUpdateCallback(void);

static void SetMotorSetPoint(float setPoint);
static float GetMotorActual(void);
static float GetMotorPower(void);

// Private variables
static FFBController_t pitchFFB;
static FFBController_t rollFFB;

static FFBHid_t ffbHid;

void Application_Init(void) {
	appInitialized = false;
	appRunning = false;

	UsbReportInit(&usbReport, USB_REPORT_IN_LITTLE_ENDIAN);

	Bsp_RegisterMotorControlLoopITCallback(&MotorControlCallback);
	Bsp_RegisterSerialDAQTxCallback(&SerialDAQTxCallback);
	Bsp_RegisterSerialDAQRxCallback(&SerialDAQRxCallback);
	Bsp_RegisterFFBControlLoopITCallback(&FFBControlCallback);
	Bsp_RegisterLoadCellReadCpltCallback(&LoadCellUpdateCallback);

	// Pitch motor velocity setup
	Motor_InitVelocityEncoder(&pitchMotor, &pitchEncoder);
	Motor_SetVelocityLoopFreqDivider(&pitchMotor,
			MOTOR_PITCH_VELOCITY_LOOP_FREQ_DIV);
	Motor_SetVelocityFilterAlpha(&pitchMotor, MOTOR_PITCH_VELOCITY_LPF_ALPHA);
	PID_t *pitchVelPid = Motor_GetVelocityPID(&pitchMotor);
	PID_SetGains(pitchVelPid, MOTOR_PITCH_VELOCITY_KP, MOTOR_PITCH_VELOCITY_KI,
			MOTOR_PITCH_VELOCITY_KD);
	PID_SetIntegralLimit(pitchVelPid, MOTOR_PITCH_VELOCITY_INTEGRAL_LIMIT);
	PID_SetIntegralEpsilon(pitchVelPid, MOTOR_PITCH_VELOCITY_EPSILON);

	// Roll motor velocity setup
	Motor_InitVelocityEncoder(&rollMotor, &rollEncoder);
	Motor_SetVelocityLoopFreqDivider(&rollMotor,
			MOTOR_ROLL_VELOCITY_LOOP_FREQ_DIV);
	Motor_SetVelocityFilterAlpha(&rollMotor, MOTOR_ROLL_VELOCITY_LPF_ALPHA);
	PID_t *rollVelPid = Motor_GetVelocityPID(&rollMotor);
	PID_SetGains(rollVelPid, MOTOR_ROLL_VELOCITY_KP, MOTOR_ROLL_VELOCITY_KI,
			MOTOR_ROLL_VELOCITY_KD);
	PID_SetIntegralLimit(rollVelPid, MOTOR_ROLL_VELOCITY_INTEGRAL_LIMIT);
	PID_SetIntegralEpsilon(rollVelPid, MOTOR_ROLL_VELOCITY_EPSILON);

	//Load Cell setup
	LoadCell_SetLowPassAlpha(&pitchLoadCell, LOAD_CELL_LPF_ALPHA);

	// Pitch FFB setup
	FFBInit(&pitchFFB, &pitchMotor, &pitchEncoder);
	FFB_SetAxisReverse(&rollFFB, false);
	FFBSetLoadCell(&pitchFFB, &pitchLoadCell);
	FFB_SetUnitPerRevConstant(&pitchFFB, PITCH_MM_PER_REV);
	FFB_SetLockGains(&rollFFB, FFB_PITCH_LOCK_KP, FFB_PITCH_LOCK_KD);
	FFBForces_t pitchHomeCenterForces = {
			.constantForce = 0.0f,
			.springForce = FFB_PITCH_HOME_SPRING,
			.damperForce = FFB_PITCH_HOME_DAMPER
	};
	FFB_SetHomeCenterForces(&pitchFFB, pitchHomeCenterForces);

	// Pitch FFB Assist setup
	FFBAssist_t *pitchFFBAssist = FFB_GetFFBAssist(&pitchFFB);
	FFBAssist_SetGain(pitchFFBAssist, FFB_ASSIST_GAIN);
	FFBAssist_SetAccelerationGain(pitchFFBAssist, FFB_ASSIST_ACCEL_GAIN);
	FFBAssist_SetVelocityGain(pitchFFBAssist, FFB_ASSIST_VELOCITY_GAIN);
	FFBAssist_SetVelocitySmallCompensation(pitchFFBAssist,
			FFB_ASSIST_VELOCITY_SMALL_COMP);

	// Roll FFB setup
	FFBInit(&rollFFB, &rollMotor, &rollEncoder);
	FFB_SetAxisReverse(&rollFFB, true);
	FFB_SetUnitPerRevConstant(&rollFFB, ROLL_DEGREE_PER_REV);
	FFB_SetLockGains(&rollFFB, FFB_ROLL_LOCK_KP, FFB_ROLL_LOCK_KD);
	FFBForces_t rollHomeCenterForces = {
			.constantForce = 0.0f,
			.springForce = FFB_ROLL_HOME_SPRING,
			.damperForce = FFB_ROLL_HOME_DAMPER
	};
	FFB_SetHomeCenterForces(&rollFFB, rollHomeCenterForces);

	// Electrical angle offset
	BLDCMotor_SetElectricalAngleOffsetCount(&pitchBLDCMotor,
			PITCH_ELECTRICAL_ANGLE_OFFSET);
	BLDCMotor_SetElectricalAngleOffsetCount(&rollBLDCMotor,
			ROLL_ELECTRICAL_ANGLE_OFFSET);

	PIDTuner_Init(&daq, FOC_GetIdPID(BLDCMotor_GetFOC(&pitchBLDCMotor)), &SetMotorSetPoint,
			&GetMotorActual, &GetMotorPower);

	// Initialize FFB HID
	FFBHid_Init(&ffbHid, &hUsbDeviceFS);
	// Register call backs
	FFBHid_RegisterForceReceivedCallback(&ffbHid,
			&ProcessFFBHidForce);
	FFBHid_RegisterControlReceivedCallback(&ffbHid,
			&ProcessFFBHidControl);
	FFBHid_RegisterUpdateCallback(&ffbHid,
			&ProcessFFBHidDataUpdate);

	// Set control data known values
	FFBHid_SetAxisMaxForce(&ffbHid, HID_PITCH, PITCH_MOTOR_CURRENT_LIMIT);
	FFBHid_SetMaxSupportedForces(&ffbHid, FFB_CONTROL_NUM_FORCES);

	appInitialized = true;
}

void Application_Run(void) {
	if(!appInitialized) {
		return;
	}

	appRunning = true;

	BLDCMotor_SetEnable(&pitchBLDCMotor, true);
	BLDCMotor_SetEnable(&rollBLDCMotor, true);

	delayMs(250);
	BLDCMotor_RunCurrentSensorCalibration(&pitchBLDCMotor, 512);
	delayMs(250);
	BLDCMotor_RunCurrentSensorCalibration(&rollBLDCMotor, 512);
	delayMs(250);

	LoadCell_RunCalibration(&pitchLoadCell, 512);

	PIDTuner_Start(&daq);

	delayMs(1000);

	Motor_SetCurrentLimit(&pitchMotor, PITCH_MOTOR_CURRENT_LIMIT);
	Motor_SetEnable(&pitchMotor, true);

	Motor_SetCurrentLimit(&rollMotor, ROLL_MOTOR_CURRENT_LIMIT);
	Motor_SetEnable(&rollMotor, true);

	FFBHome(&pitchFFB);
	FFBHome(&rollFFB);

	FFBHid_SetAxisTravelLimit(&ffbHid, HID_PITCH,
			FFBGetTravelRangeInUnit(&pitchFFB));
	FFBHid_SetAxisTravelLimit(&ffbHid, HID_ROLL,
			FFBGetTravelRangeInUnit(&rollFFB));
	FFBHid_EnableCapabilities(&ffbHid);

	FFBStart(&pitchFFB);
	FFBSetAssistEnable(&pitchFFB, true);

	FFBStart(&rollFFB);

	GPIOSetState(&statusLedGpio, GPIO_HIGH);

	while(true) {
		ProcessFFBHid(&ffbHid);
		FFBHid_Update(&ffbHid);
		delayMs(1);
	}
}

void ProcessFFBHid(FFBHid_t *hid) {

	// Prepare pitch axis
	int pitchAxisCountConstrained = Constrain(FFB_GetRawAxisCount(
			&pitchFFB),
			FFBGetMinControlRange(&pitchFFB),
			FFBGetMaxControlRange(&pitchFFB));

	// Map pitch values to pitch control range
	int16_t pitchAxis = (int16_t)Map(pitchAxisCountConstrained,
			FFBGetMinControlRange(&pitchFFB),
			FFBGetMaxControlRange(&pitchFFB),
			-32767, 32767);

	// Prepare roll axis
	int rollAxisCountConstrained = Constrain(FFB_GetRawAxisCount(
			&rollFFB),
			FFBGetMinControlRange(&rollFFB),
			FFBGetMaxControlRange(&rollFFB));

	// Map pitch values to pitch control range
	int16_t rollAxis = (int16_t)Map(rollAxisCountConstrained,
			FFBGetMinControlRange(&rollFFB),
			FFBGetMaxControlRange(&rollFFB),
			-32767, 32767);

//	float rollAngle = ROLL_DEGREE_PER_REV *
//			Encoder_GetCount(&rollEncoder)/65536.0f;
//	float rollAngleConstrained = ConstrainFloat(rollAngle, -90.0f, 90.0f);
////		int rollEncoderCountConstrained = Constrain(EncoderGetCount(
////				&rollEncoder),
////				FFBGetMinControlRange(&ffbRoll),
////				FFBGetMaxControlRange(&ffbRoll));


	// Prepare pitch force output
	int16_t scaledPitchForce = Constrain((int32_t)( 32767.0f *
			(Motor_GetCurrent(&pitchMotor)/PITCH_MOTOR_CURRENT_LIMIT)),
			-32767, 32767);

	int16_t scaledRollForce = Constrain((int32_t)(32767.0f *
			(Motor_GetCurrent(&rollMotor)/ROLL_MOTOR_CURRENT_LIMIT)),
			-32767, 32767);

	FFBHid_SetAxis(hid, HID_PITCH, pitchAxis);
	FFBHid_SetAxis(hid, HID_ROLL, rollAxis);
	FFBHid_SetForceOutput(&ffbHid, HID_PITCH, scaledPitchForce);
	FFBHid_SetForceOutput(&ffbHid, HID_ROLL, scaledRollForce);


}

//void ProcessUSBPacket(void) {
//
//	if(flag_rx == 1){
//
//		flag_rx = 0;
//
//		UsbReportLoad(&usbReport, report_buffer_rx,
//				USBD_CUSTOMHID_OUTREPORT_BUF_SIZE);
//		// Determine report ID and call appropriate function
//		switch(UsbReportGetReportId(&usbReport)) {
//		case 0x01:
//			ProcessUsbControlData(&usbReport);
//			break;
//		case 0x02:
//			ProcessUsbFFBData(&usbReport);
//			break;
//		default:
//			// Invalid reportID
//			break;
//		}
//
//		// Prepare aileron axis
//		float rollAngle = ROLL_DEGREE_PER_REV *
//				Encoder_GetCount(&rollEncoder)/65536.0f;
//		float rollAngleConstrained = ConstrainFloat(rollAngle, -90.0f, 90.0f);
////		int rollEncoderCountConstrained = Constrain(EncoderGetCount(
////				&rollEncoder),
////				FFBGetMinControlRange(&ffbRoll),
////				FFBGetMaxControlRange(&ffbRoll));
//
//		// Map roll values to roll control range
//		int16_t aileron = (int16_t)Map(rollAngleConstrained,
//				-90.0f,
//				90.0f,
//				-32767, 32767);
//
//		// Prepare elevator axis
//		int pitchEncoderCountConstrained = Constrain(Encoder_GetCount(
//				&pitchEncoder),
//				FFBGetMinControlRange(&pitchFFB),
//				FFBGetMaxControlRange(&pitchFFB));
//
//		// Map pitch values to pitch control range
//		int16_t elevator = (int16_t)Map(pitchEncoderCountConstrained,
//				FFBGetMinControlRange(&pitchFFB),
//				FFBGetMaxControlRange(&pitchFFB),
//				-32767, 32767);
//
//		// Prepare USB packet
//		// Set report ID to 1 (Data)
//		reportTxBuffer[0] = 0x01;
//		reportTxBuffer[1] = aileron >> 8;
//		reportTxBuffer[2] = aileron & 0xFF;
//		reportTxBuffer[3] = elevator >> 8;
//		reportTxBuffer[4] = elevator & 0xFF;
//
//		USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, reportTxBuffer, 5);
//
//		usbPacketCount++;
//	}
//
//}

void ProcessUsbControlData(UsbReport_t *usbReport) {
	// Parse USB report fields
	bool ffbOn = UsbReportParseNextByte(usbReport) == 0x01 ? true : false;
	int aileronRangeInDeg = UsbReportParseNextInt(usbReport);
	int elevatorRangeInMM = UsbReportParseNextInt(usbReport);

	// FFB ON/OFF
	if(ffbOn) {
		//FFBStart(&ffbRoll);
		FFBStart(&pitchFFB);
	}
	else {
		//FFBStop(&ffbRoll);
		FFBStop(&pitchFFB);
	}

	/** FFB Control Ranges **/

	// Aileron encoder range
//	int aileronEncoderRange = aileronRangeInDeg *
//			PULLEY_AILERON_ENCODER_STEP_PER_DEGREE;
//	FFBSetControlRange(&ffbRoll, -aileronEncoderRange/2, aileronEncoderRange/2);

	// Elevator encoder range
	int elevatorEncoderRange = elevatorRangeInMM * PITCH_STEP_PER_MM;
	FFBSetControlRange(&pitchFFB, -elevatorEncoderRange/2,
			elevatorEncoderRange/2);

}

//void ProcessUsbFFBData(UsbReport_t *usbReport) {
//	// Parse USB report fields
//	float rollForce = UsbReportParseNextFloat(usbReport);
//	float pitchForce = UsbReportParseNextFloat(usbReport);
//
//	// Assign forces
////	FFBSetConstantStrength(&ffbRoll, rollForce);
//	FFBSetConstant(&pitchFFB, pitchForce);
//}

// Private functions

static void ProcessFFBHidForce(FFBHid_t *hid) {
	FFBSetForces(&pitchFFB, FFBHid_GetForceData(hid, HID_PITCH));
	FFBSetForces(&rollFFB, FFBHid_GetForceData(&ffbHid, HID_ROLL));
}

static void ProcessFFBHidControl(FFBHid_t *hid) {

	if(FFBHid_GetFFBEnable(hid)) {
		FFBStart(&pitchFFB);
		FFBStart(&rollFFB);
	}
	else {
		FFBStop(&pitchFFB);
		FFBStop(&rollFFB);
	}

	TravelMinMax_t pitchTravel = FFBHid_GetAxisTravel(hid, HID_PITCH);
	FFBSetControlRange(&pitchFFB, pitchTravel.min * PITCH_STEP_PER_MM,
			pitchTravel.max * PITCH_STEP_PER_MM);

	TravelMinMax_t rollTravel = FFBHid_GetAxisTravel(hid, HID_ROLL);
	FFBSetControlRange(&rollFFB, rollTravel.min * ROLL_STEP_PER_DEGREE,
			rollTravel.max * ROLL_STEP_PER_DEGREE);
}

static void ProcessFFBHidDataUpdate(FFBHid_t *hid) {
	// Prepare elevator axis
	int pitchEncoderCountConstrained = Constrain(Encoder_GetCount(
			&pitchEncoder),
			FFBGetMinControlRange(&pitchFFB),
			FFBGetMaxControlRange(&pitchFFB));

	// Map pitch values to pitch control range
	int16_t pitchAxis = (int16_t)Map(pitchEncoderCountConstrained,
			FFBGetMinControlRange(&pitchFFB),
			FFBGetMaxControlRange(&pitchFFB),
			-32767, 32767);

	// Prepare aileron axis
//	float rollAngle = ROLL_DEGREE_PER_REV *
//			Encoder_GetCount(&rollEncoder)/65536.0f;
//	float rollAngleConstrained = ConstrainFloat(rollAngle, -90.0f, 90.0f);
//		int rollEncoderCountConstrained = Constrain(EncoderGetCount(
//				&rollEncoder),
//				FFBGetMinControlRange(&ffbRoll),
//				FFBGetMaxControlRange(&ffbRoll));

	// Map roll values to roll control range
//	int16_t rollAxis = (int16_t)Map(rollAngleConstrained,
//			-90.0f,
//			90.0f,
//			-32767, 32767);

	int rollAxisCountConstrained = Constrain(FFB_GetRawAxisCount(&rollFFB),
			FFBGetMinControlRange(&rollFFB),
			FFBGetMaxControlRange(&rollFFB));

	int16_t rollAxis = (int16_t)Map(rollAxisCountConstrained,
			FFBGetMinControlRange(&rollFFB),
			FFBGetMaxControlRange(&rollFFB),
			-32767, 32767);

	FFBHid_SetAxis(hid, HID_PITCH, pitchAxis);
	FFBHid_SetAxis(hid, HID_ROLL, rollAxis);
}

static void MotorControlCallback(Motor_t *motor, Encoder_t *encoder, int adcId,
		float deltaTimeMs) {
	if(!appRunning) {
		return;
	}

//	GPIOSetState(&probeGpio, GPIO_HIGH);

	Bsp_ADCUpdate(adcId);
	Encoder_Update(encoder, deltaTimeMs);
	Motor_Update(motor, deltaTimeMs);

//	GPIOSetState(&probeGpio, GPIO_LOW);
}

// *** Serial data acquisition functions ***
static void SerialDAQTxCallback(SerialDAQ_t *serialDaq) {
	if(!appRunning) {
		return;
	}
}

static void SerialDAQRxCallback(SerialDAQ_t *serialDaq) {
	if(!appRunning) {
		return;
	}

	SerialDAQ_Update(serialDaq);
}

static void FFBControlCallback(float deltaTimeMs) {
	if(!appRunning) {
		return;
	}

	FFBUpdate(&pitchFFB, deltaTimeMs);
	FFBUpdate(&rollFFB, deltaTimeMs);
}

static void LoadCellUpdateCallback(void) {
	LoadCell_Update(&pitchLoadCell);
}


// *** PID Tuner Callbacks ***
static void SetMotorSetPoint(float setPoint) {
//	Motor_SetCurrent(&pitchMotor, setPoint);
	BLDCMotor_SetQCurrent(&pitchBLDCMotor, setPoint);
}

static float GetMotorActual(void) {
//	return Motor_GetMeasuredCurrent(&pitchMotor, 0);
	return BLDCMotor_GetQCurrentReading(&pitchBLDCMotor);
}

static float GetMotorPower(void) {
	return Motor_GetCurrent(&pitchMotor);
	return 0;
}
