/*
 * ads1256_interface.h
 *
 *  Created on: Dec 20, 2024
 *      Author: Jennyston
 */

#ifndef INC_DEVICES_ADS1256_INTERFACE_H_
#define INC_DEVICES_ADS1256_INTERFACE_H_

#include "ads1256.h"
#include "analog_sensor.h"

void ADS1256InterfaceInit(ADCInterface_t *interface,
		ADS1256_t *adc);

#endif /* INC_DEVICES_ADS1256_INTERFACE_H_ */
