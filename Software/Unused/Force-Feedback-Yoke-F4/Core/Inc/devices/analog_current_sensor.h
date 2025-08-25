/*
 * analog_current_sensor.h
 *
 *  Created on: May 25, 2025
 *      Author: Jennyston
 */

#ifndef INC_DEVICES_ANALOG_CURRENT_SENSOR_H_
#define INC_DEVICES_ANALOG_CURRENT_SENSOR_H_

#include "analog_sensor.h"

typedef struct AnalogCurrentSensor AnalogCurrentSensor_t;

struct AnalogCurrentSensor {
	unsigned int channel;
	AnalogSensor_t *sensor;
};

#endif /* INC_DEVICES_ANALOG_CURRENT_SENSOR_H_ */
