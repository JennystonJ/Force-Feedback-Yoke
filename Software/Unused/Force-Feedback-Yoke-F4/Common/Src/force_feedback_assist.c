/*
 * force_feedback_assist.c
 *
 *  Created on: Nov 23, 2024
 *      Author: Jennyston
 */

#include "force_feedback_assist.h"
#include <math.h>

// Private Function Prototypes
void DecayAssistForce(FFBAssist_t *ffbAssist, float speed, int dt);

void FFBAssistInit(FFBAssist_t *ffbAssist) {
	ffbAssist->decayRate = 1;
	ffbAssist->speedFactor = 1;
	ffbAssist->stictionThreshold = 600;
	ffbAssist->assistThreshold = 1300;
	ffbAssist->smoothingThreshold = 3500;
	ffbAssist->smoothingRate = 0.10;
	ffbAssist->previousForceApplied = 0;
	ffbAssist->lpFilterCo = 0.1;
	ffbAssist->dFilterCo = 0.1;
	ffbAssist->dK = 0;
	ffbAssist->dFPrevious = 0;
	ffbAssist->gain = 0;

	ffbAssist->assistForce = 0;
}

void FFBAssistSetDecayRate(FFBAssist_t *ffbAssist, float decayRate) {
	ffbAssist->decayRate = decayRate;
}

void FFBAssistSetSpeedFactor(FFBAssist_t *ffbAssist, float speedFactor) {
	ffbAssist->speedFactor = speedFactor;
}

float FFBAssistCalc(FFBAssist_t *ffbAssist, float forceApplied, float speed,
		int dt) {

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

	float newForce = 0;
	if(fabs(forceApplied) < ffbAssist->assistThreshold) {
//		ffbAssist->compensatoryForce = 0.0f;
//		DecayCompensatoryForce(ffbAssist, speed, dt);

	}
	else {
		newForce = forceApplied * -ffbAssist->gain;
		if(forceApplied < 0) {
			newForce += ffbAssist->stictionThreshold;
		}
		else if(forceApplied > 0) {
			newForce -= ffbAssist->stictionThreshold;
		}

//		if(fabs(forceApplied) < ffbAssist->smoothingThreshold) {
//			// Smooth out application of force
//			ffbAssist->compensatoryForce = newForce * ffbAssist->smoothingRate +
//					ffbAssist->compensatoryForce *
//					(1 - ffbAssist->smoothingRate);
//		}
//		else {
//
//		}
	}

//	ffbAssist->assistForce = ffbAssist->assistForce +
//			ffbAssist->lpFilterCo * (newForce - ffbAssist->assistForce);

	ffbAssist->assistForce = newForce;
	float dF = ffbAssist->dFilterCo *
			(forceApplied - ffbAssist->previousForceApplied) / dt +
			(1 - ffbAssist->dFilterCo) * ffbAssist->dFPrevious;
	ffbAssist->assistForce -= ffbAssist->dK * dF;


	// Update previous force applied for next calculation
	ffbAssist->dFPrevious = dF;
	ffbAssist->previousForceApplied = forceApplied;

	return ffbAssist->assistForce;
}

void DecayAssistForce(FFBAssist_t *ffbAssist, float speed, int dt) {
	speed = speed < 0.001f ? 0 : speed;
	// Total decay combines time and speed contributions
	float totalDecay = ffbAssist->decayRate + ffbAssist->speedFactor *
			fabs(speed);

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
