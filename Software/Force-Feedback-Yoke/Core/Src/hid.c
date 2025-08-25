/*
 * hid.c
 *
 *  Created on: Aug 21, 2025
 *      Author: Jennyston
 */

#include "hid.h"
#include <usbd_custom_hid_if.h>
#include <stddef.h>
#include <string.h>

#define HID_NUM_REPORT_IDS 5

// Types
typedef struct HID {
	USBD_HandleTypeDef *husbd;

	uint8_t inBuffer[64];
	uint8_t outBuffer[64];

	uint8_t rxBufferControl[64];
	uint8_t *txBufferControlFront;
	uint8_t txBufferControl[64];

	uint8_t *capabilitiesBufferFront;
	uint8_t capabilitiesBuffer[64];


	bool rxReady[HID_NUM_REPORT_IDS];

	void (*HIDReceive)(USBD_HandleTypeDef *husbd);

	bool comError;
} HID_t;

// Private variables
static HID_t hid;

// Private forward function prototypes
static void OutEvent(uint8_t *buffer);
static uint8_t *GetReport(uint8_t reportId, uint8_t reportType,
		  uint16_t *reportLength);

void HID_Init(USBD_HandleTypeDef *husbd) {
	memset(&hid, 0, sizeof(HID_t));
	hid.husbd = husbd;
	hid.txBufferControl[0] = HID_CONTROL_REPORT_ID;
	hid.capabilitiesBuffer[0] = HID_CAPABILITIES_REPORT_ID;


	CUSTOM_HID_RegisterOutEventCallback(OutEvent);
	CUSTOM_HID_RegisterGetReportCallback(GetReport);
}

void HID_RegisterReceiveCallback(void (*HIDReceive)(USBD_HandleTypeDef *husbd)) {
	hid.HIDReceive = HIDReceive;
}

uint8_t *HID_ReadControlBuffer(void) {
	hid.rxReady[HID_CONTROL_REPORT_ID] = false;
	// Add 1 to address and return to skip the report ID
	return hid.rxBufferControl+1;
}

void HID_SetControlBuffer(uint8_t *controlBuffer) {
	hid.txBufferControlFront = controlBuffer;
}

void HID_SetCapabilitiesBuffer(uint8_t *capabilitiesBuffer) {
	hid.capabilitiesBufferFront = capabilitiesBuffer;
}


uint8_t *HID_ReadReceiveBuffer(void) {
	hid.rxReady[HID_OUT_REPORT_ID] = false;
	// Add 1 to address and return to skip the report ID
	return hid.outBuffer+1;
}

bool HID_GetDataReady(void) {
	return HID_GetReceiveReady() || HID_GetControlReady();
}

bool HID_GetReceiveReady(void) {
	return hid.rxReady[HID_OUT_REPORT_ID];
}

bool HID_GetControlReady(void) {
	return hid.rxReady[HID_CONTROL_REPORT_ID];
}

void HID_TransmitData(const uint8_t *buffer, uint8_t len) {
	hid.inBuffer[0] = HID_IN_REPORT_ID;
	memcpy(hid.inBuffer+1, buffer, len);
	USBD_CUSTOM_HID_SendReport(hid.husbd, hid.inBuffer, len+1);
}

// Private functions
static void OutEvent(uint8_t *buffer) {
	bool idValid = false;
	switch(buffer[0]) {
		case HID_CONTROL_REPORT_ID:
			memcpy(hid.rxBufferControl, buffer, sizeof(hid.rxBufferControl));
			hid.rxReady[HID_CONTROL_REPORT_ID] = true;
			idValid = true;
			break;
		case HID_IN_REPORT_ID:
			// Do nothing, this ID is only used for input (device to host)
			break;
		case HID_OUT_REPORT_ID:
			memcpy(hid.outBuffer, buffer, sizeof(hid.outBuffer));
			hid.rxReady[HID_OUT_REPORT_ID] = true;
			idValid = true;
			break;
		default:
			// Invalid report ID
			break;
	}

	if(idValid && hid.HIDReceive != NULL) {
		hid.HIDReceive(hid.husbd);
	}

}

static uint8_t *GetReport(uint8_t reportId, uint8_t reportType,
		  uint16_t *reportLength) {
	uint8_t *reportBuffer = NULL;
	uint8_t *frontBuffer = NULL;
	switch(reportId) {
		case HID_CONTROL_REPORT_ID:
			reportBuffer = hid.txBufferControl;
			frontBuffer = hid.txBufferControlFront;
			break;
		case HID_CAPABILITIES_REPORT_ID:
			reportBuffer = hid.capabilitiesBuffer;
			frontBuffer = hid.capabilitiesBufferFront;
			break;
		default:
			// Invalid report ID for get report
			hid.comError = true;
			break;
	}

	// copy to report buffer, one byte after report ID
	memcpy(reportBuffer+1, frontBuffer, (*reportLength)-1);

	return reportBuffer;
}
