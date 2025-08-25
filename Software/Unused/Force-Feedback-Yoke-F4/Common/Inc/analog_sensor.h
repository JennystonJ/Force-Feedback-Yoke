/*
 * analog_sensor.h
 *
 *  Created on: Nov 22, 2024
 *      Author: Jennyston
 */

#ifndef INC_ANALOG_SENSOR_H_
#define INC_ANALOG_SENSOR_H_

typedef struct AnalogSensorInterface AnalogSensorInterface_t;

struct AnalogSensorInterface {
	void *hardwareAnalogSensor;
	float (*AnalogSensorReadChannel)(AnalogSensorInterface_t *interface,
			unsigned int channel);
};

typedef struct AnalogSensor {
	AnalogSensorInterface_t interface;
} AnalogSensor_t;

void AnalogSensorInit(AnalogSensor_t *analogSensor,
		AnalogSensorInterface_t interface);
float AnalogSensorReadChannel(AnalogSensor_t *analogSensor,
		unsigned int channel);

#endif /* INC_ANALOG_SENSOR_H_ */
