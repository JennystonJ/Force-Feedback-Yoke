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

void MT6835Interface_Init(EncoderInterface_t *interface, MT6835_t *hwEncoder) {
	interface->hardwareEncoder = hwEncoder;
	interface->GetEncoderSensorCount = &GetEncoderSensorCount;
	interface->GetEncoderSensorAbsCount = &GetEncoderSensorAbsCount;

}

static int GetEncoderSensorCount(EncoderInterface_t *interface) {
	return MT6835_GetABCount((MT6835_t *)interface->hardwareEncoder);
}

static int GetEncoderSensorAbsCount(EncoderInterface_t *interface) {
	return MT6835_GetABCount((MT6835_t *)interface->hardwareEncoder) %
			MT6835_AB_COUNT_PER_REV;
}
