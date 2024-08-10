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
uint8_t reportTxBuffer[3];
uint8_t txBuffer[64];
uint8_t report_buffer[64];
uint8_t flag = 0;
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

// Private function prototypes
void ProcessEncoders(int deltaTimeUs);
void CommandLineMode(void);

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
	while(ButtonIsPressed(&btnAccept)) {
	}
	while(!ButtonIsPressed(&btnAccept)) {
	}
	while(ButtonIsPressed(&btnAccept)) {
	}

	// Register callback for future presses
	ButtonSetStateChangedCallback(&btnAccept, &ButtonStateChangedCallback);

	// Indicate application is running
	GPIOSetState(&gpioStatus, GPIO_HIGH);
}

void ApplicationRun(void) {
	appRunning = true;

	FFBHome(&ffbPitch);
	while(1) {}

	int32_t periFrequency = 0;
	float periAmplitude = 0.0f;
	float sprStrength = 0.0f;

	// Application is now running in loop
	while(1) {
		if(flag_rx == 1){

			flag_rx = 0;

			UsbReportLoad(&usbReport, report_buffer,
					USBD_CUSTOMHID_OUTREPORT_BUF_SIZE);
			sprStrength = UsbReportParseNextFloat(&usbReport);
			periAmplitude = UsbReportParseNextFloat(&usbReport);
			periFrequency = UsbReportParseNextFloat(&usbReport);

			// Prepare and send aileron axis
					  int16_t aileron = (int16_t)Constrain(((
							  EncoderGetCount(&rollEncoder)/4095.0f) *
							  32767), -32767, 32767);

			// Set report ID to 1
			reportTxBuffer[0] = 0x01;
			reportTxBuffer[1] = aileron & 0xFF;
			reportTxBuffer[2] = aileron >> 8;

			USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, reportTxBuffer, 3);
		}

		if(flag == 1) {
			USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, txBuffer, 64);

			flag = 0;
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

void DecodeUsbReportFFB(void) {

}
