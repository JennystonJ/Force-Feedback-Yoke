/*
 * force_feedback_periodic.c
 *
 *  Created on: May 27, 2023
 *      Author: Jennyston
 */

#include "force_feedback/force_feedback_periodic.h"
#include <math.h>

#define PI 3.141592653589793f

void FFBPeriodicInit(FFBPeriodicForce_t *peri, float amplitude, float frequency,
		float offset) {
	// Initialize FFB periodic parameters
	peri->type = FFB_FORCE_TYPE_PERIODIC;
	peri->amplitude = amplitude;
	peri->frequency = frequency;
	peri->offset = offset;

	// Reset time to 0
	peri->time = 0;
}

float FFBPeriodicCalc(FFBPeriodicForce_t *peri, int dt) {

	// Update time
	peri->time += dt;

	// Calculate force
	float force = sinf(peri->frequency * (2*PI) * (peri->time/1000.0f)) *
			peri->amplitude + peri->offset;

	return force;
}
