/*
 * load_cell.c
 *
 *  Created on: Nov 22, 2024
 *      Author: Jennyston
 */

#include "load_cell.h"

void LoadCell_Init(LoadCell_t *loadCell, AnalogSensor_t *analogSensor) {
	loadCell->analogSensor = analogSensor;
	loadCell->conversionConstant = 1;
	loadCell->offset = 0;
	loadCell->lastReading = 0;

	CircularBuffer_Init(&loadCell->circularBuffer, loadCell->circularBufferData,
			sizeof(loadCell->circularBufferData));
	MedianFilter_Init(&loadCell->medianFilter, loadCell->medianBuffer,
			sizeof(loadCell->medianBuffer));

	LowPassFilter_Init(&loadCell->lpf, 0.1);
}

float LoadCell_GetValue(LoadCell_t *loadCell) {
//	loadCell->lastReading = AnalogSensorReadChannel(loadCell->analogSensor,
//			loadCell->channel) *
//			loadCell->conversionConstant + loadCell->offset;
	loadCell->lastReading = loadCell->lpfResult *
				loadCell->conversionConstant + loadCell->offset;
	return loadCell->lastReading;
}

void LoadCell_SetLowPassAlpha(LoadCell_t *loadCell, float alpha) {
	LowPassFilter_SetAlpha(&loadCell->lpf, alpha);
}

void LoadCell_RunCalibration(LoadCell_t *loadCell, unsigned int numSamples) {
	AnalogSensor_CalibrateZeroOffset(loadCell->analogSensor, numSamples);
}

void LoadCell_Update(LoadCell_t *loadCell) {
	AnalogSensor_Update(loadCell->analogSensor);

	CircularBuffer_Append(&loadCell->circularBuffer, AnalogSensor_GetValue(
			loadCell->analogSensor));
	int medianReading = MedianFilter_Update(&loadCell->medianFilter,
			loadCell->circularBufferData,
			sizeof(loadCell->circularBufferData));
	loadCell->lpfResult = LowPassFilter_Update(&loadCell->lpf, medianReading);
}

void LoadCell_SetOffset(LoadCell_t *loadCell, float offset) {
	loadCell->offset = offset;
}

void LoadCell_SetConversionConstant(LoadCell_t *loadCell,
		float converstionConstant) {
	loadCell->conversionConstant = converstionConstant;
}
