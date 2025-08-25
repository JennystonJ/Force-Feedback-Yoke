/*
 * force_feedback_assist.c
 *
 *  Created on: Nov 23, 2024
 *      Author: Jennyston
 */

#include "force_feedback/force_feedback_assist.h"
#include <math.h>
#include <utilities/utilities.h>

// Private Function Prototypes
void DecayAssistForce(FFBAssist_t *ffbAssist, float speed, int dt);
static float slewLimitToZero(float in, float prevIn, float decay, float dt);
static float slewLimit(float in, float prevIn, float decay, float dt);

void FFBAssist_Init(FFBAssist_t *ffbAssist) {
	ffbAssist->decayRate = 1;
	ffbAssist->speedFactor = 1;
	ffbAssist->stictionThreshold = 0;
	ffbAssist->assistThreshold = 0;
	ffbAssist->smoothingThreshold = 3500;
	ffbAssist->smoothingRate = 0.10f;
	ffbAssist->previousForceApplied = 0;
	ffbAssist->lpFilterCo = 0.1f;
	ffbAssist->dFilterCo = 0.1f;
	ffbAssist->dK = 0;
	ffbAssist->dFPrevious = 0;
	ffbAssist->gain = 0;
	ffbAssist->motorTorqueCancelGain = 0;
	ffbAssist->accelerationGain = 0;
	ffbAssist->damping = 0;
	ffbAssist->velocitySmallComp = 0.001f;
	ffbAssist->forceScale = 1.0f;

	LowPassFilter_Init(&ffbAssist->lpfAssistForce, 0.25f);

	ffbAssist->assistForce = 0;


	ffbAssist->forceBiasDecay = 0.001;
}

void FFBAssist_SetDecayRate(FFBAssist_t *ffbAssist, float decayRate) {
	ffbAssist->decayRate = decayRate;
}

void FFBAssist_SetSpeedFactor(FFBAssist_t *ffbAssist, float speedFactor) {
	ffbAssist->speedFactor = speedFactor;
}

void FFBAssist_SetGain(FFBAssist_t *ffbAssist, float gain) {
	ffbAssist->gain = gain;
}

void FFBAssist_SetAccelerationGain(FFBAssist_t *ffbAssist, float accelGain) {
	ffbAssist->accelerationGain = accelGain;
}

void FFBAssist_SetVelocityGain(FFBAssist_t *ffbAssist, float velGain) {
	ffbAssist->velocityGain = velGain;
}

void FFBAssist_SetVelocitySmallCompensation(FFBAssist_t *ffbAssist,
		float velSmallComp) {
	ffbAssist->velocitySmallComp = velSmallComp;
}

