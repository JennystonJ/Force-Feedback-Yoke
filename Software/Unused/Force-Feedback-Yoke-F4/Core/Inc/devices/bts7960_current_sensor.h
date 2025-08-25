/*
 * bts7960_current_sensor.h
 *
 *  Created on: Oct 31, 2024
 *      Author: Jennyston
 */

#ifndef INC_DEVICES_BTS7960_CURRENT_SENSOR_H_
#define INC_DEVICES_BTS7960_CURRENT_SENSOR_H_

#include <stm32f4xx.h>
#include <stdint.h>
#include "devices/bts7960.h"

#define CURRENT_SENSOR_NUM_AVG_SAMPLES 64
#define CURRENT_SENSOR_BUFFER_SIZE (CURRENT_SENSOR_NUM_AVG_SAMPLES*2)

typedef struct BTS7960CurrentSensor {
	ADC_HandleTypeDef *hadc;
	uint32_t chForwardRank;
	uint32_t chReverseRank;
	BTS7960_t *motorDriver;
	float forwardConversionConstant;
	float reverseConversionConstant;
	float forwardOffset;
	float reverseOffset;
	uint16_t buffer[CURRENT_SENSOR_BUFFER_SIZE];
} BTS7960CurrentSensor_t;

/*
 * Initializes BTS7960 current sensor structure.
 * parameter currentSensor: pointer to BTS7960 current sensor structure.
 * parameter hadc: pointer to ADC handle measuring BTS7960 current sense output.
 * parameter chForwardRank: injected channel rank for forward current.
 * parameter chReverseRank: injected channel rank for reverse current.
 */
void BTS7960CurrentSensorInit(BTS7960CurrentSensor_t *currentSensor,
		ADC_HandleTypeDef *hadc,
		uint32_t chForwardRank, uint32_t chReverseRank, BTS7960_t *motorDriver);

/*
 * Starts current sensor measurements.
 * parameter currentSensor: pointer to BTS7960 current sensor structure.
 */
void BTS7960CurrentSensorStart(BTS7960CurrentSensor_t *currentSensor);

/*
 * Assigns conversion constant used for current sensor calculations.
 * parameter currentSensor: pointer to BTS7960 current sensor structure.
 * parameter conversionConstant: constant in ADC steps per unit current.
 */
void BTS7960CurrentSensorSetConvConstants(BTS7960CurrentSensor_t *currentSensor,
		float forwardConversionConstant, float reverseConversionConstant);

/*
 * Obtains conversion constant used for current sensor calculations.
 * parameter currentSensor: pointer to BTS7960 current sensor structure.
 */
//float BTS7960CurrentSensorGetConvConstant(
//		BTS7960CurrentSensor_t *currentSensor);

void BTS7960CurrentSensorSetOffsets(BTS7960CurrentSensor_t *currentSensor,
		float forwardOffset, float reverseOffset);

/*
 * Sets current sensor offsets. Typically used when motor driver is shut off.
 * parameter currentSensor: pointer to BTS7960 current sensor structure.
 */
void BTS7960CurrentSensorCalibrate(BTS7960CurrentSensor_t *currentSensor);

/*
 * Reads current sensor value.
 * parameter currentSensor: pointer to BTS7960 current sensor structure.
 * returns: current in unit current (dependent on conversion constant unit).
 */
float BTS7960CurrentSensorRead(BTS7960CurrentSensor_t *currentSensor);

float BTS7960CurrentSensorReadForward(BTS7960CurrentSensor_t *currentSensor);

float BTS7960CurrentSensorReadReverse(BTS7960CurrentSensor_t *currentSensor);

#endif /* INC_DEVICES_BTS7960_CURRENT_SENSOR_H_ */
