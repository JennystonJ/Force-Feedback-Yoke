/*
 * force_feedback_controller.c
 *
 *  Created on: May 24, 2023
 *      Author: Jennyston
 */

#include "utilities/utilities.h"
#include "force_feedback/force_feedback_controller.h"
#include "delay.h"
#include <math.h>
#include <string.h>


static float ConvertFFBToMotorVelocity(FFBController_t *ffb,
		float ffbVelocity);

static float ConvertMotorToFFBVelocity(FFBController_t *ffb,
		float motorVelocity);

static float ConvertEncoderCountsToFFBUnits(FFBController_t *ffb,
		int counts);

static void FFB_SetMotorCurrent(FFBController_t *ffb, float current);
static void FFB_SetMotorTorque(FFBController_t *ffb, float torque);
static void FFB_SetMotorVelocity(FFBController_t *ffb, float velocity);
static float FFB_GetMotorVelocity(FFBController_t *ffb);
static float FFB_GetMotorTorque(FFBController_t *ffb);

//void UpdateFFBSpeed(FFBController_t *ffb, float dt) {
//
//	int currentEncoderCount = FFB_GetRawAxisCount(ffb);
//
//	float currentSpeed = FFB_GetMotorVelocity(ffb);
//
//	// Calculate acceleration
//	ffb->acceleration = LowPassFilter_Update(&ffb->lpfAccel,
//			(currentSpeed - ffb->speed)/dt);
//
//	// Update previous variables
//	ffb->prevEncoderCount = currentEncoderCount;
//	ffb->speed = currentSpeed;
//}

void FFB_Init(FFBController_t *ffb) {
	ffb->constantGain = 1.0f;
	ffb->periodicGain = 0.0f;
	ffb->springGain = 1.0f;
	ffb->damperGain = 1.0f;

	ffb->gain = 1.0f;
//	ffb->minLock = -200000;
//	ffb->maxLock = 200000;
//	ffb->travelRange = 0;
//	ffb->lockPower = 1.0f;
//	ffb->lockKp = 0.000002f;
//	ffb->lockKd = 0.002f;
//	ffb->lockHysterisis = 8000;

//	ffb->prevEncoderCountAvg = FFB_GetRawAxisCount(ffb);
//	ffb->speed = 0;
//	LowPassFilter_Init(&ffb->lpfSpeed, 0.10f);
//	ffb->acceleration = 0;
//	LowPassFilter_Init(&ffb->lpfAccel, 0.875f);

//	ffb->speedDt = 0;

	// Initialize all forces to 0
	FFBForces_t forces = {
			.constantForce = 0,
			.springForce = 0,
			.damperForce = 0,
	};
	FFB_SetForces(ffb, forces);

//	FFB_SetConstant(ffb, 0);
////	FFBPeriodicInit(&ffb->param.periodic, 0, 0, 0);
//	FFB_SetSpring(ffb, 0);
//	FFB_SetDamper(ffb, 0);

//	ffb->assistEnable = false;
//	FFBAssist_Init(&ffb->ffbAssist);
}

//void FFB_SetLockGains(FFBController_t *ffb, float lockKp, float lockKd) {
//	ffb->lockKp = lockKp;
//	ffb->lockKd = lockKd;
//}
//
//void FFB_SetAssistEnable(FFBController_t *ffb, bool enabled) {
//	ffb->assistEnable = enabled;
//}
//
//FFBAssist_t *FFB_GetFFBAssist(FFBController_t *ffb) {
//	return &ffb->ffbAssist;
//}

void FFB_SetConstant(FFBController_t *ffb, float force) {
	ffb->forces.constantForce = force;
}

void FFB_SetSpring(FFBController_t *ffb, float spring) {
	ffb->forces.springForce= spring;
}

void FFB_SetDamper(FFBController_t *ffb, float damperStrength) {
	ffb->forces.damperForce = damperStrength;
}

void FFB_SetForces(FFBController_t *ffb, FFBForces_t forces) {
	ffb->forces = forces;
}