float FFBAssist_Calc(FFBAssist_t *ffbAssist, float forceApplied,
		float motorForce, float velocity, float acceleration, float dt) {

//	if(forceApplied > ffbAssist->assistThreshold && speed < 0.0005) {
//			// Stiction detected
//			ffbAssist->compensatoryForce = ffbAssist->stictionThreshold -
//					ffbAssist->assistThreshold;
//	}
//	else if(forceApplied < -ffbAssist->assistThreshold && speed > 0.0005) {
//			// Stiction detected
//			ffbAssist->compensatoryForce = -(ffbAssist->stictionThreshold -
//					ffbAssist->assistThreshold);
//	}
//	else {
//		DecayCompensatoryForce(ffbAssist, speed, dt);
//	}
//	//Check if force direction changed
//	if((forceApplied > 0 && ffbAssist->previousForceApplied < 0) ||
//			(forceApplied < 0 && ffbAssist->previousForceApplied > 0)) {
//		// Set to 0 (decay immediately) to help with direction changes
//		ffbAssist->compensatoryForce = 0;
//	}
// ************
//	float newForce = 0;
//	if(fabs(forceApplied) <
//			ffbAssist->assistThreshold) {r
////		ffbAssist->compensatoryForce = 0.0f;
////		DecayCompensatoryForce(ffbAssist, speed, dt);
//
//	}
//	else {
//		newForce = (motorForce*ffbAssist->motorTorqueCancelGain *
//				acceleration*ffbAssist->accelerationGain) +
//						-ffbAssist->gain * forceApplied
//						- ffbAssist->damping;
//		if(forceApplied < 0) {
//			newForce += ffbAssist->stictionThreshold;
//		}
//		else if(forceApplied > 0) {
//			newForce -= ffbAssist->stictionThreshold;
//		}
//
//		newForce = newForce * ffbAssist->smoothingRate +
//				newForce * (1 - ffbAssist->smoothingRate);
// ***************
//		if(fabs(forceApplied) < ffbAssist->smoothingThreshold) {
//			// Smooth out application of force
//			ffbAssist->compensatoryForce = newForce * ffbAssist->smoothingRate +
//					ffbAssist->compensatoryForce *
//					(1 - ffbAssist->smoothingRate);
//		}
//		else {
//
//		}
//	}

//	ffbAssist->assistForce = ffbAssist->assistForce +
//			ffbAssist->lpFilterCo * (newForce - ffbAssist->assistForce);
// *******************
//	ffbAssist->assistForce = newForce;
//	float dF = ffbAssist->dFilterCo *
//			(forceApplied - ffbAssist->previousForceApplied) / dt +
//			(1 - ffbAssist->dFilterCo) * ffbAssist->dFPrevious;
//	ffbAssist->assistForce -= ffbAssist->dK * dF;
//
//
//	// Update previous force applied for next calculation
//	ffbAssist->dFPrevious = dF;
//	ffbAssist->previousForceApplied = forceApplied;
// ************
//
//	float velocityAbs = fabs(velocity);
//	float velocityScale = velocityAbs /
//			(velocityAbs + ffbAssist->velocitySmallComp);
//	float assistGainScaled = ffbAssist->gain * velocityScale;
//
//
//	ffbAssist->inertialContribution = acceleration *
//			ffbAssist->accelerationGain;
//	ffbAssist->assistForce = assistGainScaled *
//			forceApplied - ffbAssist->inertialContribution;
//	return ffbAssist->assistForce;

// ************

	// User force estimation
//	float forceUser = forceApplied + ffbAssist->accelerationGain * acceleration +
//			ffbAssist->velocityGain * velocity; // + frictionEst
//
//	// Stiction logic
//	bool nearStick = fabsf(velocity) < ffbAssist->velocitySticition;
//	if(nearStick && fabsf(forceUser) > ffbAssist->forceBreak &&
//			!ffbAssist->boostActive) {
//		ffbAssist->boostActive = true;
//		ffbAssist->boostTimerCount = ffbAssist->boostTime;
//		ffbAssist->forceBias = ConstrainFloat(ffbAssist->forceBias +
//				signf(forceUser)*ffbAssist->forceBiasStep,
//				-ffbAssist->forceBiasMax, ffbAssist->forceBiasMax);
//	}
//
//	ffbAssist->boostTimerCount--;
//	if(ffbAssist->boostTimerCount <= 0) {
//		ffbAssist->boostTimerCount = 0;
//	}
//
//	float boostForce;
//	if(ffbAssist->boostActive) {
//		boostForce = signf(forceUser) * ffbAssist->forceBoost;
//		if((fabs(velocity) > ffbAssist->velocityExit) ||
//				(ffbAssist->boostTimerCount <= 0)) {
//			ffbAssist->boostActive = false;
//		}
//	}
//
//	if(nearStick && fabsf(forceUser) > ffbAssist->forceStart) {
//		ffbAssist->forceBias = ConstrainFloat(ffbAssist->forceBias +
//				ffbAssist->forceUserKi * forceUser * dt,
//				-ffbAssist->forceBiasMax, ffbAssist->forceBiasMax);
//	}
//	else {
//		ffbAssist->forceBias *= expf(-dt/ffbAssist->forceBiasDecay);
//	}
//
//	float forceRaw = ffbAssist->gain * forceUser + ffbAssist->forceBias +
//			boostForce;
//	ffbAssist->assistForce = slewLimit(forceRaw, ffbAssist->assistForce,
//			ffbAssist->forceSlewLimit, dt);
//
//	return ffbAssist->assistForce;

// ************
	float forceUser = forceApplied +
			ffbAssist->accelerationGain * acceleration +
			ffbAssist->velocityGain * velocity; // + frictionEst


	// Stiction logic
	bool nearStick = fabsf(velocity) < ffbAssist->velocitySticition;
	if(nearStick && fabsf(forceUser) > ffbAssist->forceBreak &&
			!ffbAssist->boostActive) {
		ffbAssist->boostActive = true;
		ffbAssist->boostTimerCount = ffbAssist->boostTime;
		ffbAssist->forceBias = ConstrainFloat(ffbAssist->forceBias +
				signf(forceUser)*ffbAssist->forceBiasStep,
				-ffbAssist->forceBiasMax, ffbAssist->forceBiasMax);
	}

	ffbAssist->boostTimerCount--;
	if(ffbAssist->boostTimerCount <= 0) {
		ffbAssist->boostTimerCount = 0;
	}

	float boostForce = 0.0f;
	if(ffbAssist->boostActive) {
		boostForce = signf(forceUser) * ffbAssist->forceBoost;
		if((fabs(velocity) > ffbAssist->velocityExit) ||
				(ffbAssist->boostTimerCount <= 0)) {
			ffbAssist->boostActive = false;
		}
	}

	if(nearStick && fabsf(forceUser) > ffbAssist->forceStart) {
		ffbAssist->forceBias = ConstrainFloat(ffbAssist->forceBias +
				ffbAssist->forceUserKi * forceUser * dt,
				-ffbAssist->forceBiasMax, ffbAssist->forceBiasMax);
	}
	else {
		ffbAssist->forceBias *= expf(-dt/ffbAssist->forceBiasDecay);
	}


	// Force-based Dampening
	float s = ConstrainFloat(fabsf(forceUser) / ffbAssist->forceScale,
			0.0f, 1.0f);

	// Dead band
	if(fabsf(forceUser) < ffbAssist->forceDeadband) {
		s = 0.0f;
	}

	float b = ffbAssist->dampingMin +
			(ffbAssist->dampingMax - ffbAssist->dampingMin) * (1.0f - s);
	ffbAssist->dampingForce = -b * velocity;

	float forceRaw = ffbAssist->gain * forceUser + ffbAssist->forceBias +
			boostForce + ffbAssist->dampingForce;
	ffbAssist->assistForce = slewLimit(forceRaw, ffbAssist->assistForce,
			ffbAssist->forceSlewLimit, dt);

	return ffbAssist->assistForce;
}

