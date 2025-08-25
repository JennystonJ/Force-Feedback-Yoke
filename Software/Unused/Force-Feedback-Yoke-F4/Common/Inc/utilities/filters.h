/*
 * filters.h
 *
 *  Created on: Dec 22, 2024
 *      Author: Jennyston
 */

#ifndef INC_UTILITIES_FILTERS_H_
#define INC_UTILITIES_FILTERS_H_

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

int MedianFilter(int buffer[], int len);
void HighPassFilterInit(HighPass_t *params, float beta);
void HighPassFilterSetBeta(HighPass_t *params, float beta);
int HighPassFilterUpdate(HighPass_t *params, int in);

void LowPassFilterInit(LowPass_t *params, float alpha);
void LowPassFilterSetAlpha(LowPass_t *params, float alpha);
float LowPassFilterUpdate(LowPass_t *params, float in);
void LowPassFilterReset(LowPass_t *params);

void MovingAvgInit(MovingAvg_t *params, int buffer[], int len);
void MovingAvgAdd(MovingAvg_t *params, int value);
int MovingAvgCalc(MovingAvg_t *params);
float MovingAvgCalcF(MovingAvg_t *params);

#endif /* INC_UTILITIES_FILTERS_H_ */
