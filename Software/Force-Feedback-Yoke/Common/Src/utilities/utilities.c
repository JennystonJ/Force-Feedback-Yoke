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

float signf(float x) {
	if(x > 0.0f) {
		return 1.0f;
	}
	else if(x < 0.0f) {
		return -1.0f;
	}
	else {
		return 0.0f;
	}
}

int32_t Abs(int32_t x) {
	return x > 0 ? x : -x;
}

float AbsFloat(float x) {
	return x > 0 ? x : -x;
}

int32_t Min(int32_t a, int32_t b) {
	return a < b ? a : b;
}

int32_t Max(int32_t a, int32_t b) {
	return a > b ? a : b;
}

uint8_t CalcEvenParity(uint8_t *data, uint8_t len) {
	// Start with 0 since parity should be even
	int parityBit = 0;
	for(int i = 0; i < len; i++) {
		for(int bit = 0; bit < 8; bit++) {
			parityBit ^= (data[i] >> bit) & 0x01;
		}
	}

	return (uint8_t)parityBit;
}
