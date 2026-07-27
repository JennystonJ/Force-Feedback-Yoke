/*
 * mt6835_interface.c
 *
 *  Created on: Jul 6, 2025
 *      Author: Jennyston
 */

#include "devices/mt6835_interface.h"
#include <stdint.h>

// Private function prototypes
static int GetEncoderSensorCount(EncoderInterface_t *interface);
static int GetEncoderSensorAbsCount(EncoderInterface_t *interface);
static EncoderEdgeTime_t GetEncoderSensorEdgeTime(EncoderInterface_t *interface);

void MT6835Interface_Init(EncoderInterface_t *interface, MT6835_t *hwEncoder) {
	interface->hardwareEncoder = hwEncoder;
	interface->GetEncoderSensorCount = &GetEncoderSensorCount;
	interface->GetEncoderSensorAbsCount = &GetEncoderSensorAbsCount;
	interface->GetEncoderSensorEdgeTime = &GetEncoderSensorEdgeTime;

	interface->data.positionCount = GetEncoderSensorAbsCount(interface);
	interface->data.prevAngle = interface->data.positionCount;
}

static int GetEncoderSensorCount(EncoderInterface_t *interface) {
	//	return MT6835_GetABCount((MT6835_t *)interface->hardwareEncoder);
	//	return MT6835_GetAngle((MT6835_t *)interface->hardwareEncoder);

	int32_t angle = MT6835_GetAngle((MT6835_t *)interface->hardwareEncoder);
	int32_t delta = angle - interface->data.prevAngle;

	if(delta > MT6835_COUNT_PER_REV >> 1) {
		delta -= MT6835_COUNT_PER_REV;
	}
	else if(delta < -MT6835_COUNT_PER_REV >> 1) {
		delta += MT6835_COUNT_PER_REV;
	}

	interface->data.positionCount += delta;
	interface->data.prevAngle = angle;

	return interface->data.positionCount;

}

static int GetEncoderSensorAbsCount(EncoderInterface_t *interface) {
	//	return MT6835_GetABCount((MT6835_t *)interface->hardwareEncoder) %
	//			MT6835_AB_COUNT_PER_REV;
	return MT6835_GetAngle((MT6835_t *)interface->hardwareEncoder);
}

static EncoderEdgeTime_t GetEncoderSensorEdgeTime(
		EncoderInterface_t *interface) {
	EncoderEdgeTime_t edgeData;
	MT6835_GetEdgeData((MT6835_t *)interface->hardwareEncoder,
			(uint32_t *)&edgeData.edgeTime, (int32_t *)&edgeData.edgeCount);

	return edgeData;
}
