/*
 * app.c
 *
 *  Created on: Jul 7, 2025
 *      Author: Jennyston
 */

#include <config/config.h>
#include <config/force_feedback_config.h>
#include <control/ffb_axis.h>
#include "calibration/calibration.h"
#include "config/calibration_config.h"
#include "app.h"
#include "bsp.h"

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "utilities/utilities.h"
#include "pid_tuner.h"
#include "motor.h"
#include "encoder.h"
#include "force_feedback/force_feedback_controller.h"
#include "delay.h"

#include <usb_device.h>
#include "usb_report.h"
#include <usbd_customhid.h>

#include "ffb_hid.h"

#include "log.h"
#include "diagnostics/diagnostics.h"
#include "diagnostics/diagnostics_config.h"

#include "peripherals/dwt.h"


#define HID_PITCH 0
#define HID_ROLL 1

bool appInitialized = false;
bool appRunning = false;

uint8_t ffbUpdateFlag = 0;

extern USBD_HandleTypeDef hUsbDeviceFS;
uint8_t reportTxBuffer[5];
uint8_t txBuffer[64];
uint8_t report_buffer_rx[64];
uint8_t flag_rx = 0;
uint32_t usbPacketCount = 0;

UsbReport_t usbReport;

static Calibration_t pitchCal;

void ProcessFFBHid(FFBHid_t *hid, int hidAxisId, FFBAxis_t *axis);
void ProcessUsbControlData(UsbReport_t *usbReport);
void ProcessUsbFFBData(UsbReport_t *usbReport);


// Private function prototypes

static void ProcessFFBHidForce(FFBHid_t *hid);
static void ProcessFFBHidControl(FFBHid_t *hid);
static void ProcessFFBHidDataUpdate(FFBHid_t *hid);

static void MotorControlCallback(Motor_t *motor, Encoder_t *encoder,
		int id, float deltaTimeMs);
static void FFBControlCallback(float deltaTimeMs);

static void SerialDAQTxCallback(SerialDAQ_t *serialDaq);
static void SerialDAQRxCallback(SerialDAQ_t *serialDaq);

static void LoadCellUpdateCallback(void);

static void SetMotorSetPoint(float setPoint);
static float GetMotorActual(void);
static float GetMotorPower(void);

// Private variables
static FFBAxis_t pitchAxis;
static FFBAxis_t rollAxis;

static FFBHid_t ffbHid;

static float pidSetPoint = 0.0f;

static uint32_t maxDwtCycles = 0;
static float elapsedTime = 0.0f;

