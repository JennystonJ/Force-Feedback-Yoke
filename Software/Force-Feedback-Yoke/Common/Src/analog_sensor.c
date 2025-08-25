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

	analogSensor->lastValue = 0;
	analogSensor->lastValueDifferential = 0;
	analogSensor->lastReturnedValue = 0;

	analogSensor->calibrating = false;
	analogSensor->calibrateUpdateFlag = false;
}

void AnalogSensor_SetDifferential(AnalogSensor_t *analogSensor,
		unsigned int channelN) {
	analogSensor->channelN = channelN;
	analogSensor->differential = true;
}

void AnalogSensor_SetOffset(AnalogSensor_t *analogSensor, int offset) {
	analogSensor->offset = offset;
}

int AnalogSensor_GetValue(AnalogSensor_t *analogSensor) {
	if(analogSensor->differential) {
		analogSensor->lastValueDifferential = analogSensor->interface.
				ADCReadChannel(&analogSensor->interface,
						analogSensor->channelN);
	}

	analogSensor->lastValue = analogSensor->interface.ADCReadChannel(
			&analogSensor->interface, analogSensor->channel);

	analogSensor->lastReturnedValue = (int)analogSensor->lastValue -
			(int)analogSensor->lastValueDifferential + analogSensor->offset;
	return analogSensor->lastReturnedValue;
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

void AnalogSensor_CalibrateZeroOffset(AnalogSensor_t *analogSensor,
		unsigned int numSamples) {

	unsigned int sampleCount = 0;
	analogSensor->offset = 0;
	int64_t sampleAccumulator = 0;

	analogSensor->calibrating = true;
	while(sampleCount < numSamples) {
		// Wait for new sample to be ready
		while(!analogSensor->calibrateUpdateFlag) {}

		// Add sample to accumulator
		sampleAccumulator += (int64_t)AnalogSensor_GetValue(analogSensor);

		// Reset flag and update sample count
		analogSensor->calibrateUpdateFlag = false;
		sampleCount++;
	}

	// Calculate average, negate, then set to offset
	analogSensor->offset = (int)(-sampleAccumulator/(int)numSamples);

	analogSensor->calibrating = false;
}

void AnalogSensor_Update(AnalogSensor_t *analogSensor) {
	if(analogSensor->calibrating) {
		analogSensor->calibrateUpdateFlag = true;
	}
}
