/*
 * filters.c
 *
 *  Created on: Dec 22, 2024
 *      Author: Jennyston
 */

#include "utilities/filters.h"
#include "utilities/utilities.h"
#include <string.h>

void MedianFilter_Init(MedianFilter_t *medianFilter, int medianBuffer[],
		int lengthInBytes) {
	medianFilter->buffer = medianBuffer;
	medianFilter->len = lengthInBytes/sizeof(int);
	// Clear buffer
	memset(medianFilter->buffer, 0, lengthInBytes);
	medianFilter->out = 0;
}

int MedianFilter_Update(MedianFilter_t *medianFilter, const int data[],
		int lengthInBytes) {

	if(medianFilter->len < lengthInBytes/sizeof(int)) {
		// Error
		return 0;
	}

	// Sort data into buffer
	for(int i = 0; i < medianFilter->len-1; i++) {
		// Find lowest number index in data
		int min = data[i];
		for(int j = i+1; j < medianFilter->len; j++) {
			if(data[j] < min) {
				min = data[j];
			}
		}

		medianFilter->buffer[i] = min;
	}

	// Number of elements is even, return average of middle values
	if(medianFilter->len % 2 == 0) {
		medianFilter->out = (medianFilter->buffer[medianFilter->len/2 - 1] +
				medianFilter->buffer[medianFilter->len/2]) / 2;
	}
	// Number of elements is odd, return middle value
	else {
		medianFilter->out = medianFilter->buffer[medianFilter->len/2];
	}

	return medianFilter->out;
}

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

void HighPassFilter_Init(HighPass_t *params, float beta) {
	HighPassFilter_SetBeta(params, beta);
	params->in = 0;
	params->out = 0;
}

void HighPassFilter_SetBeta(HighPass_t *params, float beta) {
	params->beta = ConstrainFloat(beta, 0.0f, 1.0f);
}

int HighPassFilter_Update(HighPass_t *params, int in) {
	params->out = 0.5f * (2.0f - params->beta) * (in - params->in) +
			(1.0f - params->beta) * params->out;
	// Update filter input for next calculation
	params->in = in;

	return params->out;
}

void LowPassFilter_Init(LowPass_t *params, float alpha) {
	params->alpha = alpha;
	params->in = 0;
	params->out = 0;
}

void LowPassFilter_SetAlpha(LowPass_t *params, float alpha) {
	params->alpha = ConstrainFloat(alpha, 0.0f, 1.0f);
}

float LowPassFilter_Update(LowPass_t *params, float in) {
	params->out = params->alpha * params->out + (1.0f - params->alpha) * in;

	// Update filter input
	params->in = in;

	return params->out;
}

void LowPassFilter_Reset(LowPass_t *params) {
	params->in = 0;
	params->out = 0;
}

void MovingAvg_Init(MovingAvg_t *params, int buffer[], int len) {
	params->accumulator = 0;
	params->index = 0;
	params->buffer = buffer;
	params->len = len;
}

void MovingAvg_Add(MovingAvg_t *params, int value) {
	// Subtract old value
	params->accumulator -= params->buffer[params->index];
	// Add new value
	params->accumulator += value;
	// Put new value in buffer
	params->buffer[params->index] = value;

	// Update index
	params->index = (params->index+1) % params->len;
}

int MovingAvg_Calc(MovingAvg_t *params) {
	return params->accumulator / params->len;
}

float MovingAvg_CalcF(MovingAvg_t *params) {
	return (float)params->accumulator / params->len;
}