void Application_Init(void) {

	Diagnostics_Init(&diagConfig);

	appInitialized = false;
	appRunning = false;

	UsbReportInit(&usbReport, USB_REPORT_IN_LITTLE_ENDIAN);

	Bsp_RegisterMotorControlLoopITCallback(&MotorControlCallback);
	Bsp_RegisterSerialDAQTxCallback(&SerialDAQTxCallback);
	Bsp_RegisterSerialDAQRxCallback(&SerialDAQRxCallback);
	Bsp_RegisterFFBControlLoopITCallback(&FFBControlCallback);
	Bsp_RegisterLoadCellReadCpltCallback(&LoadCellUpdateCallback);


	FFBAxis_Init(&pitchAxis, &pitchConfig);
	FFBAxis_Init(&rollAxis, &rollConfig);


	// Pitch motor velocity setup
//	Motor_InitVelocityEncoder(&pitchMotor, &pitchEncoder);
//	Motor_SetVelocityLoopFreqDivider(&pitchMotor,
//			MOTOR_PITCH_VELOCITY_LOOP_FREQ_DIV);
//	Motor_SetVelocityFilterAlpha(&pitchMotor, MOTOR_PITCH_VELOCITY_LPF_ALPHA);
//	PID_t *pitchVelPid = Motor_GetVelocityPID(&pitchMotor);
//	PID_SetGains(pitchVelPid, VELOCITY_CONTROL_PITCH_KP, VELOCITY_CONTROL_PITCH_KI,
//			VELOCITY_CONTROL_PITCH_KD);
//	PID_SetIntegralLimit(pitchVelPid, VELOCITY_CONTROL_PITCH_INTEGRAL_LIMIT);
//	PID_SetIntegralEpsilon(pitchVelPid, VELOCITY_CONTROL_PITCH_EPSILON);

	// Roll motor velocity setup
//	Motor_InitVelocityEncoder(&rollMotor, &rollEncoder);
//	Motor_SetVelocityLoopFreqDivider(&rollMotor,
//			MOTOR_ROLL_VELOCITY_LOOP_FREQ_DIV);
//	Motor_SetVelocityFilterAlpha(&rollMotor, MOTOR_ROLL_VELOCITY_LPF_ALPHA);
//	PID_t *rollVelPid = Motor_GetVelocityPID(&rollMotor);
//	PID_SetGains(rollVelPid, VELOCITY_CONTROL_ROLL_KP, VELOCITY_CONTROL_ROLL_KI,
//			VELOCITY_CONTROL_ROLL_KD);
//	PID_SetIntegralLimit(rollVelPid, VELOCITY_CONTROL_ROLL_INTEGRAL_LIMIT);
//	PID_SetIntegralEpsilon(rollVelPid, VELOCITY_CONTROL_ROLL_EPSILON);

	//Load Cell setup
//	LoadCell_SetLowPassAlpha(&pitchLoadCell, LOAD_CELL_LPF_ALPHA);

	// Pitch FFB setup
//	FFB_Init(&pitchFFB, &pitchMotor, &pitchEncoder);
//	FFB_SetAxisReverse(&pitchFFB, false);
//	FFB_SetLoadCell(&pitchFFB, &pitchLoadCell);
//	FFB_SetUnitPerRevConstant(&pitchFFB, PITCH_MM_PER_REV);
//	FFB_SetLockGains(&pitchFFB, FFB_PITCH_LOCK_KP, FFB_PITCH_LOCK_KD);
//	FFBForces_t pitchHomeCenterForces = {
//			.constantForce = 0.0f,
//			.springForce = FFB_PITCH_HOME_SPRING,
//			.damperForce = FFB_PITCH_HOME_DAMPER
//	};
//	FFB_SetHomeCenterForces(&pitchFFB, pitchHomeCenterForces);
//	FFB_SetUnitPerNmConstant(&pitchFFB, PITCH_YOKE_FORCE_PER_MOTOR_TORQUE);

	// Pitch FFB Assist setup
//	FFBAssist_t *pitchFFBAssist = FFB_GetFFBAssist(&pitchFFB);
//	FFBAssist_SetGain(pitchFFBAssist, FFB_ASSIST_GAIN);
//	FFBAssist_SetAccelerationGain(pitchFFBAssist, FFB_ASSIST_ACCEL_GAIN);
//	FFBAssist_SetVelocityGain(pitchFFBAssist, FFB_ASSIST_VELOCITY_GAIN);
//	FFBAssist_SetVelocitySmallCompensation(pitchFFBAssist,
//			FFB_ASSIST_VELOCITY_SMALL_COMP);

	// Roll FFB setup
//	FFB_Init(&rollFFB, &rollMotor, &rollEncoder);
//	FFB_SetAxisReverse(&rollFFB, true);
//	FFB_SetUnitPerRevConstant(&rollFFB, ROLL_DEGREE_PER_REV);
//	FFB_SetLockGains(&rollFFB, FFB_ROLL_LOCK_KP, FFB_ROLL_LOCK_KD);
//	FFBForces_t rollHomeCenterForces = {
//			.constantForce = 0.0f,
//			.springForce = FFB_ROLL_HOME_SPRING,
//			.damperForce = FFB_ROLL_HOME_DAMPER
//	};
//	FFB_SetHomeCenterForces(&rollFFB, rollHomeCenterForces);
//	FFB_SetUnitPerNmConstant(&rollFFB, ROLL_YOKE_TORQUE_PER_MOTOR_TORQUE);

//	// Electrical angle offset
//	BLDCMotor_SetElectricalAngleOffsetCount(&pitchBLDCMotor,
//			PITCH_ELECTRICAL_ANGLE_OFFSET);
//	BLDCMotor_SetElectricalAngleOffsetCount(&rollBLDCMotor,
//			ROLL_ELECTRICAL_ANGLE_OFFSET);

//	PIDTuner_Init(&daq, FOC_GetIdPID(BLDCMotor_GetFOC(&pitchBLDCMotor)), &SetMotorSetPoint,
//			&GetMotorActual, &GetMotorPower);

#if PID_TUNING_MODE
	// Prevent stopper from interfering with tuning
	AxisLimits_SetStopperEnable(FFBAxis_GetAxisLimits(&pitchAxis), false);

	PIDTuner_Init(&daq, VelocityControl_GetVelocityPID(&pitchAxis.velControl),
			&SetMotorSetPoint, &GetMotorActual, &GetMotorPower);
	PIDTuner_Start(&daq);
#endif

	// Initialize FFB HID
	FFBHid_Init(&ffbHid, &hUsbDeviceFS);
	// Register call backs
	FFBHid_RegisterForceReceivedCallback(&ffbHid,
			&ProcessFFBHidForce);
	FFBHid_RegisterControlReceivedCallback(&ffbHid,
			&ProcessFFBHidControl);
	FFBHid_RegisterUpdateCallback(&ffbHid,
			&ProcessFFBHidDataUpdate);

	// Set capability data
	FFBHid_SetAxisMaxForce(&ffbHid, HID_PITCH,
			AxisGeometry_MotorTorqueToYokeEffort(&pitchAxis.geom,
					FFBAxis_GetSafeMaxTorque(&pitchAxis)));

	FFBHid_SetAxisMaxForce(&ffbHid, HID_ROLL,
			AxisGeometry_MotorTorqueToYokeEffort(&rollAxis.geom,
					FFBAxis_GetSafeMaxTorque(&rollAxis)));

	appInitialized = true;

	// Calibration
	FFBAxis_StartCalibration(&pitchAxis);
	FFBAxis_StartCalibration(&rollAxis);

	while(!(FFBAxis_IsCalibrationDone(&pitchAxis) &&
			FFBAxis_IsCalibrationDone(&rollAxis))) {
		// Wait for calibration to complete, do nothing
	}

#if !PID_TUNING_MODE
	// Homing

	FFBAxis_StartHoming(&pitchAxis);
	FFBAxis_StartHoming(&rollAxis);

	while(!(FFBAxis_IsHomingDone(&pitchAxis) && FFBAxis_IsHomingDone(&rollAxis))) {
			// Wait for homing to complete, do nothing
	}


//	while(1) {
//		Diagnostics_Process();
//		delayMs(1);
//	}

//	static Calibration_t pitchCal;
/*
	Calibration_Init(&pitchCal, &pitchAxis, &pitchCalConfig);
	Calibration_Start(&pitchCal);

	while(Calibration_IsRunning(&pitchCal)) {
		while(ffbUpdateFlag == 0) { }
		ffbUpdateFlag = 0;

		Calibration_Update(&pitchCal, 1/1000.0f);
	}*/

/*

	// Set default pitch operating range
	AxisLimits_t *pitchLimits = FFBAxis_GetAxisLimits(&pitchAxis);
	AxisLimits_SetOperatingPositionRange(pitchLimits, (AxisRange_t) {
		.min = AxisGeometry_PosToRad(&pitchAxis.geom,
				AXIS_PITCH_DEFAULT_OPERATING_LIMIT_MM_MIN),
		.max = AxisGeometry_PosToRad(&pitchAxis.geom,
				AXIS_PITCH_DEFAULT_OPERATING_LIMIT_MM_MAX),
	});

	// Set default roll operating range
	AxisLimits_t *rollLimits = FFBAxis_GetAxisLimits(&rollAxis);
	AxisLimits_SetOperatingPositionRange(rollLimits, (AxisRange_t) {
		.min = AxisGeometry_PosToRad(&rollAxis.geom,
				AXIS_ROLL_DEFAULT_OPERATING_LIMIT_DEG_MIN),
		.max = AxisGeometry_PosToRad(&rollAxis.geom,
				AXIS_ROLL_DEFAULT_OPERATING_LIMIT_DEG_MAX),
	});
*/
#endif
}

