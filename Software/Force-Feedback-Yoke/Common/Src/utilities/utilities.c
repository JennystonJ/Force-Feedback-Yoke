/*
 * utilities.c
 *
 *  Created on: May 19, 2023
 *      Author: Jennyston
 */

#include "utilities/utilities.h"

int32_t Map(int32_t in, int32_t inMin, int32_t inMax, int32_t outMin,
		int32_t outMax) {
	return (((int64_t)(in - inMin)*(outMax - outMin))/(inMax - inMin)) + outMin;
}

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

int32_t Abs(int32_t x) {
	return x > 0 ? x : -x;
}

int32_t Min(int32_t a, int32_t b) {
	return a < b ? a : b;
}

int32_t Max(int32_t a, int32_t b) {
	return a > b ? a : b;
}
