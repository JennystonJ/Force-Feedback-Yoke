/*
 * analog_sensor.c
 *
 *  Created on: Nov 22, 2024
 *      Author: Jennyston
 */

#include <analog_sensor.h>
#include "delay.h"
#include <stdint.h>

void AnalogSensor_Init(AnalogSensor_t *analogSensor,
		ADCInterface_t interface, unsigned int channel,
		unsigned int maxCount) {
	analogSensor->interface = interface;
	analogSensor->channel = channel;
	analogSensor->differential = false;
	analogSensor->maxCount = maxCount;
	analogSensor->offset = 0;

	analogSensor->lastValueRaw = 0;
	analogSensor->lastValue = 0;
	analogSensor->lastValueDifferential = 0;

	// Calibration variables
	analogSensor->calState = ANALOG_SENSOR_CAL_READY;
	analogSensor->calSampleCount = 0;
	analogSensor->calSampleTarget = 0;
	analogSensor->calSampleAccumulator = 0;
}

void AnalogSensor_SetDifferential(AnalogSensor_t *analogSensor,
		unsigned int channelN) {
	analogSensor->channelN = channelN;
	analogSensor->differential = true;
}

void AnalogSensor_SetOffset(AnalogSensor_t *analogSensor, int offset) {
	analogSensor->offset = offset;
}

int AnalogSensor_GetRawValue(AnalogSensor_t *analogSensor) {
	if(analogSensor->differential) {
			analogSensor->lastValueDifferential = analogSensor->interface.
					ADCReadChannel(&analogSensor->interface,
							analogSensor->channelN);
		}

		analogSensor->lastValueRaw = analogSensor->interface.ADCReadChannel(
				&analogSensor->interface, analogSensor->channel) -
						(int)analogSensor->lastValueDifferential;
	return analogSensor->lastValueRaw;
}

int AnalogSensor_GetValue(AnalogSensor_t *analogSensor) {

	analogSensor->lastValue = AnalogSensor_GetRawValue(analogSensor) +
			analogSensor->offset;

	return analogSensor->lastValue;
}

unsigned int AnalogSensor_GetMaxCount(AnalogSensor_t *analogSensor) {
	return analogSensor->maxCount;
}

float AnalogSensor_GetVoltage(AnalogSensor_t *analogSensor) {
	return (float)AnalogSensor_GetValue(analogSensor)/analogSensor->maxCount *
			AnalogSensor_GetVref(analogSensor);
}

float AnalogSensor_GetVref(AnalogSensor_t *analogSensor) {
	return analogSensor->interface.ADCGetVref(
			&analogSensor->interface);
}

void AnalogSensor_StartCalibration(AnalogSensor_t *analogSensor,
		unsigned int numSamples) {
	analogSensor->calSampleTarget = numSamples;
	analogSensor->calSampleCount = 0;
	analogSensor->calSampleAccumulator = 0;
	// Start calibration
	analogSensor->calState = ANALOG_SENSOR_CAL_RUNNING;
}

void AnalogSensor_Update(AnalogSensor_t *analogSensor) {
	if(analogSensor->calState == ANALOG_SENSOR_CAL_RUNNING) {
		// Add sample to accumulator
		analogSensor->calSampleAccumulator +=
				(int64_t)AnalogSensor_GetRawValue(analogSensor);

		// Update remaining sample count
		analogSensor->calSampleCount++;

		if(analogSensor->calSampleCount >= analogSensor->calSampleTarget) {

			// Calculate average, negate, then set to offset
			analogSensor->offset = -(int)(analogSensor->calSampleAccumulator /
					analogSensor->calSampleCount);

			// Calibration done
			analogSensor->calState = ANALOG_SENSOR_CAL_DONE;
		}
	}
}

bool AnalogSensor_IsCalibrationDone(AnalogSensor_t *analogSensor) {
	return analogSensor->calState == ANALOG_SENSOR_CAL_DONE;
}
