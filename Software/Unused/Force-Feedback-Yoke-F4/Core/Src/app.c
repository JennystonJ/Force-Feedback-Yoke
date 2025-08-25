/*
 * app.c
 *
 *  Created on: Jul 13, 2024
 *      Author: Jennyston
 */

#include "app.h"
#include "main.h"
#include "bsp.h"

#include <usb_device.h>
#include "usb_report.h"
#include <usbd_customhid.h>

#include "force_feedback_controller.h"

#include "utilities/utilities.h"

#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <math.h>

#include "usb_ctrl_request.h"
#include "anti_cog.h"
#include "anti_cog_pitch_data.h"

extern USBD_HandleTypeDef hUsbDeviceFS;
uint8_t reportTxBuffer[5];
uint8_t txBuffer[64];
uint8_t report_buffer[64];
uint8_t flag_rx = 0;

UsbReport_t usbReport;

bool appInitialized = false;
bool appRunning = false;
bool appFastUpdateFlag = false;
bool appUpdateFlag = false;
int appUpdateDt = 0;
int appFastUpdateDt = 0;

int watchDogCount = 0;
int startCalCycleCount = 0;

Button_t btnAccept;

AntiCog_t antiCogPitch;
//float antiCogMapPitch[512];
int cogCalibrationTimeElapsed = 0;
bool forwardDumped = false;
bool reverseDumped = false;

// FFB variables
FFBController_t ffbPitch;
FFBController_t ffbRoll;

// For live debugging
static float angle;
static long usbPacketCount = 0;

// Private function prototypes
void ProcessEncoders(int deltaTimeUs);
void CommandLineMode(void);
void ProcessUsbControlData(UsbReport_t *usbReport);
void ProcessUsbFFBData(UsbReport_t *usbReport);
void ProcessUSBPacket(void);

// Callbacks
void ButtonStateChangedCallback(Button_t *button) {
	if(button == &btnAccept) {
		// Add implementation for accept button here
		if(ButtonIsPressed(&btnAccept)) {
			switch (FFBGetState(&ffbPitch)) {
				case FFB_RUNNING:
					FFBStop(&ffbPitch);
					break;
				case FFB_STOPPED:
					FFBStart(&ffbPitch);
					break;
				default:
					FFBStop(&ffbPitch);
					break;
			}
		}
	}
}

int ButtonReadState(Button_t *button) {
	if(button == &btnAccept) {
		return GPIOGetState(&gpioAccept) == GPIO_HIGH ? 1 : 0;
	}

	return 0;
}

void ApplicationInit(void) {

	appInitialized = false;
	appRunning = false;

	UsbReportInit(&usbReport, USB_REPORT_IN_LITTLE_ENDIAN);

	ButtonInit(&btnAccept, &ButtonReadState);

	FFBInit(&ffbPitch, &pitchMotor, &pitchEncoder);
	FFBSetLoadCell(&ffbPitch, &pitchLoadCell);

	FFBInit(&ffbRoll, &rollMotor, &rollEncoder);

	// TODO: Reorganize calibration code
	AntiCogInit(&antiCogPitch, &pitchEncoder, pitchCogMap,
			sizeof(pitchCogMap)/sizeof(float));
	MotorSetAntiCog(&pitchMotor, &antiCogPitch);


	appInitialized = true;

	// Register callback for button presses
	ButtonSetStateChangedCallback(&btnAccept, &ButtonStateChangedCallback);

}

void ApplicationRun(void) {
	appRunning = true;

//	FFBHome(&ffbPitch);
	EncoderResetCount(&rollEncoder);

	// Indicate homing is complete
	GPIOSetState(&gpioStatus, GPIO_HIGH);

	// Remove spring force
	FFBSpringParam_t spring = {
			.minimumSpringForce = 0,
			.offset = 0,
			.strength = 0,
	};

	MotorSetCurrent(&pitchMotor, 0);
//	FFBSetSpringParams(&ffbPitch, spring);
	// Application is now running in loop
	while(1) {

		if(appFastUpdateFlag) {
			ApplicationFastUpdate(appFastUpdateDt);
			appFastUpdateFlag = false;
		}

		if(appUpdateFlag) {
			ApplicationUpdate(appUpdateDt);
			appUpdateFlag = false;
		}

		if(pidTunerUpdateFlag) {
//			BspUpdatePIDTuner(MotorGetMeasuredCurrent(&pitchMotor),
//								MotorGetPower(&pitchMotor),
//								MotorGetPIDCurrent(&pitchMotor));
//			MotorSetCurrent(&pitchMotor, pidTunerSetPoint);
//			BspUpdatePIDTuner(EncoderGetCount(&pitchEncoder),
//					MotorGetCurrent(&pitchMotor),
//					&antiCogPitch.calibration.pidPosition);

			BspUpdatePIDTuner(antiCogPitch.calibration.lpfSpeed.out,
					MotorGetCurrent(&pitchMotor),
					&antiCogPitch.calibration.pidSpeed);
			pidTunerUpdateFlag = false;
		}

		watchDogCount = 0;
//		angle = (EncoderGetCount(&rollEncoder)/49152.0f)*360.0f;
	}
}

