/*
 * bts7960_current_sensor_interface.h
 *
 *  Created on: Nov 8, 2024
 *      Author: Jennyston
 */

#ifndef INC_DEVICES_BTS7960_CURRENT_SENSOR_INTERFACE_H_
#define INC_DEVICES_BTS7960_CURRENT_SENSOR_INTERFACE_H_

#include "devices/bts7960_current_sensor.h"
#include "current_sensor.h"

void BTS7960CurrentSensorInterfaceInit(CurrentSensorInterface_t *interface,
		BTS7960CurrentSensor_t *currentSensor);

#endif /* INC_DEVICES_BTS7960_CURRENT_SENSOR_INTERFACE_H_ */
