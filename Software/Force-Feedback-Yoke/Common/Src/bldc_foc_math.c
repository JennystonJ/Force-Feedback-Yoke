/*
 * bldc_foc_math.c
 *
 *  Created on: Jul 8, 2025
 *      Author: Jennyston
 */

#include "bldc_foc_math.h"
#include <math.h>

#define _1_SQRT3 (0.57735026919f)
#define _SQRT3_2 (0.86602540378f)

ABCurrent_t FOCMath_CalcABCurrent(PhaseCurrents_t currents) {

	ABCurrent_t abCurrent;

	// Clarke transform (source: SimpleFOC)
	float mid = (currents.a + currents.b + currents.c)/3.0f;

    float a = currents.a - mid;
    float b = currents.b - mid;
    float c = currents.c - mid;

    abCurrent.alpha = a;
    abCurrent.beta = _SQRT3_2 * (b - c);

	return abCurrent;
}

DQCurrent_t FOCMath_CalcDQCurrent(ABCurrent_t abCurrent, float angleElec) {

	// Park transform
	DQCurrent_t dqCurrent;
	float cosResult = cosf(angleElec);
	float sinResult = sinf(angleElec);
	dqCurrent.d = abCurrent.alpha * cosResult + abCurrent.beta * sinResult;
	dqCurrent.q = abCurrent.beta * cosResult - abCurrent.alpha * sinResult;

	return dqCurrent;
}

PhaseVoltages_t FOCMath_CalcPhaseVoltages(float ud, float uq, float angleElec){

	float cosResult = cosf(angleElec);
	float sinResult = sinf(angleElec);

	// Inverse Park transform
	float uAlpha = ud * cosResult - uq * sinResult;
	float uBeta = ud * sinResult + uq * cosResult;

	PhaseVoltages_t voltages;
	// Inverse Clarke transform
	voltages.a = uAlpha;
	voltages.b = -0.5f * uAlpha + _SQRT3_2 * uBeta;
	voltages.c = -0.5f * uAlpha - _SQRT3_2 * uBeta;

	return voltages;
}

