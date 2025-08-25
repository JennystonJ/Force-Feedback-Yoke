/*
 * analog_current_sensor_interface.h
 *
 *  Created on: May 25, 2025
 *      Author: Jennyston
 */

#ifndef INC_DEVICES_ANALOG_CURRENT_SENSOR_INTERFACE_H_
#define INC_DEVICES_ANALOG_CURRENT_SENSOR_INTERFACE_H_

#include "current_sensor.h"
#include "analog_sensor.h"

void AnalogCurrentSensorInterfaceInit(
		AnalogCurrentSensorInterface_t *interface,
		AnalogSensor_t *sensor);

#endif /* INC_DEVICES_ANALOG_CURRENT_SENSOR_INTERFACE_H_ */
