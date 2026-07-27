/*
 * velocity_estimator.h
 *
 *  Created on: May 21, 2026
 *      Author: Jennyston
 */

#ifndef INC_VELOCITY_ESTIMATOR_H_
#define INC_VELOCITY_ESTIMATOR_H_

#include "encoder.h"

typedef struct VelocityEstimator {

	float blendSpeed;
	float velocity;
	float pulseVel;
	float countVel;


	float positionEstimate;
	float positionPredict;
	float velocityEstimate;
	float velocityPredict;

	float alpha;
	float beta;

	float preError;
	float preVelocity;

	float kP;
	float kI;
} VelocityEstimator_t;

void VelocityEstimator_Init(VelocityEstimator_t *ve, float currentPosition,
		float kP, float kI);
void VelocityEstimator_Update(VelocityEstimator_t *ve, float currentPosition,
		float deltaTime);
float VelocityEstimator_GetVelocity(VelocityEstimator_t *ve);

#endif /* INC_VELOCITY_ESTIMATOR_H_ */
