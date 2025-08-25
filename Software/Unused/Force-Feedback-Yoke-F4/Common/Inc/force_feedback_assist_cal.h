/*
 * force_feedback_assist_cal.h
 *
 *  Created on: Aug 10, 2024
 *      Author: Jennyston
 */

#ifndef INC_FORCE_FEEDBACK_ASSIST_CAL_H_
#define INC_FORCE_FEEDBACK_ASSIST_CAL_H_

typedef struct FFBAssistCal {
	struct {
		float staticFriction;
		float dynamicFriction;
		float inertialTorque;
	} calibration;

	FFBController_t *ffb;
} FFBAssistCal_t;

void FFBAssistCalInit(FFBAssistCal_t *cal, FFBController_t *ffb);
void FFBAssistCalRunCalibration(FFBAssistCal_t *cal);

#endif /* INC_FORCE_FEEDBACK_ASSIST_CAL_H_ */
