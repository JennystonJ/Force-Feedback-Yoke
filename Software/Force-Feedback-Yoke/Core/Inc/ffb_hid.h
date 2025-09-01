/*
 * ffb_hid.h
 *
 *  Created on: Aug 21, 2025
 *      Author: Jennyston
 */

#ifndef INC_FFB_HID_H_
#define INC_FFB_HID_H_

#include "hid.h"

#define FFB_HID_NUM_AXIS 2

#include "force_feedback/force_feedback_force.h"

typedef struct TravelMinMax {
	float min;
	float max;
} TravelMinMax_t;

typedef struct __attribute__((packed)) FFBHidControlData {
	bool ffbEnabled;
	TravelMinMax_t axisLimits[FFB_HID_NUM_AXIS];
} FFBHidControlData_t;

typedef struct __attribute__((packed)) FFBHidCapabilities {
	bool initialized;
	float travelLimit[FFB_HID_NUM_AXIS];
	float axisMaxForce[FFB_HID_NUM_AXIS];
	uint8_t maxSupportedForces;
} FFBHidCapabilities_t;

typedef struct __attribute__((packed)) FFBHidTransmitPacket {
	int16_t axis[FFB_HID_NUM_AXIS];
	int16_t forceOutput[FFB_HID_NUM_AXIS];
} FFBHidTransmitPacket_t;

typedef struct FFBHid FFBHid_t;
struct FFBHid {
	USBD_HandleTypeDef *husbd;

	uint8_t forceDataFrontBufferIndex;
	FFBForces_t forceData[FFB_HID_NUM_AXIS][2];

	FFBHidControlData_t controlData;
	FFBHidCapabilities_t capabilities;
	FFBHidTransmitPacket_t txPacket;

	void (*ForceReceivedCallback)(FFBHid_t *ffbHid);
	void (*ControlReceivedCallback)(FFBHid_t *ffbHid);
	void (*UpdateCallback)(FFBHid_t *ffbHid);
};

void FFBHid_Init(FFBHid_t *ffbHid, USBD_HandleTypeDef *husbd);
void FFBHid_SetAxisTravelLimit(FFBHid_t *ffbHid, uint8_t axis, float limit);
void FFBHid_SetAxisMaxForce(FFBHid_t *ffbHid, uint8_t axis, float maxPower);
void FFBHid_SetMaxSupportedForces(FFBHid_t *ffbHid, uint8_t numMaxForces);
void FFBHid_EnableCapabilities(FFBHid_t *ffbHid);
void FFBHid_SetAxis(FFBHid_t *ffbHid, uint8_t axis, int16_t value);
void FFBHid_SetForceOutput(FFBHid_t *ffbHid, uint8_t axis, int16_t value);
bool FFBHid_GetFFBEnable(FFBHid_t *ffbHid);
TravelMinMax_t FFBHid_GetAxisTravel(FFBHid_t *ffbHid, uint8_t axis);
FFBForces_t FFBHid_GetForceData(FFBHid_t *ffbHid, uint8_t axis);
void FFBHid_RegisterForceReceivedCallback(FFBHid_t *ffbHid,
		void (*ForceReceivedCallback)(FFBHid_t *ffbHid));
void FFBHid_RegisterControlReceivedCallback(FFBHid_t *ffbHid,
		void (*ControlReceivedCallback)(FFBHid_t *ffbHid));
void FFBHid_RegisterUpdateCallback(FFBHid_t *ffbHid,
		void (*UpdateCallback)(FFBHid_t *ffbHid));
void FFBHid_Update(FFBHid_t *ffbHid);

#endif /* INC_FFB_HID_H_ */