void DecayAssistForce(FFBAssist_t *ffbAssist, float speed, int dt) {
	speed = speed < 0.001f ? 0 : speed;
	// Total decay combines time and speed contributions
	float totalDecay = ffbAssist->decayRate + ffbAssist->speedFactor *
			fabsf(speed);

	// Determine compensatory force direction and update compensatory force
	if(ffbAssist->assistForce < 0) {
		ffbAssist->assistForce = fminf(0,
				ffbAssist->assistForce + totalDecay*dt*DT_SCALE_TO_MS);
	}
	else if(ffbAssist->assistForce > 0) {
		ffbAssist->assistForce = fmaxf(0,
				ffbAssist->assistForce - totalDecay*dt*DT_SCALE_TO_MS);
	}
	else {
		// Do nothing
	}
}

static float slewLimitToZero(float in, float prevIn, float decay, float dt) {

	if(dt <= 0.0f || decay <= 0.0f) {
		return in;
	}

	if(fabsf(in) > fabs(prevIn)) {
		// magnitude is going up, pass input directly as output
		return in;
	}


	float maxDecay = decay * dt;
	float delta = in - prevIn;
	float step = fminf(fabsf(delta), maxDecay) * (delta >= 0 ? 1.0f : -1.0f);

	return prevIn + step;
}

static float slewLimit(float in, float prevIn, float decay, float dt) {

	if(dt <= 0.0f || decay <= 0.0f) {
		return in;
	}

	float maxSlew = decay * dt;
	float delta = in - prevIn;
	float step = fminf(fabsf(delta), maxSlew) * (delta >= 0 ? 1.0f : -1.0f);

	return prevIn + step;
}
