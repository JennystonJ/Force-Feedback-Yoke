/*
 * force_feedback_periodic.c
 *
 *  Created on: May 27, 2023
 *      Author: Jennyston
 */

#include "force_feedback_periodic.h"
#include <math.h>

#define PI 3.141592653589793f

void FFBPeriodicInit(FFBPeriodic_t *peri, float amplitude, float frequency,
		float offset) {
	// Initialize FFB periodic parameters
	peri->amplitude = amplitude;
	peri->frequency = frequency;
	peri->offset = offset;
	peri->gain = 1.0f;

	// Reset time to 0
	peri->time = 0;
}

float CalcFFBPeriodic(FFBPeriodic_t *peri, int dt) {

	float force = sinf(peri->frequency * (2*PI) * (peri->time/1000.0f)) *
			peri->amplitude * peri->gain + peri->offset;
	peri->time += dt;

	return force;
}
