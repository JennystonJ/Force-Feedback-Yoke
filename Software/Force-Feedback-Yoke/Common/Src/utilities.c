/*
 * utilities.c
 *
 *  Created on: May 19, 2023
 *      Author: Jennyston
 */

#include "utilities.h"

int32_t Constrain(int32_t value, int32_t min, int32_t max) {
	if(value < min) {
		return min;
	}
	else if(value > max) {
		return max;
	}
	else {
		return value;
	}
}

float ConstrainFloat(float value, float min, float max) {
	if(value < min) {
		return min;
	}
	else if(value > max) {
		return max;
	}
	else {
		return value;
	}
}

int32_t UnwrapAtThreshold16(uint16_t currentCount, uint16_t newCount,
		uint16_t threshold) {

	//find change in count
	int32_t deltaCount = (int32_t)newCount - currentCount;

	//new count did not wrap
	if(Abs(deltaCount) < threshold) {
		return newCount;
	}
	else {
		//new count underflow
		if(currentCount < newCount) {
			return -(0xFFFF + (int32_t)currentCount - newCount + 1);
		}
		//new count overflow
		else {
			return 0xFFFF - (int32_t)currentCount + newCount + 1;
		}
	}
}

int32_t Abs(int32_t x) {
	return x > 0 ? x : -x;
}