void Application_Run(void) {
	if(!appInitialized) {
		return;
	}

	appRunning = true;

//	PIDTuner_Start(&daq);

	delayMs(1000);
/*
	Motor_SetTorqueLimit(&pitchMotor, PITCH_MOTOR_TORQUE_LIMIT);
	Motor_SetEnable(&pitchMotor, true);

	Motor_SetTorqueLimit(&rollMotor, ROLL_MOTOR_TORQUE_LIMIT);
	Motor_SetEnable(&rollMotor, true);

	FFB_Home(&pitchFFB);
	FFB_Home(&rollFFB);
*/
//	Motor_SetEnable(&pitchMotor, true);

	/*FFBAssistCal_t pitchFFBAssistCal;
	FFBAssistCal_Init(&pitchFFBAssistCal, &pitchFFB);
	FFBAssistCal_RunStaticCalibration(&pitchFFBAssistCal);
	while(true) {}*/

//	FFBHid_SetAxisTravelLimit(&ffbHid, HID_PITCH,
//			FFB_GetTravelRangeInUnit(&pitchFFB));
//	FFBHid_SetAxisTravelLimit(&ffbHid, HID_ROLL,
//			FFB_GetTravelRangeInUnit(&rollFFB));
//	FFBHid_EnableCapabilities(&ffbHid);
#if !PID_TUNING_MODE
	AxisRange_t pitchRange = FFBAxis_GetSafeAxisPositionRange(&pitchAxis);
	FFBHid_SetAxisTravelLimit(&ffbHid, HID_PITCH, pitchRange.max -
			pitchRange.min);
	AxisRange_t rollRange = FFBAxis_GetSafeAxisPositionRange(&rollAxis);
	FFBHid_SetAxisTravelLimit(&ffbHid, HID_ROLL, rollRange.max -
			rollRange.min);
	FFBHid_EnableCapabilities(&ffbHid);

//	FFB_Start(&pitchFFB);
//	FFB_SetAssistEnable(&pitchFFB, true);

//	FFB_Start(&rollFFB);

	bool success = FFBAxis_SetFFBOn(&pitchAxis) == FFB_AXIS_STATUS_OK &&
			FFBAxis_SetFFBOn(&rollAxis) == FFB_AXIS_STATUS_OK;

	if(success) {
		GPIO_SetState(&statusLedGpio, GPIO_HIGH);
	}
	else {
		FFBAxis_SetFFBOff(&pitchAxis);
		FFBAxis_SetFFBOff(&rollAxis);

		__BKPT(0xFF);
		while(true) {
			// Fault, do nothing
		}
	}

	while(true) {
		ProcessFFBHid(&ffbHid, HID_PITCH, &pitchAxis);
		ProcessFFBHid(&ffbHid, HID_ROLL, &rollAxis);
		FFBHid_Update(&ffbHid);
//		Diagnostics_Process();
		delayMs(1);
	}
#else
	while(true) {
		delayMs(1);
	}
#endif
}

