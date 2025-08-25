/*
 * bts7960_current_sensor.c
 *
 *  Created on: Oct 31, 2024
 *      Author: Jennyston
 */

#include "devices/bts7960_current_sensor.h"

void BTS7960CurrentSensorInit(BTS7960CurrentSensor_t *currentSensor,
		ADC_HandleTypeDef *hadc,
		uint32_t chForwardRank, uint32_t chReverseRank,
		BTS7960_t *motorDriver) {
	currentSensor->hadc = hadc;

	currentSensor->motorDriver = motorDriver;

	currentSensor->chForwardRank = chForwardRank;
	currentSensor->chReverseRank = chReverseRank;

	currentSensor->forwardOffset = 0;
	currentSensor->reverseOffset = 0;
}

void BTS7960CurrentSensorStart(BTS7960CurrentSensor_t *currentSensor) {
	HAL_ADC_Start_DMA(currentSensor->hadc, (uint32_t *)currentSensor->buffer,
			CURRENT_SENSOR_BUFFER_SIZE);
}

void BTS7960CurrentSensorSetConvConstants(
		BTS7960CurrentSensor_t *currentSensor,
		float forwardConversionConstant, float reverseConversionConstant) {
	currentSensor->forwardConversionConstant = forwardConversionConstant;
	currentSensor->reverseConversionConstant = reverseConversionConstant;
}

//float BTS7960CurrentSensorGetConvConstant(
//		BTS7960CurrentSensor_t *currentSensor) {
//	return currentSensor->conversionConstant;
//}

void BTS7960CurrentSensorSetOffsets(BTS7960CurrentSensor_t *currentSensor,
		float forwardOffset, float reverseOffset) {
	currentSensor->forwardOffset = forwardOffset;
	currentSensor->reverseOffset = reverseOffset;
}

void BTS7960CurrentSensorCalibrate(BTS7960CurrentSensor_t *currentSensor) {

	// Reset offsets to avoid conflicts with calculations
	currentSensor->forwardOffset = 0;
	currentSensor->reverseOffset = 0;

	// Calculate average forward current
	double sum = 0;
	for(int i = 0; i < 1000; i++) {
		sum += BTS7960CurrentSensorReadForward(currentSensor);
		HAL_Delay(1);
	}
	double average = sum/1000;

	// Update forward current offset (negate)
	currentSensor->forwardOffset = -average;

	// Calculate average for reverse current
	sum = 0;
	for(int i = 0; i < 1000; i++) {
		sum += BTS7960CurrentSensorReadReverse(currentSensor);
	}
	average = sum/1000;

	// Update reverse current offset (negate)
	currentSensor->reverseOffset = -average;

}

float BTS7960CurrentSensorRead(BTS7960CurrentSensor_t *currentSensor) {

	if(BTS7960GetPower(currentSensor->motorDriver) < 0) {
		return -BTS7960CurrentSensorReadReverse(currentSensor);
	}
	else if(BTS7960GetPower(currentSensor->motorDriver) > 0) {
		return BTS7960CurrentSensorReadForward(currentSensor);
	}
	else {
		return 0;
	}

//	int reading = //(int)HAL_ADCEx_InjectedGetValue(currentSensor->hadc,
//			//currentSensor->chForwardRank) -
//			HAL_ADCEx_InjectedGetValue(currentSensor->hadc,
//					currentSensor->chReverseRank);
//	return (reading * currentSensor->conversionConstant) + currentSensor->offset;

//	int forwardSum = 0;
//	for(int i = 0; i < CURRENT_SENSOR_BUFFER_SIZE; i += 2) {
//		forwardSum += currentSensor->buffer[i];
//	}
//
//	int reverseSum = 0;
//	for(int i = 1; i < CURRENT_SENSOR_BUFFER_SIZE; i += 2) {
//		reverseSum += currentSensor->buffer[i];
//	}
//
//	float current = (-forwardSum * currentSensor->forwardConversionConstant +
//			reverseSum * currentSensor->reverseConversionConstant) /
//					CURRENT_SENSOR_NUM_AVG_SAMPLES + currentSensor->offset;

//	int sum = 0;
//	int motorPower = BTS7960GetPower(currentSensor->motorDriver);
//	int start = motorPower < 0 ? 1 : 0;
//	for(int i = start; i < CURRENT_SENSOR_BUFFER_SIZE; i += 2) {
//		sum += currentSensor->buffer[i];
//	}
//
//	float current = (float)sum/CURRENT_SENSOR_NUM_AVG_SAMPLES *
//			currentSensor->forwardConversionConstant +
//			currentSensor->offset;
//
//	if(motorPower < 0) {
//		current = -current;
//	}
//
//
//	return current;
//	return (float)sum/CURRENT_SENSOR_NUM_AVG_SAMPLES *
//			currentSensor->conversionConstant +
//			currentSensor->offset;
}

float BTS7960CurrentSensorReadForward(BTS7960CurrentSensor_t *currentSensor) {

	// Calculate average forward current
	int sum = 0;
	for(int i = 0; i < CURRENT_SENSOR_BUFFER_SIZE; i += 2) {
		sum += currentSensor->buffer[i];
	}

	float current = (sum * currentSensor->forwardConversionConstant) /
			CURRENT_SENSOR_NUM_AVG_SAMPLES + currentSensor->forwardOffset;

	return current;
}

float BTS7960CurrentSensorReadReverse(BTS7960CurrentSensor_t *currentSensor) {

	// Calculate average reverse current
	int sum = 0;
	for(int i = 1; i < CURRENT_SENSOR_BUFFER_SIZE; i += 2) {
		sum += currentSensor->buffer[i];
	}

	float current = (sum * currentSensor->reverseConversionConstant) /
			CURRENT_SENSOR_NUM_AVG_SAMPLES + currentSensor->reverseOffset;

	return current;
}