void ApplicationHighPriorityUpdate(int deltaTimeUs) {
	if(!appInitialized) {
		return;
	}

	BspUpdateDeviceData();
	MotorCurrentUpdate(&pitchMotor, deltaTimeUs);
}

void ApplicationSetFastUpdateFlag(int deltaTimeUs) {
	if(!appInitialized) {
		return;
	}

	appFastUpdateDt = deltaTimeUs;
	appFastUpdateFlag = true;
}

void ApplicationFastUpdate(int deltaTimeUs) {
	if(!appInitialized) {
		return;
	}

	ProcessEncoders(deltaTimeUs);
//	AntiCogCalibrationUpdate2(&antiCogPitch, deltaTimeUs);
//	if(antiCogPitch.calibration.speedLocked) {
//		cogCalibrationTimeElapsed++;
//	}
//	if(cogCalibrationTimeElapsed == 60000 && !forwardDumped) {
//		MotorSetPower(&pitchMotor, 0);
//		BspDumpCogData(antiCogMapPitch, sizeof(antiCogMapPitch)/sizeof(float),
//				"======== Forward Cog Data ========\r\n");
//		forwardDumped = true;
//
//		AntiCogStartCalibration(&antiCogPitch, &pitchMotor, true);
//	}
//	else if(cogCalibrationTimeElapsed == 120000 && !reverseDumped) {
//		MotorSetPower(&pitchMotor, 0);
//
//		BspDumpCogData(antiCogMapPitch, sizeof(antiCogMapPitch)/sizeof(float),
//				"======== Reverse Cog Data ========\r\n");
//
//		reverseDumped = true;
//		while(true);
//	}
//	AntiCogCalibrationUpdate(&antiCogPitch, deltaTimeUs);

//	MotorSetCurrent(&pitchMotor, pidTunerSetPoint);
}

void ApplicationSetUpdateFlag(int deltaTimeUs) {
	if(!appInitialized) {
		return;
	}

	appUpdateDt = deltaTimeUs;
	appUpdateFlag = true;
}

void ApplicationUpdate(int deltaTimeUs) {

	ButtonProcessInt(&btnAccept);

//	startCalCycleCount++;
//	if(startCalCycleCount > 16 && fabsf(EncoderGetSpeed(&pitchEncoder)) < 0.01) {
//		startCalCycleCount = 0;
//		// Motor isn't moving, calibrate
////		MotorCurrentCalibrate(&pitchMotor);
//		static bool antiCogCalibrating = false;
//		if(!antiCogCalibrating) {
//			antiCogCalibrating = true;
//			AntiCogStartCalibration(&antiCogPitch, &pitchMotor, false);
//		}
//	}
	//TODO: Un-comment for force feedback (disabled for PID current tuning)
//
//	ApplicationFFBUpdate(deltaTimeUs);
//
//	ProcessUSBPacket();
}

void ProcessUSBPacket(void) {
	if(flag_rx == 1){

		flag_rx = 0;

		UsbReportLoad(&usbReport, report_buffer,
				USBD_CUSTOMHID_OUTREPORT_BUF_SIZE);
		// Determine report ID and call appropriate function
		switch(UsbReportGetReportId(&usbReport)) {
		case 0x01:
			ProcessUsbFFBData(&usbReport);
			break;
		case 0x02:
			ProcessUsbControlData(&usbReport);
			break;
		default:
			// Invalid reportID
			break;
		}

		// Prepare aileron axis
		int rollEncoderCountConstrained = Constrain(EncoderGetCount(
				&rollEncoder),
				FFBGetMinControlRange(&ffbRoll),
				FFBGetMaxControlRange(&ffbRoll));

		// Map roll values to roll control range
		int16_t aileron = (int16_t)Map(rollEncoderCountConstrained,
				FFBGetMinControlRange(&ffbRoll),
				FFBGetMaxControlRange(&ffbRoll),
				-32767, 32767);

		// Prepare elevator axis
		int pitchEncoderCountConstrained = Constrain(EncoderGetCount(
				&pitchEncoder),
				FFBGetMinControlRange(&ffbPitch),
				FFBGetMaxControlRange(&ffbPitch));

		// Map pitch values to pitch control range
		int16_t elevator = (int16_t)Map(pitchEncoderCountConstrained,
				FFBGetMinControlRange(&ffbPitch),
				FFBGetMaxControlRange(&ffbPitch),
				-32767, 32767);

		// Prepare USB packet
		// Set report ID to 1 (Data)
		reportTxBuffer[0] = 0x01;
		reportTxBuffer[1] = aileron >> 8;
		reportTxBuffer[2] = aileron & 0xFF;
		reportTxBuffer[3] = elevator >> 8;
		reportTxBuffer[4] = elevator & 0xFF;

		USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, reportTxBuffer, 5);

		usbPacketCount++;
	}

}