void ProcessFFBHid(FFBHid_t *hid, int hidAxisId, FFBAxis_t *axis) {

	const AxisKinematics_t *kinematics = FFBAxis_GetAxisKinematics(axis);

	// Convert position to 16-bit integer
	AxisLimits_t *limits = FFBAxis_GetAxisLimits(axis);
	AxisRange_t operatingRange = AxisLimits_GetOperatingPositionRange(limits);

	// Clamp position to axis limits
	float axisPosConstrained = ConstrainFloat(kinematics->position,
			operatingRange.min, operatingRange.max);

	// Map position to 16-bit integer
	int16_t axisPos16 = (int16_t)MapFloat(axisPosConstrained,
			operatingRange.min, operatingRange.max, -32767, 32767);

	// Convert motor torque to 16-bit integer
	float normalizedTorque = kinematics->motorTorque /
			AxisLimits_GetSafetyMaxTorque(limits);
	int16_t torque16 = (int16_t)Constrain(32767.0f * normalizedTorque,
			-32767, 32767);

	// Set HID parameters
	FFBHid_SetAxis(hid, hidAxisId, axisPos16);
	FFBHid_SetForceOutput(&ffbHid, hidAxisId, torque16);

/*
	// Prepare pitch axis
	int pitchAxisCountConstrained = Constrain(FFB_GetRawAxisCount(
			&pitchFFB),
			FFB_GetMinControlRange(&pitchFFB),
			FFB_GetMaxControlRange(&pitchFFB));

	// Map pitch values to pitch control range
	int16_t pitchAxis = (int16_t)Map(pitchAxisCountConstrained,
			FFB_GetMinControlRange(&pitchFFB),
			FFB_GetMaxControlRange(&pitchFFB),
			-32767, 32767);

	// Prepare roll axis
	int rollAxisCountConstrained = Constrain(FFB_GetRawAxisCount(
			&rollFFB),
			FFB_GetMinControlRange(&rollFFB),
			FFB_GetMaxControlRange(&rollFFB));

	// Map roll values to roll control range
	int16_t rollAxis = (int16_t)Map(rollAxisCountConstrained,
			FFB_GetMinControlRange(&rollFFB),
			FFB_GetMaxControlRange(&rollFFB),
			-32767, 32767);

	int16_t scaledPitchForce = Constrain((int32_t)(32767.0f *
			(FFB_GetFeedback(&pitchFFB)/FFB_ConvertMotorTorqueToFFBUnits
					(&pitchFFB, PITCH_MOTOR_TORQUE_LIMIT))),
					-32767, 32767);

	int16_t scaledRollForce = Constrain((int32_t)(32767.0f *
			(FFB_GetFeedback(&rollFFB)/FFB_ConvertMotorTorqueToFFBUnits
					(&rollFFB, ROLL_MOTOR_TORQUE_LIMIT))),
							-32767, 32767);


	FFBHid_SetAxis(hid, HID_PITCH, pitchAxis);
	FFBHid_SetAxis(hid, HID_ROLL, rollAxis);
	FFBHid_SetForceOutput(&ffbHid, HID_PITCH, scaledPitchForce);
	FFBHid_SetForceOutput(&ffbHid, HID_ROLL, scaledRollForce);

*/
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
	/*
	// Parse USB report fields
	bool ffbOn = UsbReportParseNextByte(usbReport) == 0x01 ? true : false;
	int aileronRangeInDeg = UsbReportParseNextInt(usbReport);
	int elevatorRangeInMM = UsbReportParseNextInt(usbReport);

	// FFB ON/OFF
	if(ffbOn) {
		//FFBStart(&ffbRoll);
		FFB_Start(&pitchFFB);
	}
	else {
		//FFBStop(&ffbRoll);
		FFB_Stop(&pitchFFB);
	}
*/
	/** FFB Control Ranges **/

	// Aileron encoder range
//	int aileronEncoderRange = aileronRangeInDeg *
//			PULLEY_AILERON_ENCODER_STEP_PER_DEGREE;
//	FFBSetControlRange(&ffbRoll, -aileronEncoderRange/2, aileronEncoderRange/2);
/*
	// Elevator encoder range
	int elevatorEncoderRange = elevatorRangeInMM * PITCH_STEP_PER_MM;
	FFB_SetControlRange(&pitchFFB, -elevatorEncoderRange/2,
			elevatorEncoderRange/2);
*/
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

	FFBForces_t pitchForces = FFBHid_GetForceData(hid, HID_PITCH);
	FFBAxis_SetForces(&pitchAxis, &pitchForces);

	FFBForces_t rollForces = FFBHid_GetForceData(hid, HID_ROLL);
	FFBAxis_SetForces(&rollAxis, &rollForces);

}

