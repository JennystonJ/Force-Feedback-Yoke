/*
 * current_sensor.c
 *
 *  Created on: Jul 13, 2025
 *      Author: Jennyston
 */


#include "current_sensor.h"

void CurrentSensor_Init(CurrentSensor_t *currentSensor, AnalogSensor_t *sensor,
		float maxCurrent) {
	currentSensor->sensor = sensor;
	currentSensor->maxCurrent = maxCurrent;
	currentSensor->offset = 0.0f;
	currentSensor->reading = 0.0f;

	// Low pass filter is disabled unless alpha is changed (0.0)
	LowPassFilter_Init(&currentSensor->lpf, 0.0f);
}

void CurrentSensor_SetOffset(CurrentSensor_t *currentSensor, float offset) {
	currentSensor->offset = offset;
}

float CurrentSensor_GetValue(CurrentSensor_t *currentSensor) {
	return currentSensor->reading;
}

void CurrentSensor_Calibrate(CurrentSensor_t *currentSensor,
		unsigned int numSamples) {
	AnalogSensor_CalibrateZeroOffset(currentSensor->sensor, numSamples);
}

void CurrentSensor_Update(CurrentSensor_t *currentSensor, float deltaTimeMs) {
	AnalogSensor_Update(currentSensor->sensor);
	float rawReading = (float)AnalogSensor_GetValue(
			currentSensor->sensor) /
			(AnalogSensor_GetMaxCount(currentSensor->sensor)/2) *
			currentSensor->maxCurrent;
	currentSensor->reading = LowPassFilter_Update(
			&currentSensor->lpf, rawReading);
}

void CurrentSensor_SetLowPassAlpha(CurrentSensor_t *currentSensor,
		float alpha) {
	LowPassFilter_SetAlpha(&currentSensor->lpf, alpha);
}
