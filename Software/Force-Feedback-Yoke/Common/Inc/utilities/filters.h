/*
 * filters.h
 *
 *  Created on: Dec 22, 2024
 *      Author: Jennyston
 */

#ifndef INC_UTILITIES_FILTERS_H_
#define INC_UTILITIES_FILTERS_H_

typedef struct {
	int *buffer;
	int len;
	int out;
} MedianFilter_t;

typedef struct {
	float beta;
	int in;
	int out;
}HighPass_t;

typedef struct {
	float alpha;
	float in;
	float out;
} LowPass_t;

typedef struct {
	int accumulator;
	int index;
	int *buffer;
	int len;
}MovingAvg_t;

void MedianFilter_Init(MedianFilter_t *medianFilter, int medianBuffer[],
		int lengthInBytes);
int MedianFilter_Update(MedianFilter_t *medianFilter, const int data[],
		int lengthInBytes);

void HighPassFilter_Init(HighPass_t *params, float beta);
void HighPassFilter_SetBeta(HighPass_t *params, float beta);
int HighPassFilter_Update(HighPass_t *params, int in);

void LowPassFilter_Init(LowPass_t *params, float alpha);
void LowPassFilter_SetAlpha(LowPass_t *params, float alpha);
float LowPassFilter_Update(LowPass_t *params, float in);
void LowPassFilter_Reset(LowPass_t *params);

void MovingAvg_Init(MovingAvg_t *params, int buffer[], int len);
void MovingAvg_Add(MovingAvg_t *params, int value);
int MovingAvg_Calc(MovingAvg_t *params);
float MovingAvg_CalcF(MovingAvg_t *params);

#endif /* INC_UTILITIES_FILTERS_H_ */
