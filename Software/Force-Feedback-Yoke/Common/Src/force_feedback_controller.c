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
	ffb->lockAngle = 90;

	// Initialize all forces to 0
	FFBSetConstantStrength(ffb, 0);
	FFBPeriodicInit(&ffb->param.periodic, 0, 0, 0);
	FFBSpringParam_t spring = {
			.offset = 0,
			.strength = 0,
			.minimumSpringForce = 0
	};
	FFBSetSpringParams(ffb, spring);
	FFBSetDamper(ffb, 0);
}

void FFBSetConstantStrength(FFBController_t *ffb, float constantStrength) {
	ffb->param.constantStrength = constantStrength;
}

void FFBSetPeriodicParams(FFBController_t *ffb, FFBPeriodicParam_t periodic) {
	ffb->param.periodic = periodic;
}

void FFBSetSpringParams(FFBController_t *ffb, FFBSpringParam_t spring) {
	ffb->param.spring = spring;
}

void FFBSetDamper(FFBController_t *ffb, float damperStrength) {
	ffb->param.damperStrength = damperStrength;
}

float FFBCalcForces(FFBController_t *ffb, float measuredPosition,
		int deltaTime) {
	float constantForce = FFBCalcConstantForce(ffb->constantGain,
			ffb->param.constantStrength);

	float periodicForce = FFBCalcPeriodicForce(ffb->periodicGain,
			&ffb->param.periodic, deltaTime);

	float springForce = FFBCalcSpringForce(ffb->springGain, measuredPosition,
			&ffb->param.spring);

	float damperForce = FFBCalcDamperForce(ffb->damperGain,
			ffb->param.damperStrength);

	return ffb->gain *
			(constantForce + periodicForce + springForce + damperForce);
}


float FFBCalcMotorTorque(FFBController_t *ffb, float motorCurrent) {
	return ffb->motorKtConstant * motorCurrent;
}

float FFBCalcConstantForce(float gain, float amount) {
	return gain * amount;
}

float FFBCalcPeriodicForce(float gain, FFBPeriodicParam_t *periodic,
		float deltaTime) {
	return gain *
			FFBPeriodicCalc(periodic, deltaTime);
}

float FFBCalcSpringForce(float gain, float measuredAngle,
		FFBSpringParam_t *springParam) {

	float constrainedStrength = ConstrainFloat(
			springParam->strength, -1.0f, 1.0f);

	float force = gain * (springParam->offset - measuredAngle) *
			constrainedStrength;

	//add/subtract minimum spring force based on force direction
	if(force < 0) {
		force -= springParam->minimumSpringForce;
	}
	else if (force > 0) {
		force += springParam->minimumSpringForce;
	}

	return force;
}

float FFBCalcDamperForce(float gain, float magnitude) {
	float force = gain * -magnitude;
	return force;
}

