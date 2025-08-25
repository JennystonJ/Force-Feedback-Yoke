/*
 * load_cell.c
 *
 *  Created on: Nov 22, 2024
 *      Author: Jennyston
 */

#include "load_cell.h"

void LoadCellInit(LoadCell_t *loadCell, AnalogSensor_t *analogSensor,
		 unsigned int channel) {
	loadCell->analogSensor = analogSensor;
	loadCell->channel = channel;
	loadCell->conversionConstant = 1;
	loadCell->offset = 0;
	loadCell->lastReading = 0;

	LowPassFilterInit(&loadCell->lpf, 0.99);
}

float LoadCellGetValue(LoadCell_t *loadCell) {
//	loadCell->lastReading = AnalogSensorReadChannel(loadCell->analogSensor,
//			loadCell->channel) *
//			loadCell->conversionConstant + loadCell->offset;
	loadCell->lastReading = loadCell->lpfResult *
				loadCell->conversionConstant + loadCell->offset;
	return loadCell->lastReading;
}

void LoadCellUpdate(LoadCell_t *loadCell) {
	loadCell->lpfResult = LowPassFilterUpdate(&loadCell->lpf,
			AnalogSensorReadChannel(loadCell->analogSensor,
			loadCell->channel));
}

void LoadCellSetOffset(LoadCell_t *loadCell, float offset) {
	loadCell->offset = offset;
}

void LoadCellSetConversionConstant(LoadCell_t *loadCell,
		float converstionConstant) {
	loadCell->conversionConstant = converstionConstant;
}
