/*
 * filters.c
 *
 *  Created on: Dec 22, 2024
 *      Author: Jennyston
 */

#include "utilities/filters.h"
#include "utilities/utilities.h"

int MedianFilter(int buffer[], int len) {
	// Sort buffer
	for(int i = 0; i < len-1; i++) {
		// Find lowest number index in buffer
		int min = buffer[i];
		int minIndex = i;
		for(int j = i+1; j < len; j++) {
			if(buffer[j] < min) {
				min = buffer[j];
				minIndex = j;
			}
		}

		// Swap current index with minimum index
		int temp = buffer[minIndex];
		buffer[minIndex] = buffer[i];
		buffer[i] = temp;
	}

	// Number of elements is even, return average of middle values
	if(len % 2 == 0) {
		return (buffer[len/2 - 1] + buffer[len/2]) / 2;
	}
	// Number of elements is odd, return middle value
	else {
		return buffer[len/2];
	}
}

void HighPassFilterInit(HighPass_t *params, float beta) {
	HighPassFilterSetBeta(params, beta);
	params->in = 0;
	params->out = 0;
}

void HighPassFilterSetBeta(HighPass_t *params, float beta) {
	params->beta = ConstrainFloat(beta, 0.0f, 1.0f);
}

int HighPassFilterUpdate(HighPass_t *params, int in) {
	params->out = 0.5f * (2.0f - params->beta) * (in - params->in) +
			(1.0f - params->beta) * params->out;
	// Update filter input for next calculation
	params->in = in;

	return params->out;
}

void LowPassFilterInit(LowPass_t *params, float alpha) {
	params->alpha = alpha;
	params->in = 0;
	params->out = 0;
}

void LowPassFilterSetAlpha(LowPass_t *params, float alpha) {
	params->alpha = ConstrainFloat(alpha, 0.0f, 1.0f);
}

float LowPassFilterUpdate(LowPass_t *params, float in) {
	params->out = params->alpha * in + (1.0f - params->alpha) * params->out;

	// Update filter input
	params->in = in;
}

void LowPassFilterReset(LowPass_t *params) {
	params->in = 0;
	params->out = 0;
}

void MovingAvgInit(MovingAvg_t *params, int buffer[], int len) {
	params->accumulator = 0;
	params->index = 0;
	params->buffer = buffer;
	params->len = len;
}

void MovingAvgAdd(MovingAvg_t *params, int value) {
	// Subtract old value
	params->accumulator -= params->buffer[params->index];
	// Add new value
	params->accumulator += value;
	// Put new value in buffer
	params->buffer[params->index] = value;

	// Update index
	params->index = (params->index+1) % params->len;
}

int MovingAvgCalc(MovingAvg_t *params) {
	return params->accumulator / params->len;
}

float MovingAvgCalcF(MovingAvg_t *params) {
	return (float)params->accumulator / params->len;
}
