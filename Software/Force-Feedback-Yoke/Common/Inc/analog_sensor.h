/*
 * analog_sensor.h
 *
 *  Created on: Nov 22, 2024
 *      Author: Jennyston
 */

#ifndef INC_ANALOG_SENSOR_H_
#define INC_ANALOG_SENSOR_H_

#include <stdbool.h>
#include <stdint.h>

typedef struct ADCInterface ADCInterface_t;

struct ADCInterface {
	void *hardwareADC;
	unsigned int (*ADCReadChannel)(ADCInterface_t *interface,
			unsigned int channel);
	float (*ADCGetVref)(ADCInterface_t *interface);
};

typedef enum AnalogSensorCalState {
	ANALOG_SENSOR_CAL_READY,
	ANALOG_SENSOR_CAL_RUNNING,
	ANALOG_SENSOR_CAL_DONE,
} AnalogSensorCalState_e;

typedef struct AnalogSensor {
	ADCInterface_t interface;
	unsigned int channel;
	unsigned int maxCount;
	bool differential;
	unsigned int channelN;
	int offset;

	int lastValueRaw;
	int lastValue;
	unsigned int lastValueDifferential;

	AnalogSensorCalState_e calState;
	unsigned int calSampleCount;
	unsigned int calSampleTarget;
	int64_t calSampleAccumulator;
} AnalogSensor_t;

void AnalogSensor_Init(AnalogSensor_t *analogSensor,
		ADCInterface_t interface, unsigned int channel,
		unsigned int maxCount);
void AnalogSensor_SetDifferential(AnalogSensor_t *analogSensor,
		unsigned int channelN);
void AnalogSensor_SetOffset(AnalogSensor_t *analogSensor, int offset);
int AnalogSensor_GetValue(AnalogSensor_t *analogSensor);
unsigned int AnalogSensor_GetMaxCount(AnalogSensor_t *analogSensor);
float AnalogSensor_GetVoltage(AnalogSensor_t *analogSensor);
float AnalogSensor_GetVref(AnalogSensor_t *analogSensor);
void AnalogSensor_StartCalibration(AnalogSensor_t *analogSensor,
		unsigned int numSamples);
void AnalogSensor_Update(AnalogSensor_t *analogSensor);
bool AnalogSensor_IsCalibrationDone(AnalogSensor_t *analogSensor);

#endif /* INC_ANALOG_SENSOR_H_ */
