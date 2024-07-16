/*
 * as5600_interface.c
 *
 *  Created on: Jul 13, 2024
 *      Author: Jennyston
 */

#include "devices/as5600_interface.h"
#include "devices/as5600.h"

// Private function prototypes
int GetEncoderSensorCount(EncoderInterface_t *interface);


void AS5600InterfaceInit(EncoderInterface_t *interface, AS5600_t *hwEncoder) {
	interface->hardwareEncoder = hwEncoder;
	interface->GetEncoderSensorCount = &GetEncoderSensorCount;
}

int GetEncoderSensorCount(EncoderInterface_t *interface) {
	return AS5600GetAngle((AS5600_t *)interface->hardwareEncoder);
}