//void FFB_SetHomeCenterForces(FFBController_t *ffb, FFBForces_t homeCenterForces) {
//	ffb->homeCenterForce = homeCenterForces;
//}

float FFB_Update(FFBController_t *ffb, const AxisKinematics_t *in,
		float deltaTime) {

	// Calculate force output from each force type
	float constantForce = FFB_CalcConstantForce(ffb->constantGain,
			ffb->forces.constantForce);
	float springForce = FFB_CalcSpringForce(ffb->springGain, in->position,
			ffb->forces.springForce);
	float damperForce = FFB_CalcDamperForce(ffb->damperGain, ffb->forces.damperForce,
			in->velocity);

	// Calculate net force
	ffb->forceOut = ffb->gain * (constantForce + springForce + damperForce);

	return ffb->forceOut;

/*
		float constantForce = FFB_CalcConstantForce(ffb->constantGain,
				ffb->forces.constantForce);

		// TODO: Implement periodic force type
		float periodicForce = 0.0f;
//		float periodicForce = FFBCalcPeriodicForce(ffb->periodicGain,
//				&ffb->param.periodic, deltaTime);

		float springForce = FFB_CalcSpringForce(ffb->springGain, in->position,
				ffb->forces.springForce);

		float damperForce = FFB_CalcDamperForce(ffb->damperGain,
				ffb->forces.damperForce, in->velocity);


		// Assist force gain is independent to prevent runaway
		float force = ffb->gain *
				(constantForce + periodicForce + springForce + damperForce);

		// Update force output from main forces
		ffb->forceOut = force;

		if(ffb->assistEnable) {

			force += FFBAssist_Calc(&ffb->ffbAssist,
					in->userTorque,
					in->motorTorque,
					in->velocity, in->acceleration, deltaTime);
		}

		// Check if axis is outside lock range
		float lockDampening = 0.0f;
		if(in->position > ffb->minLock + ffb->lockHysterisis) {
			ffb->minLockReached = false;
		}
		else if(in->position < ffb->minLock) {
			ffb->minLockReached = true;
			lockDampening = ffb->lockKd * in->velocity;
		}
		else {
			lockDampening = ffb->lockKd * in->velocity;
			return fmaxf(force, 0) - lockDampening ;
		}

		if(in->position < ffb->maxLock - ffb->lockHysterisis) {
			ffb->maxLockReached = false;
		}
		else if(in->position > ffb->maxLock) {
			ffb->maxLockReached = true;
			lockDampening = ffb->lockKd * in->velocity;
		}
		else {
			lockDampening = ffb->lockKd * in->velocity;
			return fminf(force, 0) - lockDampening;
		}

		if(ffb->minLockReached) {
			return fmaxf(fmaxf(force, 0) + ffb->lockKp *
					powf(ffb->minLock - in->position, 2.0f),
					0) - lockDampening;
		}
		else if (ffb->maxLockReached) {
			return fminf(fminf(force, 0) -
					ffb->lockKp * powf(ffb->maxLock - in->position, 2.0f),
					0) - lockDampening;
		}
		else {
			return force - lockDampening;
		}
		*/
}


//void FFB_SetControlRange(FFBController_t *ffb, int min, int max) {
//	ffb->minLock = min;
//	ffb->maxLock = max;
//}
//
//int FFB_GetMinControlRange(FFBController_t *ffb) {
//	return ffb->minLock;
//}
//
//int FFB_GetMaxControlRange(FFBController_t *ffb) {
//	return ffb->maxLock;
//}
//
//int FFB_GetTravelRange(FFBController_t *ffb) {
//	return ffb->travelRange;
//}

