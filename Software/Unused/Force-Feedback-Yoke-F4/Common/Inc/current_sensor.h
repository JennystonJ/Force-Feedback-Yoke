/*
 * current_sensor.h
 *
 *  Created on: Nov 8, 2024
 *      Author: Jennyston
 */

#ifndef INC_CURRENT_SENSOR_H_
#define INC_CURRENT_SENSOR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "analog_sensor.h"
#include <stdbool.h>
#include "utilities/filters.h"

typedef struct CurrentSensorInterface CurrentSensorInterface_t;

struct CurrentSensorInterface {
	void *hardwareCurrentSensor;
	float (*CurrentSensorGetCurrent)(CurrentSensorInterface_t *currentSensor);
};

typedef struct CurrentSensor CurrentSensor_t;

struct CurrentSensor {
	AnalogSensor_t *sensor;
	unsigned int channel;
	float offset;
	float conversionConstant;
	float lastReading;
	LowPass_t lpfCurrent;
	bool calibration;
	int calibrationCycle;

	void(*calibrationCompleteCallback)(CurrentSensor_t *);
};

void CurrentSensorInit(CurrentSensor_t *currentSensor,
		AnalogSensor_t *analogSensor, unsigned int channel);
float CurrentSensorGetValue(CurrentSensor_t *currentSensor);
void CurrentSensorUpdate(CurrentSensor_t *currentSensor);
void CurrentSensorSetOffset(CurrentSensor_t *currentSensor, float offset);
void CurrentSensorSetConversionConstant(CurrentSensor_t *currentSensor,
		float converstionConstant);
void CurrentSensorStartCalibration(CurrentSensor_t *currentSensor);
void CurrentSensorCalibrationUpdate(CurrentSensor_t *currentSensor);
void CurrentSensorRegisterCalibrationCallback(CurrentSensor_t *currentSensor,
		void(*calibrationComplete)(CurrentSensor_t *));
bool CurrentSensorIsCalibrating(CurrentSensor_t *currentSensor);

#ifdef __cplusplus
}
#endif

#endif /* INC_CURRENT_SENSOR_H_ */
