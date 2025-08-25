/*
 * load_cell.h
 *
 *  Created on: Nov 22, 2024
 *      Author: Jennyston
 */

#ifndef INC_LOAD_CELL_H_
#define INC_LOAD_CELL_H_

#include <analog_sensor.h>
#include "utilities/filters.h"
#include "utilities/circular_buffer.h"

typedef struct LoadCell {
	AnalogSensor_t *analogSensor;
	float offset;
	float conversionConstant;
	float lastReading;

	CircularBuffer_t circularBuffer;
	int circularBufferData[5];
	MedianFilter_t medianFilter;
	int medianBuffer[5];

	LowPass_t lpf;
	float lpfResult;
} LoadCell_t;

void LoadCell_Init(LoadCell_t *loadCell, AnalogSensor_t *analogSensor);
float LoadCell_GetValue(LoadCell_t *loadCell);
void LoadCell_SetLowPassAlpha(LoadCell_t *loadCell, float alpha);
void LoadCell_SetOffset(LoadCell_t *loadCell, float offset);
void LoadCell_SetConversionConstant(LoadCell_t *loadCell,
		float converstionCosntant);
void LoadCell_RunCalibration(LoadCell_t *loadCell, unsigned int numSamples);
void LoadCell_Update(LoadCell_t *loadCell);

#endif /* INC_LOAD_CELL_H_ */
