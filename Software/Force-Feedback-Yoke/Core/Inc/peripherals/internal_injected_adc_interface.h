/*
 * internal_injected_adc_interface.h
 *
 *  Created on: Nov 22, 2024
 *      Author: Jennyston
 */

#ifndef INC_PERIPHERALS_INTERNAL_INJECTED_ADC_INTERFACE_H_
#define INC_PERIPHERALS_INTERNAL_INJECTED_ADC_INTERFACE_H_

#include <analog_sensor.h>
#include <peripherals/internal_injected_adc.h>

void InternalInjectedADCInterface_Init(ADCInterface_t *interface,
		InternalInjectedADC_t *adc);

#endif /* INC_PERIPHERALS_INTERNAL_INJECTED_ADC_INTERFACE_H_ */
