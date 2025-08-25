/*
 * current_sensor.h
 *
 *  Created on: Jul 13, 2025
 *      Author: Jennyston
 */

#ifndef INC_CURRENT_SENSOR_H_
#define INC_CURRENT_SENSOR_H_

#include "analog_sensor.h"
#include "utilities/filters.h"

typedef struct CurrentSensor {
	AnalogSensor_t *sensor;
	float offset;
	float maxCurrent;
	float reading;

	LowPass_t lpf;
} CurrentSensor_t;

void CurrentSensor_Init(CurrentSensor_t *currentSensor, AnalogSensor_t *sensor,
		float maxCurrent);
void CurrentSensor_SetOffset(CurrentSensor_t *currentSensor, float offset);
float CurrentSensor_GetValue(CurrentSensor_t *currentSensor);
void CurrentSensor_Calibrate(CurrentSensor_t *currentSensor,
		unsigned int numSamples);
void CurrentSensor_SetLowPassAlpha(CurrentSensor_t *currentSensor, float alpha);
void CurrentSensor_Update(CurrentSensor_t *currentSensor, float deltaTimeMs);

#endif /* INC_CURRENT_SENSOR_H_ */
