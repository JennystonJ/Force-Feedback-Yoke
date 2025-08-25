/*
 * as5048a_interface.c
 *
 *  Created on: Apr 21, 2025
 *      Author: Jennyston
 */

#include "devices/as5048a_interface.h"
#include "devices/as5048a.h"

// Private function prototypes
static int GetEncoderSensorCount(EncoderInterface_t *interface);

void AS5048AInterfaceInit(EncoderInterface_t *interface, AS5048A_t *hwEncoder) {
	interface->hardwareEncoder = hwEncoder;
	interface->GetEncoderSensorCount = &GetEncoderSensorCount;
}

static int GetEncoderSensorCount(EncoderInterface_t *interface) {
	return AS5048AGetAngle((AS5048A_t *)interface->hardwareEncoder);
}
