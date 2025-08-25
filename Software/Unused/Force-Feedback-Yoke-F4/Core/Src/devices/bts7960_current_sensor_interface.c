/*
 * bts7960_current_sensor_interface.c
 *
 *  Created on: Nov 8, 2024
 *      Author: Jennyston
 */

#include "devices/bts7960_current_sensor_interface.h"

// Private function prototypes
float CurrentSensorIGetCurrent(CurrentSensorInterface_t *interface);

void BTS7960CurrentSensorInterfaceInit(CurrentSensorInterface_t *interface,
		BTS7960CurrentSensor_t *currentSensor) {
	interface->hardwareCurrentSensor = currentSensor;
	interface->CurrentSensorGetCurrent = &CurrentSensorIGetCurrent;
}

float CurrentSensorIGetCurrent(CurrentSensorInterface_t * interface) {
	return BTS7960CurrentSensorRead(
			(BTS7960CurrentSensor_t *)interface->hardwareCurrentSensor);
}