//void FFB_Home(FFBController_t *ffb) {
//
//	// Save FFB state
//	FFBControllerState_e prevState = FFB_GetState(ffb);
//
//	ffb->state = FFB_IDLE;
//
//	// Save current limit setting
//	float motorPrevCurrentLimit = Motor_GetCurrentLimit(ffb->motor);
//
//	Motor_SetCurrentLimit(ffb->motor, FFB_CONTROL_HOME_CURRENT_LIMIT);
//
//	Motor_SetEnable(ffb->motor, true);
//	/* Find home start */
//	// Record motor position
//	int previousPosition = FFB_GetRawAxisCount(ffb);
//	// Reverse motor
//	FFB_SetMotorVelocity(ffb,
//			ConvertFFBToMotorVelocity(ffb, -FFB_CONTROL_HOME_VELOCITY));
//	delayMs(200);
//	// Wait until motor stops moving (hit end)
//	int steadyCount = 0;
//	do {
//		int currentPosition = FFB_GetRawAxisCount(ffb);
//		if(Abs(currentPosition-previousPosition) < 10) {
//			steadyCount++;
//		}
//		else {
//			steadyCount = 0;
//		}
//		previousPosition = currentPosition;
//		delayMs(10);
//	} while(steadyCount < 25);
//	// Record start position
//	int startPosition = FFB_GetRawAxisCount(ffb);
//	// Stop motor
//	FFB_SetMotorCurrent(ffb, 0);
//	delayMs(1000);
//
//
//	/* Find home end */
//	// Record motor position
//	previousPosition = FFB_GetRawAxisCount(ffb);
//
//	// Move motor forward
//	FFB_SetMotorVelocity(ffb,
//			ConvertFFBToMotorVelocity(ffb, FFB_CONTROL_HOME_VELOCITY));
//	delayMs(200);
//	// Wait until motor stops moving (hit end)
//	steadyCount = 0;
//	do {
//		int currentPosition = FFB_GetRawAxisCount(ffb);
//		if(Abs(currentPosition-previousPosition) < 10) {
//			steadyCount++;
//		}
//		else {
//			steadyCount = 0;
//		}
//		previousPosition = currentPosition;
//		delayMs(10);
//	} while(steadyCount < 25);
//	// Record end position
//	int endPosition = FFB_GetRawAxisCount(ffb);
//	// Stop motor
//	FFB_SetMotorCurrent(ffb, 0);
//	delayMs(1000);
//
//	if(endPosition < startPosition) {
//		// Error
//	}
//
//	/* Record travel range */
//	ffb->travelRange = endPosition - startPosition;
//
//	/* Calibrate center */
//	int center = (endPosition - startPosition)/2;
//	FFB_SetAxisCount(ffb, center);
//	ffb->prevEncoderCountAvg = 0;
//
//	/* Go to center */
//	FFB_SetMotorVelocity(ffb,
//			ConvertFFBToMotorVelocity(ffb, -FFB_CONTROL_HOME_VELOCITY));
//
//	// Start
////	FFBStart(ffb);
//
//	// Wait for center to be reached
//	while(Abs(FFB_GetRawAxisCount(ffb)) > 5000) {
//		delayMs(10);
//	}
//
//	delayMs(500);
//
//	FFB_ResetForces(ffb);
//
//	// Restore current limit
//	Motor_SetCurrentLimit(ffb->motor, motorPrevCurrentLimit);
//	// Return to previous state
//	if(prevState == FFB_RUNNING) {
//		FFB_Start(ffb);
//	}
//	else {
//		FFB_Stop(ffb);
//	}
//}

void FFB_ResetForces(FFBController_t *ffb) {
	// Clear all forces
	memset(&ffb->forces, 0, sizeof(ffb->forces));
}

float FFB_CalcConstantForce(float gain, float amount) {
	return gain * amount;
}

float FFB_CalcPeriodicForce(float gain, FFBPeriodicForce_t *periodic,
		float deltaTime) {
	return gain *
			FFBPeriodicCalc(periodic, deltaTime);
}

float FFB_CalcSpringForce(float gain, float measuredPosition,
		float springForce) {

	float constrainedStrength = ConstrainFloat(
			springForce, -1.0f, 1.0f);

	float force = gain * -measuredPosition * constrainedStrength;
	return force;
}

float FFB_CalcDamperForce(float gain, float magnitude, float velocity) {
	float force = gain * magnitude * -velocity;
	return force;
}

