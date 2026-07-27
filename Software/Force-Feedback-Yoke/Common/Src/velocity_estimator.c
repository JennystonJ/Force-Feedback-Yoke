/*
 * velocity_estimator.c
 *
 *  Created on: May 21, 2026
 *      Author: Jennyston
 */

#include "velocity_estimator.h"
#include "utilities/utilities.h"
#include <math.h>

void VelocityEstimator_Init(VelocityEstimator_t *ve, float currentPosition,
		float kP, float kI) {

	ve->blendSpeed = 1;
	ve->countVel = 0;
	ve->pulseVel = 0;
	ve->velocity = 0;

	ve->kP = kP;
	ve->kI = kI;
	ve->preError = 0;
	ve->positionEstimate = currentPosition;
	ve->velocityEstimate = 0;


	// State extrapolation
	ve->positionPredict = currentPosition;
	ve->velocityPredict = 0.0f;
}

void VelocityEstimator_Update(VelocityEstimator_t *ve, float currentPosition,
		float deltaTime) {
//	int count = Encoder_GetCount(ve->encoder);
//	int pulseTime = Encoder_GetPulseTimeCount(ve->encoder);
//	if(pulseTime == 0){
//		ve->pulseVel = 0;
//	}
//	else {
//		ve->pulseVel = 1/(pulseTime * Encoder_GetPulseTickPeriod(ve->encoder));
//	}
//
//	ve->countVel = (count - ve->prevCount)/deltaTime;
//	float speed = fabsf(ve->countVel);
//
//	ve->alpha = speed / ve->blendSpeed;
//	ve->alpha = ConstrainFloat(ve->alpha, 0.0f, 1.0f);
//	ve->velocity = ve->alpha * ve->countVel + (1.0f - ve->alpha) * ve->pulseVel *
//			signf(ve->countVel);
//
//	// Update previous count for next update
//	ve->prevCount = count;

/*
	// Alpha - Beta filter

	float residual = currentPosition - ve->positionPredict;

	// State update for position
	ve->positionEstimate = ve->positionPredict + ve->alpha * residual;

	// State update for velocity
	ve->velocityEstimate = ve->velocityPredict + ve->beta * (residual/deltaTime);

	// State extrapolation
	ve->positionPredict = ve->positionEstimate + deltaTime * ve->velocityEstimate;
	ve->velocityPredict = ve->velocityEstimate;

	*/

	// PLL
	// Calculate tracking error
	float error = currentPosition - ve->positionEstimate;

	float deltaError = error - ve->preError;
	ve->preError = error;

	// Update velocity estimate
	ve->velocityEstimate += ve->kP * deltaError + ve->kI * deltaTime * error;

	// Update position estimate
	ve->positionEstimate += ve->velocityEstimate * deltaTime;
}

float VelocityEstimator_GetVelocity(VelocityEstimator_t *ve) {
	return ve->velocityEstimate;
}
