	/*
 * current_sensor.c
 *
 *  Created on: Nov 8, 2024
 *      Author: Jennyston
 */

#include "current_sensor.h"
#include <stddef.h>
#include "utilities/filters.h"

void CurrentSensorInit(CurrentSensor_t *currentSensor,
		AnalogSensor_t *analogSensor, unsigned int channel) {
	currentSensor->channel = channel;
	currentSensor->sensor = analogSensor;

	currentSensor->offset = 0;
	currentSensor->conversionConstant = 1;
	currentSensor->lastReading = 0;

	LowPassFilterInit(&currentSensor->lpfCurrent, 0.001);

	currentSensor->calibration = false;
	currentSensor->calibrationCycle = 0;

	currentSensor->calibrationCompleteCallback = NULL;
}

float CurrentSensorGetValue(CurrentSensor_t *currentSensor) {
	return currentSensor->lastReading;
}

void CurrentSensorUpdate(CurrentSensor_t *currentSensor) {
	float newReading = -AnalogSensorReadChannel(
			currentSensor->sensor,
			currentSensor->channel) *
			currentSensor->conversionConstant + currentSensor->offset;
	currentSensor->lastReading =
			LowPassFilterUpdate(&currentSensor->lpfCurrent, newReading);
}

void CurrentSensorSetOffset(CurrentSensor_t *currentSensor, float offset) {
	currentSensor->offset = offset;
}

void CurrentSensorSetConversionConstant(CurrentSensor_t *currentSensor,
		float conversionConstant) {
	currentSensor->conversionConstant = conversionConstant;
}

void CurrentSensorStartCalibration(CurrentSensor_t *currentSensor) {
	currentSensor->calibration = true;
}

void CurrentSensorCalibrationUpdate(CurrentSensor_t *currentSensor) {
	if(currentSensor->calibration) {
		// Wait 2 update cycles
		currentSensor->calibrationCycle++;
		if (currentSensor->calibrationCycle == 2) {
			CurrentSensorSetOffset(currentSensor,
					AnalogSensorReadChannel(currentSensor->sensor,
							currentSensor->channel));
			currentSensor->calibrationCycle = 0;
			currentSensor->calibration = false;

			if(currentSensor->calibrationCompleteCallback != NULL) {
				currentSensor->calibrationCompleteCallback(currentSensor);
			}
		}
	}
}

void CurrentSensorRegisterCalibrationCallback(CurrentSensor_t *currentSensor,
		void(*calibrationComplete)(CurrentSensor_t *)) {
	currentSensor->calibrationCompleteCallback = calibrationComplete;
}

bool CurrentSensorIsCalibrating(CurrentSensor_t *currentSensor) {
	return currentSensor->calibration;
}