static void ProcessFFBHidControl(FFBHid_t *hid) {
#if !PID_TUNING_MODE
	if(FFBHid_GetFFBEnable(hid)) {
		FFBAxis_SetFFBOn(&pitchAxis);
		FFBAxis_SetFFBOn(&rollAxis);
	}
	else {
		FFBAxis_SetFFBOff(&pitchAxis);
		FFBAxis_SetFFBOff(&rollAxis);
	}

	TravelMinMax_t pitchTravel = FFBHid_GetAxisTravel(hid, HID_PITCH);
	AxisLimits_t *pitchLimits = FFBAxis_GetAxisLimits(&pitchAxis);
	AxisLimits_SetOperatingPositionRange(pitchLimits, (AxisRange_t) {
		.min = AxisGeometry_PosToRad(&pitchAxis.geom, pitchTravel.min),
		.max = AxisGeometry_PosToRad(&pitchAxis.geom, pitchTravel.max),
	});

//	FFB_SetControlRange(&pitchFFB, pitchTravel.min * PITCH_STEP_PER_MM,
//			pitchTravel.max * PITCH_STEP_PER_MM);

	TravelMinMax_t rollTravel = FFBHid_GetAxisTravel(hid, HID_ROLL);
	AxisLimits_t *rollLimits = FFBAxis_GetAxisLimits(&rollAxis);
	AxisLimits_SetOperatingPositionRange(rollLimits, (AxisRange_t) {
		.min = AxisGeometry_PosToRad(&rollAxis.geom, rollTravel.min),
		.max = AxisGeometry_PosToRad(&rollAxis.geom, rollTravel.max),
	});

//	FFB_SetControlRange(&rollFFB, rollTravel.min * ROLL_STEP_PER_DEGREE,
//			rollTravel.max * ROLL_STEP_PER_DEGREE);
#endif
}

