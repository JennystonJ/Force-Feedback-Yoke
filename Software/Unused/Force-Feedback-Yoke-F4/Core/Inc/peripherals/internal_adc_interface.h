/*
 * internal_adc_interface.h
 *
 *  Created on: Nov 22, 2024
 *      Author: Jennyston
 */

#ifndef INC_PERIPHERALS_INTERNAL_ADC_INTERFACE_H_
#define INC_PERIPHERALS_INTERNAL_ADC_INTERFACE_H_

#include "peripherals/internal_adc.h"
#include "analog_sensor.h"

void InternalADCInterfaceInit(AnalogSensorInterface_t *interface,
		InternalADC_t *adc);

#endif /* INC_PERIPHERALS_INTERNAL_ADC_INTERFACE_H_ */
