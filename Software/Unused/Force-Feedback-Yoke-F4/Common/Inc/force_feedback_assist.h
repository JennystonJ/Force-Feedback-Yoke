/*
 * force_feedback_assist.h
 *
 *  Created on: Nov 23, 2024
 *      Author: Jennyston
 */

#ifndef INC_FORCE_FEEDBACK_ASSIST_H_
#define INC_FORCE_FEEDBACK_ASSIST_H_

#define DT_SCALE_TO_MS 0.001f

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

	float assistForce;
} FFBAssist_t;

void FFBAssistInit(FFBAssist_t *ffbAssist);
void FFBAssistSetDecayRate(FFBAssist_t *ffbAssist, float decayRate);
void FFBAssistSetSpeedFactor(FFBAssist_t *ffbAssist, float speedFactor);
float FFBAssistCalc(FFBAssist_t *ffbAssist, float forceApplied, float speed,
		int dt);

#endif /* INC_FORCE_FEEDBACK_ASSIST_H_ */
