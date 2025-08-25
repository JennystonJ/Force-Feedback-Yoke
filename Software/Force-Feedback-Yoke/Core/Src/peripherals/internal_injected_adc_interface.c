/*
 * internal_adc_interface.c
 *
 *  Created on: Nov 22, 2024
 *      Author: Jennyston
 */

#include <peripherals/internal_injected_adc_interface.h>

// Private function prototypes
static unsigned int ADCIReadChannel(ADCInterface_t *interface,
		unsigned int channel);
static float ADCIGetVref(ADCInterface_t *interface);

void InternalInjectedADCInterface_Init(ADCInterface_t *interface,
		InternalInjectedADC_t *adc) {
	interface->hardwareADC = adc;
	interface->ADCReadChannel = &ADCIReadChannel;
	interface->ADCGetVref = &ADCIGetVref;
}

static unsigned int ADCIReadChannel(ADCInterface_t *interface,
		unsigned int channel) {
	return InternalInjectedADC_ReadValue(
			(InternalInjectedADC_t *)interface->hardwareADC,
			channel);
}

static float ADCIGetVref(ADCInterface_t *interface) {
	return InternalInjectedADC_GetVref(
			(InternalInjectedADC_t *)interface->hardwareADC);
}
