/*
 * velocity_control.c
 *
 *  Created on: Aug 7, 2025
 *      Author: Jennyston
 */

#include "control/velocity_control.h"
#include "utilities/utilities.h"

void VelocityControl_Init(VelocityControl_t *velControl) {

	velControl->radsTarget = 0.0f;
	velControl->radsSetPoint = 0.0f;
	velControl->kv = 0.0f;
	velControl->ffTorque = 0.0f;
	velControl->stictionTorqueConstant = 0.0f;
	velControl->ffStiction = 0.0f;
//	velControl->velocity = 0.0f;
//	velControl->prevPosition = currentPosition;
	velControl->accelerationLimit = 1.0f;
	velControl->targetReached = false;

	PID_Init(&velControl->velPid);
//	LowPassFilter_Init(&velControl->lpfVelocity, lpfAlpha);
//	PID_Init(&velControl->accelPid);
}

void VelocityControl_SetRadSTarget(VelocityControl_t *velControl,
		float velocity) {
	velControl->radsTarget = velocity;
	velControl->ffTorque = velControl->kv * velocity;
	velControl->targetReached = false;

	if(velocity < 0) {
		velControl->ffStiction = -velControl->stictionTorqueConstant;
	}
	else if(velocity > 0) {
		velControl->ffStiction = velControl->stictionTorqueConstant;
	}
	else {
		velControl->ffStiction = 0.0f;
	}

	// Determine acceleration direction
	if(velControl->radsTarget > velControl->radsSetPoint) {
		velControl->accelerationTarget = velControl->accelerationLimit;
	}
	else if(velControl->radsTarget < velControl->radsSetPoint) {
		velControl->accelerationTarget = -velControl->accelerationLimit;
	}
	else {
		velControl->accelerationTarget = 0.0f;
	}
}

float VelocityControl_GetRadSTarget(VelocityControl_t *velControl) {
	return velControl->radsTarget;
}
//
//void VelocityControl_SetFilterAlpha(VelocityControl_t *velControl,
//		float alpha) {
//	LowPassFilter_SetAlpha(&velControl->lpfVelocity, alpha);
//}

void VelocityControl_SetAccelerationLimit(VelocityControl_t *velControl,
		float accelerationLimit) {
	velControl->accelerationLimit = accelerationLimit;
	velControl->accelerationTarget = signf(velControl->accelerationTarget) *
			velControl->accelerationLimit;
}

float VelocityControl_GetAccelerationTarget(VelocityControl_t *velControl) {
	return velControl->accelerationTarget;
}

bool VelocityControl_IsVelocityTargetReached(VelocityControl_t *velControl) {
	return velControl->targetReached;
}

PID_t *VelocityControl_GetVelocityPID(VelocityControl_t *velControl) {
	return &velControl->velPid;
}
//
//float VelocityControl_GetVelocity(VelocityControl_t *velControl) {
//	return velControl->velocity;
//}

//PID_t *VelocityControl_GetAccelerationPID(VelocityControl_t *velControl) {
//	return &velControl->accelPid;
//}

//void VelocityControl_UpdateVelocity(VelocityControl_t *velControl,
//		float measuredPosition, float deltaTime) {
//	velControl->velocity = LowPassFilter_Update(&velControl->lpfVelocity,
//				(measuredPosition - velControl->prevPosition)/deltaTime);
//
//	// Update for next iteration
//	velControl->prevPosition = measuredPosition;
//}

float VelocityControl_CalcTorque(VelocityControl_t *velControl, float velocity,
		float deltaTime) {

	//vf = vi + at
	velControl->radsSetPoint = velControl->radsSetPoint +
			velControl->accelerationTarget * deltaTime;

	if((velControl->accelerationTarget > 0 &&
			velControl->radsSetPoint >= velControl->radsTarget) ||
			(velControl->accelerationTarget < 0 &&
						velControl->radsSetPoint <= velControl->radsTarget)) {
		velControl->accelerationTarget = 0;
		velControl->radsSetPoint = velControl->radsTarget;
		velControl->targetReached = true;
	}

	velControl->output = PID_Calc(&velControl->velPid,
			velControl->radsSetPoint, velocity, deltaTime) + velControl->ffTorque +
					velControl->ffStiction;
	return velControl->output;
}
