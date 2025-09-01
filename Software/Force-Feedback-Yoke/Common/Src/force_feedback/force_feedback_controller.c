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
static void FFB_SetMotorVelocity(FFBController_t *ffb, float velocity);
static float FFB_GetMotorVelocity(FFBController_t *ffb);
static float FFB_GetMotorTorque(FFBController_t *ffb);

void UpdateFFBSpeed(FFBController_t *ffb, float dt) {
	int currentEncoderCount = FFB_GetRawAxisCount(ffb);

//	float currentSpeed = LowPassFilterUpdate(&ffb->lpfSpeed,
//			(currentEncoderCount - ffb->prevEncoderCount)/dt);
	float currentSpeed = FFB_GetMotorVelocity(ffb);
	ffb->acceleration = LowPassFilter_Update(&ffb->lpfAccel,
			(currentSpeed - ffb->speed)/dt);

//	ffb->unitPerRev = 1.0f;

//	ffb->speedDt += dt;
//
//	// Check if required time for speed calculation has passed
//	if(ffb->speedDt >= FFB_AVG_SPEED_DT) {
//		ffb->speedDt -= FFB_AVG_SPEED_DT;
//
//		// Calculate new speed
//		int encoderReading = Encoder_GetCount(ffb->encoder);
//		ffb->speed = (encoderReading - ffb->prevEncoderCountAvg)/
//				(float)FFB_AVG_SPEED_DT;
//		ffb->prevEncoderCountAvg = encoderReading;
//	}

	// Update previous variables
	ffb->prevEncoderCount = currentEncoderCount;
	ffb->speed = currentSpeed;
}

void FFBInit(FFBController_t *ffb, Motor_t *motor, Encoder_t *encoder) {
	ffb->state = FFB_STOPPED;
	ffb->homingState = FFB_UNHOMED;

	ffb->motor = motor;
	ffb->encoder = encoder;
	ffb->loadCell = NULL;

	ffb->axisReverse = false;

	ffb->constantGain = 1.0f;
	ffb->periodicGain = 0.0f;
	ffb->springGain = 1.0f;
	ffb->damperGain = 1.0f;

	// Temporarily disable assist until better implementation
	ffb->assistMin = 200;
	ffb->assistGain = 0;//40000;

	ffb->gain = 10.0f;
	ffb->motorKtConstant = 0.0265;
	ffb->minLock = -200000;
	ffb->maxLock = 200000;
	ffb->travelRange = 0;
	ffb->lockPower = 1.0f;
	ffb->lockKp = 0.000002f;
	ffb->lockKd = 0.002f;
	ffb->lockHysterisis = 8000;

	ffb->prevEncoderCountAvg = FFB_GetRawAxisCount(ffb);
	ffb->speed = 0;
	LowPassFilter_Init(&ffb->lpfSpeed, 0.10f);
	ffb->acceleration = 0;
	LowPassFilter_Init(&ffb->lpfAccel, 0.875f);

	ffb->speedDt = 0;

	// Initialize all forces to 0
	FFBSetConstant(ffb, 0);
	FFBPeriodicInit(&ffb->param.periodic, 0, 0, 0);

	FFBSetSpring(ffb, 0);
	FFBSetDamper(ffb, 0);

	ffb->assistEnable = false;
	FFBAssist_Init(&ffb->ffbAssist);
}


void FFB_SetAxisReverse(FFBController_t *ffb, bool reverse) {
	ffb->axisReverse = reverse;
}

int FFB_GetRawAxisCount(FFBController_t *ffb) {
	return ffb->axisReverse ? -Encoder_GetCount(ffb->encoder) :
			Encoder_GetCount(ffb->encoder);
}

void FFB_SetAxisCount(FFBController_t *ffb, int count) {
	ffb->axisReverse ? Encoder_SetCount(ffb->encoder, -count) :
			Encoder_SetCount(ffb->encoder, count);
}

void FFBSetLoadCell(FFBController_t *ffb, LoadCell_t *loadCell) {
	ffb->loadCell = loadCell;
}

void FFB_SetLockGains(FFBController_t *ffb, float lockKp, float lockKd) {
	ffb->lockKp = lockKp;
	ffb->lockKd = lockKd;
}

void FFBSetAssistEnable(FFBController_t *ffb, bool enabled) {
	// Only enable assist if a load cell has been set
	ffb->assistEnable = enabled & (ffb->loadCell != NULL);
}

FFBAssist_t *FFB_GetFFBAssist(FFBController_t *ffb) {
	return &ffb->ffbAssist;
}

