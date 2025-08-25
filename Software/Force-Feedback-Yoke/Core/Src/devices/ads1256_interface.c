/*
 * ads1256_interface.c
 *
 *  Created on: Dec 20, 2024
 *      Author: Jennyston
 */

#include "devices/ads1256_interface.h"

#define ADS1256_MIN_COUNT (-8388608)

// Private function prototypes
static unsigned int ADCReadChannel(ADCInterface_t *interface,
		unsigned int channel);
static float ADCGetVref(ADCInterface_t *interface);

void ADS1256InterfaceInit(ADCInterface_t *interface,
		ADS1256_t *adc) {
	interface->hardwareADC = adc;
	interface->ADCReadChannel = &ADCReadChannel;
	interface->ADCGetVref = &ADCGetVref;
}

static unsigned int ADCReadChannel(ADCInterface_t *interface,
		unsigned int channel) {
	// TODO: Add multiple channel support
	return (unsigned int)(ADS1256_Read((ADS1256_t *)interface->hardwareADC) -
			ADS1256_MIN_COUNT);
}

static float ADCGetVref(ADCInterface_t *interface) {
	return ADS1256_GetVref((ADS1256_t *)interface->hardwareADC);
}
