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

extern USBD_HandleTypeDef hUsbDeviceFS;
uint8_t reportTxBuffer[5];
uint8_t txBuffer[64];
uint8_t report_buffer[64];
uint8_t flag_rx = 0;

UsbReport_t usbReport;

bool appInitialized = false;
bool appRunning = false;

Button_t btnAccept;


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
//			MotorSetPower(&pitchMotor, MotorGetPower(&pitchMotor)+100);
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
	//FFBInit(&ffbRoll, &rollMotor, &rollEncoder);

	appInitialized = true;
	printf("Ready!\r\n");

	// Wait for button press then release before proceeding
//	while(ButtonIsPressed(&btnAccept)) {
//	}
//	while(!ButtonIsPressed(&btnAccept)) {
//	}
//	while(ButtonIsPressed(&btnAccept)) {
//	}

	// Register callback for future presses
	ButtonSetStateChangedCallback(&btnAccept, &ButtonStateChangedCallback);

}

void ApplicationRun(void) {
	appRunning = true;

	FFBHome(&ffbPitch);

	// Indicate homing is complete
	GPIOSetState(&gpioStatus, GPIO_HIGH);

	// Remove spring force
	FFBSpringParam_t spring = {
			.minimumSpringForce = 0,
			.offset = 0,
			.strength = 0,
	};
	FFBSetSpringParams(&ffbPitch, spring);

	// Application is now running in loop
	while(1) {
		if(flag_rx == 1){

			flag_rx = 0;

			UsbReportLoad(&usbReport, report_buffer,
					USBD_CUSTOMHID_OUTREPORT_BUF_SIZE);
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
//			int16_t aileron = (int16_t)Constrain(((
//					EncoderGetCount(&rollEncoder)/4095.0f) *
//					32767), -32767, 32767);

			// TODO: Un-comment
//			int rollEncoderCountConstrained = Constrain(EncoderGetCount(
//					&rollEncoder), -32767, 32767);
			// TODO: Remove
			int rollEncoderCountConstrained = 0;

			// Map roll values to roll control range
//			int16_t aileron = (int16_t)Map(rollEncoderCountConstrained,
//					FFBGetMinControlRange(&ffbRoll),
//					FFBGetMaxControlRange(&ffbRoll),
//					-32767, 32767);

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

			// Set report ID to 1 (Data)
			reportTxBuffer[0] = 0x01;
			reportTxBuffer[1] = 0;//aileron & 0xFF;
			reportTxBuffer[2] = 0;//aileron >> 8;
			reportTxBuffer[3] = elevator >> 8;
			reportTxBuffer[4] = elevator & 0xFF;

			USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, reportTxBuffer, 5);

			usbPacketCount++;
		}

		angle = (EncoderGetCount(&rollEncoder)/49152.0f)*360.0f;

		HAL_Delay(5);

	}
}

void ApplicationUpdate(int deltaTimeUs) {
	if(!appInitialized) {
		return;
	}

	ButtonProcessInt(&btnAccept);
	ProcessEncoders(deltaTimeUs);

}

void ProcessEncoders(int deltaTimeUs) {
	EncoderUpdate(&pitchEncoder, deltaTimeUs);
	//EncoderUpdate(&rollEncoder, deltaTimeUs);
}

void ApplicationFFBUpdate(int deltaTimeUs) {
	if(!appInitialized || !appRunning) {
		return;
	}
	FFBUpdate(&ffbPitch, deltaTimeUs);
	//FFBUpdate(&ffbRoll, deltaTimeUs);
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
//	FFBSetControlRange(&ffbRoll, -aileronEncoderRange/2, aileronEncoderRange/2);

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

void DecodeUsbReportFFB(void) {

}
