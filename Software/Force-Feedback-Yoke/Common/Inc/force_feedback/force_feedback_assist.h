/*
 * force_feedback_assist.h
 *
 *  Created on: Nov 23, 2024
 *      Author: Jennyston
 */

#ifndef INC_FORCE_FEEDBACK_ASSIST_H_
#define INC_FORCE_FEEDBACK_ASSIST_H_

#define DT_SCALE_TO_MS 0.001f

#include "utilities/filters.h"
#include <stdbool.h>

typedef struct FFBAssist {
	float decayRate;
	float speedFactor;
	float stictionThreshold;
	float assistThreshold;
	float smoothingThreshold;
	float smoothingRate;
	float gain;
	float previousForceApplied;
	float lpFilterCo;
	float dFilterCo;
	float dFPrevious;
	float dK;
	float motorTorqueCancelGain;
	float accelerationGain;

	float velocityGain;
	float velocitySticition;
	float velocityExit;

	float forceBreak;
	int boostTimerCount;
	int boostTime;
	bool boostActive;
	float forceBoost;
	float forceStart;
	float forceUserKi;
	float forceBiasDecay;
	float forceSlewLimit;

	float forceBias;
	float forceBiasStep;
	float forceBiasMax;


	float forceScale;
	float forceDeadband;
	float dampingMin;
	float dampingMax;
	float dampingForce;

	float damping;
	float inertialContribution;
	float velocitySmallComp;

	LowPass_t lpfAssistForce;

	float assistForce;
} FFBAssist_t;

void FFBAssist_Init(FFBAssist_t *ffbAssist);
void FFBAssist_SetDecayRate(FFBAssist_t *ffbAssist, float decayRate);
void FFBAssist_SetSpeedFactor(FFBAssist_t *ffbAssist, float speedFactor);

void FFBAssist_SetGain(FFBAssist_t *ffbAssist, float gain);
void FFBAssist_SetAccelerationGain(FFBAssist_t *ffbAssist, float accelGain);
void FFBAssist_SetVelocityGain(FFBAssist_t *ffbAssist, float velGain);
void FFBAssist_SetVelocitySmallCompensation(FFBAssist_t *ffbAssist,
		float velSmallComp);

float FFBAssist_Calc(FFBAssist_t *ffbAssist, float forceApplied,
		float motorForce, float speed, float acceleration, float dt);

#endif /* INC_FORCE_FEEDBACK_ASSIST_H_ */
