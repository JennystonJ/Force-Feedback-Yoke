/*
 * force_feedback_controller.c
 *
 *  Created on: May 24, 2023
 *      Author: Jennyston
 */

#include "utilities/utilities.h"
#include "force_feedback_controller.h"

void FFBInit(FFBController_t *ffb) {
	ffb->constantGain = 0;
	ffb->periodicGain = 0;
	ffb->springGain = 165;
	ffb->damperGain = 2;

	ffb->gain = 1;
	ffb->motorKtConstant = 0.0265;
	ffb->minimumSpringForce = 0.01;
	ffb->lockAngle = 90;
}

float FFBComputeMotorTorque(FFBController_t *ffb, float motorCurrent) {
	return ffb->motorKtConstant * motorCurrent;
}

float FFBComputeConstantForce(FFBController_t *ffb, float amount) {
	return ffb->constantGain * amount;
}

float FFBComputeSpringForce(FFBController_t *ffb, float measuredAngle,
		float setPointAngle, float strength) {

	float constrainedStrength = ConstrainFloat(strength, -1.0f, 1.0f);

	float force = ffb->springGain * (setPointAngle - measuredAngle) *
			ffb->gain * constrainedStrength;

	//add/subtract minimum spring force based on force direction
	if(force < 0) {
		force -= ffb->minimumSpringForce;
	}
	else if (force > 0) {
		force += ffb->minimumSpringForce;
	}

	return force;
}

float FFBComputeDamperForce(FFBController_t *ffb, float magnitude) {
	float force = ffb->damperGain * -magnitude * ffb->gain;
	return force;
}

