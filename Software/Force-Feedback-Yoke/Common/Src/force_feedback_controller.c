/*
 * force_feedback_controller.c
 *
 *  Created on: May 24, 2023
 *      Author: Jennyston
 */

#include "utilities/utilities.h"
#include "force_feedback_controller.h"
#include "delay.h"

void FFBInit(FFBController_t *ffb, Motor_t *motor, Encoder_t *encoder) {
	ffb->state = FFB_STOPPED;
	ffb->homingState = FFB_UNHOMED;

	ffb->motor = motor;
	ffb->encoder = encoder;

	ffb->constantGain = 0;
	ffb->periodicGain = 0;
	ffb->springGain = 10;
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

void FFBUpdate(FFBController_t *ffb, int deltaTimeUs) {
	switch(ffb->state){
	case FFB_STOPPED:
		MotorSetPower(ffb->motor, 0);
		break;
	case FFB_RUNNING:
		int motorPower = FFBCalcForces(ffb, EncoderGetCount(ffb->encoder),
				deltaTimeUs);
		//TODO: Remove: Scale down motor power and limit for testing and safety
		motorPower /= 2;
		motorPower = Constrain(motorPower, -MOTOR_POWER_MAX/2,
				MOTOR_POWER_MAX/2);

		MotorSetPower(ffb->motor, motorPower);
		break;
	case FFB_IDLE:
		break;
	default:
		// Should not reach here
		MotorSetPower(ffb->motor, 0);
		break;
	}
}

void FFBStop(FFBController_t *ffb) {
	ffb->state = FFB_STOPPED;
	MotorSetPower(ffb->motor, 0);
}

void FFBStart(FFBController_t *ffb) {
	ffb->state = FFB_RUNNING;
}

FFBControllerState_e FFBGetState(FFBController_t *ffb) {
	return ffb->state;
}

void FFBHome(FFBController_t *ffb) {
	ffb->state = FFB_IDLE;
	/* Find home start */
	// Record motor position
	int previousPosition = EncoderGetCount(ffb->encoder);
	// Reverse motor slowly
	MotorSetPower(ffb->motor, -FFB_CONTROL_HOME_POWER);
	// Wait for motor to move
	delayMs(300);
	// Wait until motor stops moving (hit end)
	int steadyCount = 0;
	do {
		int currentPosition = EncoderGetCount(ffb->encoder);
		if(Abs(currentPosition-previousPosition) < 10) {
			steadyCount++;
		}
		else {
			steadyCount = 0;
		}
		previousPosition = currentPosition;
		delayMs(10);
	} while(steadyCount < 25);
	// Record start position
	int startPosition = EncoderGetCount(ffb->encoder);
	// Stop motor
	MotorSetPower(ffb->motor, 0);
	delayMs(1000);


	/* Find home end */
	// Record motor position
	previousPosition = EncoderGetCount(ffb->encoder);
	// move motor forward slowly
	MotorSetPower(ffb->motor, FFB_CONTROL_HOME_POWER);
	// Wait for motor to move
	delayMs(300);
	// Wait until motor stops moving (hit end)
	steadyCount = 0;
	do {
		int currentPosition = EncoderGetCount(ffb->encoder);
		if(Abs(currentPosition-previousPosition) < 10) {
			steadyCount++;
		}
		else {
			steadyCount = 0;
		}
		previousPosition = currentPosition;
		delayMs(10);
	} while(steadyCount < 25);
	// Record end position
	int endPosition = EncoderGetCount(ffb->encoder);
	// Stop motor
	MotorSetPower(ffb->motor, 0);
	delayMs(1000);

	/* Calibrate center */
	int center = (endPosition - startPosition)/2;
	EncoderSetCount(ffb->encoder, center);

	/* Go to center */
	FFBSpringParam_t centerForce = {
			.minimumSpringForce = 0,
			.offset = 0,
			.strength = 0.2,
	};
	FFBSetSpringParams(ffb, centerForce);

	// Start
	FFBStart(ffb);

	// Wait for center to be reached
	while(Abs(EncoderGetCount(ffb->encoder) - center) > 50) {
		// Do nothing
	}

//	// Zero center position
//	EncoderResetCount(ffb->encoder);
//
//	FFBSpringParam_t newCenterForce = {
//			.minimumSpringForce = 0,
//			.offset = 0,
//			.strength = 0.35,
//	};
//	FFBSetSpringParams(ffb, newCenterForce);
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

