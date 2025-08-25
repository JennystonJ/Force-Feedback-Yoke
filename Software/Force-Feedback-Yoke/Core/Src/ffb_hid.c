/*
 * ffb_hid.c
 *
 *  Created on: Aug 21, 2025
 *      Author: Jennyston
 */

#include "ffb_hid.h"
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define FFB_HID_RX_BUFFER_SIZE 12
#define FFB_HID_RX_CONTROL_BUFFER_SIZE 6

typedef struct __attribute__((packed)) FFBHIDReceivePacket {
	FFBForcesPacked_t packedForce;
}FFBHIDReceivePacket;

void FFBHid_Init(FFBHid_t *ffbHid, USBD_HandleTypeDef *husbd) {
	memset(ffbHid, 0, sizeof(FFBHid_t));
	ffbHid->husbd = husbd;

	HID_Init(husbd);
	HID_SetControlBuffer((uint8_t *)&ffbHid->controlData);
	HID_SetCapabilitiesBuffer((uint8_t *)&ffbHid->capabilities);
}

void FFBHid_SetAxisTravelLimit(FFBHid_t *ffbHid, uint8_t axis, float limit) {
	ffbHid->capabilities.travelLimit[axis] = limit;
}

void FFBHid_SetAxisMaxForce(FFBHid_t *ffbHid, uint8_t axis, float maxForce) {
	ffbHid->capabilities.axisMaxForce[axis] = maxForce;
}

void FFBHid_SetMaxSupportedForces(FFBHid_t *ffbHid, uint8_t numMaxForces) {
	ffbHid->capabilities.maxSupportedForces = numMaxForces;
}

void FFBHid_EnableCapabilities(FFBHid_t *ffbHid) {
	ffbHid->capabilities.initialized = true;
}

void FFBHid_SetAxis(FFBHid_t *ffbHid, uint8_t axis, int16_t value) {
	ffbHid->txPacket.axis[axis] = value;
}

void FFBHid_SetForceOutput(FFBHid_t *ffbHid, uint8_t axis, int16_t value) {
	ffbHid->txPacket.forceOutput[axis] = value;
}

bool FFBHid_GetFFBEnable(FFBHid_t *ffbHid) {
	return ffbHid->controlData.ffbEnabled;
}

TravelMinMax_t FFBHid_GetAxisTravel(FFBHid_t *ffbHid, uint8_t axis) {
	return ffbHid->controlData.axisLimits[axis];
}

FFBForces_t FFBHid_GetForceData(FFBHid_t *ffbHid) {
	return ffbHid->forceData[ffbHid->forceDataFrontBufferIndex];
}

void FFBHid_RegisterForceReceivedCallback(FFBHid_t *ffbHid,
		void (*ForceReceivedCallback)(FFBHid_t *ffbHid)) {
	ffbHid->ForceReceivedCallback = ForceReceivedCallback;
}

void FFBHid_RegisterControlReceivedCallback(FFBHid_t *ffbHid,
		void (*ControlReceivedCallback)(FFBHid_t *ffbHid)) {
	ffbHid->ControlReceivedCallback = ControlReceivedCallback;
}

void FFBHid_RegisterUpdateCallback(FFBHid_t *ffbHid,
		void (*UpdateCallback)(FFBHid_t *ffbHid)) {
	ffbHid->UpdateCallback = UpdateCallback;
}

void FFBHid_Update(FFBHid_t *ffbHid) {
	if(HID_GetDataReady()) {

		if(HID_GetReceiveReady()) {
			uint8_t *buffer = HID_ReadReceiveBuffer();
			FFBHIDReceivePacket packet;
			memcpy(&packet, buffer, FFB_HID_RX_BUFFER_SIZE);
			// Unpack to back buffer
			FFB_ForceUnpack(&ffbHid->
					forceData[!ffbHid->forceDataFrontBufferIndex],
					&packet.packedForce);
			// Swap buffers
			ffbHid->forceDataFrontBufferIndex =
					!ffbHid->forceDataFrontBufferIndex;

			if(ffbHid->ForceReceivedCallback != NULL) {
				ffbHid->ForceReceivedCallback(ffbHid);
			}
		}

		if(HID_GetControlReady()) {
			uint8_t *buffer = HID_ReadControlBuffer();

			// Copy to control data buffer before assigning to hid control data
			// to prevent non-atomic writes and ensure memory alignment with
			// memcpy
			FFBHidControlData_t controlDataBuffer;
			memcpy(&controlDataBuffer, buffer, sizeof(controlDataBuffer));
			ffbHid->controlData = controlDataBuffer;


			if(ffbHid->ForceReceivedCallback != NULL) {
				ffbHid->ControlReceivedCallback(ffbHid);
			}
		}

		if(ffbHid->UpdateCallback != NULL) {
			ffbHid->UpdateCallback(ffbHid);
		}

	}
	else {
		// Do nothing
	}

	HID_TransmitData((uint8_t *)&ffbHid->txPacket, sizeof(ffbHid->txPacket));
}