static void ProcessFFBHidDataUpdate(FFBHid_t *hid) {
	/*
	// Prepare elevator axis
	int pitchEncoderCountConstrained = Constrain(Encoder_GetCount(
			&pitchEncoder),
			FFB_GetMinControlRange(&pitchFFB),
			FFB_GetMaxControlRange(&pitchFFB));

	// Map pitch values to pitch control range
	int16_t pitchAxis = (int16_t)Map(pitchEncoderCountConstrained,
			FFB_GetMinControlRange(&pitchFFB),
			FFB_GetMaxControlRange(&pitchFFB),
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
			FFB_GetMinControlRange(&rollFFB),
			FFB_GetMaxControlRange(&rollFFB));

	int16_t rollAxis = (int16_t)Map(rollAxisCountConstrained,
			FFB_GetMinControlRange(&rollFFB),
			FFB_GetMaxControlRange(&rollFFB),
			-32767, 32767);

	FFBHid_SetAxis(hid, HID_PITCH, pitchAxis);
	FFBHid_SetAxis(hid, HID_ROLL, rollAxis);
	*/
}

static void MotorControlCallback(Motor_t *motor, Encoder_t *encoder, int id,
		float deltaTimeMs) {
	if(!appInitialized) {
		return;
	}

//	GPIOSetState(&probeGpio, GPIO_HIGH);

//	uint32_t start = DWT_GetCount();

	Bsp_ADCUpdate(id);
	switch(id) {
		case BSP_PITCH_ID:
			FFBAxis_ControlISR(&pitchAxis, deltaTimeMs);
			break;
		case BSP_ROLL_ID:
			FFBAxis_ControlISR(&rollAxis, deltaTimeMs);
			break;
		default:
			// Invalid ID
			// Do nothing
			break;
	}

	Bsp_EncoderUpdate(id);

//	uint32_t elapsed = DWT_GetCount() - start;
//
//	if(elapsed > maxDwtCycles) {
//		maxDwtCycles = elapsed;
//		elapsedTime = DWT_ConvertCyclesToUs(maxDwtCycles);
//	}

//	Encoder_Update(encoder, deltaTimeMs);
//	Motor_Update(motor, deltaTimeMs);

//	GPIOSetState(&probeGpio, GPIO_LOW);
}