void FFBSetConstant(FFBController_t *ffb, float force) {
	ffb->forces.constantForce = force;
}

//void FFBSetPeriodicParams(FFBController_t *ffb, FFBPeriodicForce_t periodic) {
//	ffb->param.periodic = periodic;
//}
//
void FFBSetSpring(FFBController_t *ffb, float spring) {
	ffb->forces.springForce= spring;
}

void FFBSetDamper(FFBController_t *ffb, float damperStrength) {
	ffb->forces.damperForce = damperStrength;
}

void FFBSetForces(FFBController_t *ffb, FFBForces_t forces) {
	ffb->forces = forces;
}

void FFB_SetHomeCenterForces(FFBController_t *ffb, FFBForces_t homeCenterForces) {
	ffb->homeCenterForce = homeCenterForces;
}

float FFBCalcForces(FFBController_t *ffb, float measuredPosition,
		float deltaTime) {

//	// Check if axis is outside lock range
//	if(measuredPosition < ffb->minLock) {
//
//		return ffb->lockKp * powf(ffb->minLock - measuredPosition, 2.0f) -
//				ffb->lockKd * speed;
//	}
//	else if(measuredPosition > ffb->maxLock) {
//
//		return -(ffb->lockKp * powf(ffb->maxLock - measuredPosition, 2.0f) -
//				ffb->lockKd * speed);
//	}
//	// Axis is within lock range, perform calculations
//	else {

//		float constantForce = 0.0f;
//		float springForce = 0.0f;
//		float damperForce = 0.0f;
//		float periodicForce = 0.0f;
//		for(int i = 0; i < FFB_CONTROL_NUM_FORCES; i++) {
//			switch(ffb->forces[i].header.type) {
//				case FFB_FORCE_TYPE_CLEAR:
//					// Do nothing
//					break;
//				case FFB_FORCE_TYPE_CONSTANT:
//					constantForce += FFBCalcConstantForce(ffb->constantGain,
//							ffb->forces[i].constant.force);
//					break;
//				case FFB_FORCE_TYPE_SPRING:
//					springForce += FFBCalcSpringForce(ffb->springGain,
//							measuredPosition, &ffb->forces[i].spring);
//					break;
//				case FFB_FORCE_TYPE_DAMPER:
//					damperForce += FFBCalcDamperForce(ffb->damperGain,
//							ffb->forces[i].damper.strength);
//					break;
//				case FFB_FORCE_TYPE_PERIODIC:
//					periodicForce += FFBCalcPeriodicForce(ffb->periodicGain,
//							&ffb->forces[i].periodic, deltaTime);
//					break;
//				default:
//					// Invalid, do nothing
//					break;
//			}
//		}

		float constantForce = FFBCalcConstantForce(ffb->constantGain,
				ffb->forces.constantForce);

		float periodicForce = FFBCalcPeriodicForce(ffb->periodicGain,
				&ffb->param.periodic, deltaTime);

		float springForce = FFBCalcSpringForce(ffb->springGain,
				ConvertEncoderCountsToFFBUnits(ffb, measuredPosition),
				ffb->forces.springForce);

		float damperForce = FFBCalcDamperForce(ffb->damperGain,
				ffb->forces.damperForce, ffb->speed);

//		float assistForce = FFBCalcAssist(ffb->assistGain, ffb->assistMin,
//				ffb->speed);

//		// TODO: Remove to enable assist force
//		assistForce = 0;
//		ffb->loadCell = NULL;

		// Assist force gain is independent to prevent runaway
		float force = ffb->gain *
				(constantForce + periodicForce + springForce + damperForce); //+
//				assistForce;
		// Update force output from main forces
		ffb->forceOut = force;

		if(ffb->assistEnable) {

			force += FFBAssist_Calc(&ffb->ffbAssist,
					-LoadCell_GetValue(ffb->loadCell),
					FFB_GetMotorTorque(ffb),
					ffb->speed, ffb->acceleration, deltaTime);

//			float loadCellValue = LoadCellGetValue(ffb->loadCell);
//			if(loadCellValue > 100) {
//				force += ffb->assistMin + ffb->assistGain*loadCellValue;
//			}
//			else if(loadCellValue < -100) {
//				force = force - ffb->assistMin + ffb->assistGain*loadCellValue;
//			}
//			force -= speed*10000;
		}

		// Check if axis is outside lock range
		float lockDampening = 0.0f;
		if(measuredPosition > ffb->minLock + ffb->lockHysterisis) {
			ffb->minLockReached = false;
		}
		else if(measuredPosition < ffb->minLock) {
			ffb->minLockReached = true;
			lockDampening = ffb->lockKd * ffb->speed;
		}
		else {
			lockDampening = ffb->lockKd * ffb->speed;
			return fmaxf(force, 0) - lockDampening ;
		}

		if(measuredPosition < ffb->maxLock - ffb->lockHysterisis) {
			ffb->maxLockReached = false;
		}
		else if(measuredPosition > ffb->maxLock) {
			ffb->maxLockReached = true;
			lockDampening = ffb->lockKd * ffb->speed;
		}
		else {
			lockDampening = ffb->lockKd * ffb->speed;
			return fminf(force, 0) - lockDampening;
		}

		if(ffb->minLockReached) {
			return fmaxf(fmaxf(force, 0) + ffb->lockKp *
					powf(ffb->minLock - measuredPosition, 2.0f),
					0) - lockDampening;
		}
		else if (ffb->maxLockReached) {
			return fminf(fminf(force, 0) -
					ffb->lockKp * powf(ffb->maxLock - measuredPosition, 2.0f),
					0) - lockDampening;
		}
		else {
			return force - lockDampening;
		}

//	}
}

