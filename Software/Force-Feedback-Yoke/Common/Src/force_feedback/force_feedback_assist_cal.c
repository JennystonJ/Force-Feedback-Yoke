/*
 * force_feedback_assist_cal.c
 *
 *  Created on: Aug 10, 2024
 *      Author: Jennyston
 */

#include <config/force_feedback_config.h>
#include "force_feedback/force_feedback_assist_cal.h"
#include <stdbool.h>
#include <math.h>
#include "delay.h"

#define EPSILON 0.05f

static void FFBAssistCal_SetPosition(FFBAssistCal_t *cal, int position,
		float velocity);

static bool FFBAssistCal_RunStaticTest(FFBAssistCal_t *cal, int torque);

//void FindStaticFriction(FFBAssistCal_t *cal);
//
//void FFBAssistCalInit(FFBAssistCal_t *cal, FFBController_t *ffb) {
//	cal->ffb = ffb;
//
//	cal->calibration.staticFriction = 0;
//	cal->calibration.dynamicFriction = 0;
//	cal->calibration.inertialTorque = 0;
//}
//
//void FFBAssistCalRunCalibration(FFBAssistCal_t *cal) {
//	FindStaticFriction(cal);
//}
//
//void FindStaticFriction(FFBAssistCal_t *cal) {
//
//}

void FFBAssistCal_Init(FFBAssistCal_t *cal, FFBController_t *ffb) {
	cal->ffb = ffb;

	cal->calibration.staticFriction = 0;
	cal->calibration.dynamicFriction = 0;
}

void FFBAssistCal_RunStaticCalibration(FFBAssistCal_t *cal) {
	FFB_Home(cal->ffb);
	FFB_Stop(cal->ffb);

//	Motor_t *ffbMotor = cal->ffb->motor;

	// Perform binary search for static friction
	float min = FFB_ASSIST_CAL_STATIC_TORQUE_TEST_MIN;
	float max = FFB_ASSIST_CAL_STATIC_TORQUE_TEST_MAX;
	float test = (max + min)/2;
	float preTest;
	bool found = false;

	do {
		preTest = test;

		test = (min + max)/2;

		if(FFBAssistCal_RunStaticTest(cal, test) == true) {
			// Torque is enough
			max = test;
		}
		else {
			// Not enough torque
			min = test;
		}
	} while (fabsf(max - min) > EPSILON);

	cal->calibration.staticFriction = test;

}

static void FFBAssistCal_SetPosition(FFBAssistCal_t *cal, int position,
		float velocity) {
	int startPosition = FFB_GetRawAxisCount(cal->ffb);
	int sign = (startPosition > 0) - (startPosition < 0);
//	Motor_t *ffbMotor = cal->ffb->motor;

	// Move to target position
//	Motor_SetVelocity(ffbMotor, velocity * sign);
	while(FFB_GetRawAxisCount(cal->ffb) != position) {
		// Do nothing
	}

	// Target position reached, stop
//	Motor_SetVelocity(ffbMotor, 0);
}

static bool FFBAssistCal_RunStaticTest(FFBAssistCal_t *cal, int torque) {
	// Go to starting position
	FFBAssistCal_SetPosition(cal, -FFB_GetTravelRange(cal->ffb)/2 *
			FFB_ASSIST_CAL_TRAVEL_LIMIT_PERCENT, FFB_ASSIST_CAL_POS_SEEK_VEL);
	int startPosition = FFB_GetRawAxisCount(cal->ffb);

	// Apply torque
//	Motor_SetTorque(cal->ffb->motor, torque);
	delayMs(FFB_ASSIST_CAL_STATIC_TORQUE_TEST_DELAY);
	if(FFB_GetRawAxisCount(cal->ffb) - startPosition >
		FFB_ASSIST_CAL_STATIC_TORQUE_TEST_DELTA_POS) {
		// Enough torque
		return true;
	}
	else {
		// Not enough torque
		return false;
	}
}