// *** Serial data acquisition functions ***
static void SerialDAQTxCallback(SerialDAQ_t *serialDaq) {
//	if(!appRunning) {
//		return;
//	}
#if !PID_TUNING_MODE
	Log_UpdateDMA();
#endif
}

static void SerialDAQRxCallback(SerialDAQ_t *serialDaq) {
//	if(!appRunning) {
//		return;
//	}
#if PID_TUNING_MODE
	SerialDAQ_Update(serialDaq);
#endif
}

static void FFBControlCallback(float deltaTimeMs) {
	if(!appInitialized) {
		return;
	}
#if PID_TUNING_MODE
	MotionControlCommand_t command = {
			.type = MOTION_CONTROL_TYPE_VELOCITY,
			.data.velocityCommand = {
					.velocityTarget = pidSetPoint,
					.torqueLimit = 1.0f,
					.accelerationLimit = 1000.0f,
			},
	};

//	MotionControlCommand_t command = {
//			.type = MOTION_CONTROL_TYPE_TORQUE,
//			.data.torqueCommand = {
//					.torqueTarget = velocitySetPoint,
//					.torqueLimit = 0.65,
//			},
//	};
	FFBAxis_ApplyMotionCommand(&pitchAxis, &command, deltaTimeMs/1000.0f);
#endif

	uint32_t start = DWT_GetCount();
 	FFBAxis_Update(&pitchAxis, deltaTimeMs);
	FFBAxis_Update(&rollAxis, deltaTimeMs);
	uint32_t elapsed = DWT_GetCount() - start;

	if(elapsed > maxDwtCycles) {
		maxDwtCycles = elapsed;
		elapsedTime = DWT_ConvertCyclesToUs(maxDwtCycles);
	}

	ffbUpdateFlag = 1;

//	FFB_Update(&pitchFFB, deltaTimeMs);
//	FFB_Update(&rollFFB, deltaTimeMs);
}

static void LoadCellUpdateCallback(void) {
	LoadCell_Update(&pitchLoadCell);
}


// *** PID Tuner Callbacks ***
static void SetMotorSetPoint(float setPoint) {
//	Motor_SetCurrent(&pitchMotor, setPoint);
//	BLDCMotor_SetQCurrent(&pitchBLDCMotor, setPoint);

	pidSetPoint = setPoint;


}

static float GetMotorActual(void) {
//	return Motor_GetMeasuredCurrent(&pitchMotor, 0);
//	return BLDCMotor_GetQCurrentReading(&pitchBLDCMotor);
//	return pitchMotor.velocityState.velControl.velocityState;
//	return pitchAxis.ve.velocityEstimate;
	return FFBAxis_GetAxisKinematics(&pitchAxis)->velocity;
}

static float GetMotorPower(void) {
	return FFBAxis_GetAxisKinematics(&pitchAxis)->motorTorque;
//	return Motor_GetCurrent(&pitchMotor);
//	return pitchMotor.velocityState.velControl.velocitySetPoint;
//	return pitchAxis.velControl.radsSetPoint;
}
