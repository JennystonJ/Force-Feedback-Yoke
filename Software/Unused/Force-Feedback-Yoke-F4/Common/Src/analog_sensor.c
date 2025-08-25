/*
 * analog_sensor.c
 *
 *  Created on: Nov 22, 2024
 *      Author: Jennyston
 */

#include "analog_sensor.h"

void AnalogSensorInit(AnalogSensor_t *analogSensor,
		AnalogSensorInterface_t interface) {
	analogSensor->interface = interface;
}

float AnalogSensorReadChannel(AnalogSensor_t *analogSensor,
		unsigned int channel) {
	return analogSensor->interface.AnalogSensorReadChannel(
			&analogSensor->interface, channel);
}
