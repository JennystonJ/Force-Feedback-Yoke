/*
 * ads1256_interface.c
 *
 *  Created on: Dec 20, 2024
 *      Author: Jennyston
 */

#include "devices/ads1256_interface.h"

// Private function prototypes
static float AnalogSensorIReadChannel(AnalogSensorInterface_t *interface,
		unsigned int channel);

void ADS1256InterfaceInit(AnalogSensorInterface_t *interface,
		ADS1256_t *adc) {
	interface->hardwareAnalogSensor = adc;
	interface->AnalogSensorReadChannel = &AnalogSensorIReadChannel;
}

static float AnalogSensorIReadChannel(AnalogSensorInterface_t *interface,
		unsigned int channel) {
	return ADS1256Read((ADS1256_t *)interface->hardwareAnalogSensor);
}