void ProcessEncoders(int deltaTimeUs) {
	EncoderUpdate(&pitchEncoder, deltaTimeUs/1000.0f);
//	EncoderUpdate(&rollEncoder, deltaTimeUs);
}

void ApplicationFFBUpdate(int deltaTimeUs) {
	if(!appInitialized || !appRunning) {
		return;
	}
//	TODO: Remove (for PID tuning)
	return;

	FFBUpdate(&ffbPitch, deltaTimeUs);
	FFBUpdate(&ffbRoll, deltaTimeUs);
}

void ApplicationProcessWatchDog(void) {
	if(!appInitialized) {
		return;
	}

	watchDogCount++;
	if(watchDogCount >= 100) {
		// Application stuck, trigger E-stop
		//BspSetEStop(true);
	}
}

void ProcessUsbControlData(UsbReport_t *usbReport) {
	// Parse USB report fields
	bool ffbOn = UsbReportParseNextByte(usbReport) == 0x01 ? true : false;
	int aileronRangeInDeg = UsbReportParseNextInt(usbReport);
	int elevatorRangeInMM = UsbReportParseNextInt(usbReport);

	// FFB ON/OFF
	if(ffbOn) {
		//FFBStart(&ffbRoll);
		FFBStart(&ffbPitch);
	}
	else {
		//FFBStop(&ffbRoll);
		FFBStop(&ffbPitch);
	}

	/** FFB Control Ranges **/

	// Aileron encoder range
	int aileronEncoderRange = aileronRangeInDeg *
			PULLEY_AILERON_ENCODER_STEP_PER_DEGREE;
	FFBSetControlRange(&ffbRoll, -aileronEncoderRange/2, aileronEncoderRange/2);

	// Elevator encoder range
	int elevatorEncoderRange = elevatorRangeInMM *
			PULLEY_ELEVATOR_ENCODER_STEP_PER_MM;
	FFBSetControlRange(&ffbPitch, -elevatorEncoderRange/2,
			elevatorEncoderRange/2);

}

void ProcessUsbFFBData(UsbReport_t *usbReport) {
	// Parse USB report fields
	float rollForce = UsbReportParseNextFloat(usbReport);
	float pitchForce = UsbReportParseNextFloat(usbReport);

	// Assign forces
//	FFBSetConstantStrength(&ffbRoll, rollForce);
	FFBSetConstantStrength(&ffbPitch, pitchForce);
}

void USBD_CTRL_Vendor_Req(uint8_t bRequest) {
	// Receive data from host
	uint8_t receivedData[8];
	USBD_CtlPrepareRx(&hUsbDeviceFS, receivedData, sizeof(receivedData));

	switch(bRequest) {
	case USB_REQ_GET_FFB_EN:
	{
		uint8_t response = FFBGetState(&ffbPitch) != FFB_STOPPED;
		USBD_CtlSendData(&hUsbDeviceFS, &response, 1);
		break;
	}
	case USB_REQ_SET_FFB_EN:
	{
		bool ffbOn = receivedData[0] == 0x01 ? true : false;
		if(ffbOn) {
			//FFBStart(&ffbRoll);
			FFBStart(&ffbPitch);
		}
		else {
			//FFBStop(&ffbRoll);
			FFBStop(&ffbPitch);
		}
		break;
	}
	case USB_REQ_GET_PITCH_RANGE:
	{
		int pitchRangeInMM = FFBGetMaxControlRange(&ffbPitch)*2 /
			PULLEY_ELEVATOR_ENCODER_STEP_PER_MM;
		USBD_CtlSendData(&hUsbDeviceFS, (uint8_t *)&pitchRangeInMM,
				sizeof(pitchRangeInMM));
		break;
	}
	case USB_REQ_SET_PITCH_RANGE:
	{
		int pitchRangeInMM = *(int *)receivedData;
		int pitchEncoderRange = pitchRangeInMM *
				PULLEY_ELEVATOR_ENCODER_STEP_PER_MM;
		FFBSetControlRange(&ffbPitch, -pitchEncoderRange/2,
				pitchEncoderRange/2);
		break;
	}
	case USB_REQ_GET_ROLL_RANGE:
	{
		int rollRangeInDeg = FFBGetMaxControlRange(&ffbRoll)*2 /
			PULLEY_AILERON_ENCODER_STEP_PER_DEGREE;
		USBD_CtlSendData(&hUsbDeviceFS, (uint8_t *)&rollRangeInDeg,
				sizeof(rollRangeInDeg));
		break;
	}
	case USB_REQ_SET_ROLL_RANGE:
	{
		int rollRangeInDeg = *(int *)receivedData;
		int rollEncoderRange = rollRangeInDeg *
				PULLEY_AILERON_ENCODER_STEP_PER_DEGREE;
		FFBSetControlRange(&ffbRoll, -rollEncoderRange/2,
				rollEncoderRange/2);
		break;
	}
	}
}

