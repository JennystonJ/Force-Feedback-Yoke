/*
 * load_cell.h
 *
 *  Created on: Nov 22, 2024
 *      Author: Jennyston
 */

#ifndef INC_LOAD_CELL_H_
#define INC_LOAD_CELL_H_

#include "analog_sensor.h"
#include "utilities/filters.h"

typedef struct LoadCell {
	AnalogSensor_t *analogSensor;
	unsigned int channel;
	float offset;
	float conversionConstant;
	float lastReading;

	LowPass_t lpf;
	float lpfResult;
} LoadCell_t;

void LoadCellInit(LoadCell_t *loadCell, AnalogSensor_t *analogSensor,
		 unsigned int channel);
float LoadCellGetValue(LoadCell_t *loadCell);
void LoadCellSetOffset(LoadCell_t *loadCell, float offset);
void LoadCellSetConversionConstant(LoadCell_t *loadCell,
		float converstionCosntant);
void LoadCellUpdate(LoadCell_t *loadCell);

#endif /* INC_LOAD_CELL_H_ */