void FFBUpdate(FFBController_t *ffb, float deltaTimeMs) {
	UpdateFFBSpeed(ffb, deltaTimeMs);
	if(ffb->loadCell != NULL) {
		LoadCell_Update(ffb->loadCell);
	}

	switch(ffb->state){
	case FFB_STOPPED:
		break;
	case FFB_RUNNING:
		// TODO: constrain to bus voltage
		float motorPower =
				ConstrainFloat(FFBCalcForces(ffb,
						FFB_GetRawAxisCount(ffb),
						deltaTimeMs), -10.0f,
						10.0f);
		FFB_SetMotorCurrent(ffb, motorPower);
		break;
	case FFB_IDLE:
		break;
	default:
		// Should not reach here
		Motor_SetVoltage(ffb->motor, 0);
		break;
	}
}

void FFBStop(FFBController_t *ffb) {
	ffb->state = FFB_STOPPED;
	Motor_SetVoltage(ffb->motor, 0);
	Motor_SetEnable(ffb->motor, false);
}

void FFBStart(FFBController_t *ffb) {
	ffb->state = FFB_RUNNING;
	Motor_SetEnable(ffb->motor, true);
}

FFBControllerState_e FFBGetState(FFBController_t *ffb) {
	return ffb->state;
}

void FFBSetControlRange(FFBController_t *ffb, int min, int max) {
	ffb->minLock = min;
	ffb->maxLock = max;
}

int FFBGetMinControlRange(FFBController_t *ffb) {
	return ffb->minLock;
}

int FFBGetMaxControlRange(FFBController_t *ffb) {
	return ffb->maxLock;
}

int FFBGetTravelRange(FFBController_t *ffb) {
	return ffb->travelRange;
}

float FFBGetTravelRangeInUnit(FFBController_t *ffb) {
	return ffb->travelRange/(float)Encoder_GetCountPerRev(ffb->encoder) *
			ffb->unitPerRev;
}

