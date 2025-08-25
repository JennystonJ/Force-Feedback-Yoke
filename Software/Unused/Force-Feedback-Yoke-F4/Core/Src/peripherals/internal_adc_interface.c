/*
 * internal_adc_interface.c
 *
 *  Created on: Nov 22, 2024
 *      Author: Jennyston
 */

#include "peripherals/internal_adc_interface.h"

// Private function prototypes
static float AnalogSensorIReadChannel(AnalogSensorInterface_t *interface,
		unsigned int channel);

void InternalADCInterfaceInit(AnalogSensorInterface_t *interface,
		InternalADC_t *adc) {
	interface->hardwareAnalogSensor = adc;
	interface->AnalogSensorReadChannel = &AnalogSensorIReadChannel;
}

static float AnalogSensorIReadChannel(AnalogSensorInterface_t *interface,
		unsigned int channel) {
	return InternalADCReadChannel(
			(InternalADC_t *)interface->hardwareAnalogSensor, channel);
}