void FFBHome(FFBController_t *ffb) {

	// Save FFB state
	FFBControllerState_e prevState = FFBGetState(ffb);

	ffb->state = FFB_IDLE;

	// Save current limit setting
	float motorPrevCurrentLimit = Motor_GetCurrentLimit(ffb->motor);

	Motor_SetCurrentLimit(ffb->motor, FFB_CONTROL_HOME_CURRENT_LIMIT);

	Motor_SetEnable(ffb->motor, true);
	/* Find home start */
	// Record motor position
	int previousPosition = FFB_GetRawAxisCount(ffb);
	// Reverse motor
	FFB_SetMotorVelocity(ffb,
			ConvertFFBToMotorVelocity(ffb, -FFB_CONTROL_HOME_VELOCITY));
	delayMs(200);
	// Wait until motor stops moving (hit end)
	int steadyCount = 0;
	do {
		int currentPosition = FFB_GetRawAxisCount(ffb);
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
	int startPosition = FFB_GetRawAxisCount(ffb);
	// Stop motor
	FFB_SetMotorCurrent(ffb, 0);
	delayMs(1000);


	/* Find home end */
	// Record motor position
	previousPosition = FFB_GetRawAxisCount(ffb);

	// Move motor forward
	FFB_SetMotorVelocity(ffb,
			ConvertFFBToMotorVelocity(ffb, FFB_CONTROL_HOME_VELOCITY));
	delayMs(200);
	// Wait until motor stops moving (hit end)
	steadyCount = 0;
	do {
		int currentPosition = FFB_GetRawAxisCount(ffb);
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
	int endPosition = FFB_GetRawAxisCount(ffb);
	// Stop motor
	FFB_SetMotorCurrent(ffb, 0);
	delayMs(1000);

	if(endPosition < startPosition) {
		// Error
	}

	/* Record travel range */
	ffb->travelRange = endPosition - startPosition;

	/* Calibrate center */
	int center = (endPosition - startPosition)/2;
	FFB_SetAxisCount(ffb, center);
	ffb->prevEncoderCountAvg = 0;

	/* Go to center */
//	FFBSetForces(ffb, ffb->homeCenterForce);

	FFB_SetMotorVelocity(ffb,
			ConvertFFBToMotorVelocity(ffb, -FFB_CONTROL_HOME_VELOCITY));

	// Start
//	FFBStart(ffb);

	// Wait for center to be reached
	while(Abs(FFB_GetRawAxisCount(ffb)) > 5000) {
		delayMs(10);
	}

	delayMs(500);

	FFB_ResetForces(ffb);

	// Restore current limit
	Motor_SetCurrentLimit(ffb->motor, motorPrevCurrentLimit);
	// Return to previous state
	if(prevState == FFB_RUNNING) {
		FFBStart(ffb);
	}
	else {
		FFBStop(ffb);
	}

//	// Zero center position
//	EncoderResetCount(ffb->encoder);
//
}

void FFB_SetUnitPerRevConstant(FFBController_t *ffb, float unitPerRev) {
	ffb->unitPerRev = unitPerRev;
}

void FFB_ResetForces(FFBController_t *ffb) {
	// Clear all forces
	memset(&ffb->forces, 0, sizeof(ffb->forces));
}

float FFBCalcConstantForce(float gain, float amount) {
	return gain * amount;
}

float FFBCalcPeriodicForce(float gain, FFBPeriodicForce_t *periodic,
		float deltaTime) {
	return gain *
			FFBPeriodicCalc(periodic, deltaTime);
}

float FFBCalcSpringForce(float gain, float measuredPosition,
		float springForce) {

	float constrainedStrength = ConstrainFloat(
			springForce, -1.0f, 1.0f);

	float force = gain * -measuredPosition * constrainedStrength;
	return force;
}

float FFBCalcDamperForce(float gain, float magnitude, float velocity) {
	float force = gain * magnitude * -velocity;
	return force;
}

float FFB_GetOutputForce(FFBController_t *ffb) {
	return ffb->forceOut;
}

float FFBCalcAssist(float gain, float min, float speed) {
	return 0;
	if(speed < 0) {
		return gain*speed - min;
	}
	else if(speed > 0) {
		return gain*speed + min;
	}
	else {
		return 0;
	}
}

static float ConvertFFBToMotorVelocity(FFBController_t *ffb,
		float ffbVelocity) {
	return (ffbVelocity / ffb->unitPerRev) * 60.0f;
}

static float ConvertMotorToFFBVelocity(FFBController_t *ffb,
		float motorVelocity) {
	return (motorVelocity / 60.0f) * ffb->unitPerRev;
}

static float ConvertEncoderCountsToFFBUnits(FFBController_t *ffb,
		int counts) {
	return (counts/(float)Encoder_GetCountPerRev(ffb->encoder)) *
			ffb->unitPerRev;
}

static void FFB_SetMotorCurrent(FFBController_t *ffb, float current) {
	ffb->axisReverse ? Motor_SetCurrent(ffb->motor, -current) :
			Motor_SetCurrent(ffb->motor, current);
}

static void FFB_SetMotorVelocity(FFBController_t *ffb, float velocity) {
	ffb->axisReverse ? Motor_SetVelocity(ffb->motor, -velocity) :
			Motor_SetVelocity(ffb->motor, velocity);
}

static float FFB_GetMotorVelocity(FFBController_t *ffb) {
	return ffb->axisReverse ? -Motor_GetVelocity(ffb->motor) :
			Motor_GetVelocity(ffb->motor);
}

static float FFB_GetMotorTorque(FFBController_t *ffb) {
	return ffb->axisReverse ? -Motor_GetTorque(ffb->motor) :
			Motor_GetTorque(ffb->motor);
}
