/*
 * velocity_control.c
 *
 *  Created on: Aug 7, 2025
 *      Author: Jennyston
 */

#include "velocity_control.h"

void VelocityControl_Init(VelocityControl_t *velControl, int currentPosition,
		float lpfAlpha) {

	velControl->velocitySetPoint = 0.0f;
	velControl->velocity = 0.0f;
	velControl->prevPosition = currentPosition;
//	velControl->accelerationLimit = 0.0f;

	PID_Init(&velControl->velPid);
	LowPassFilter_Init(&velControl->lpfVelocity, lpfAlpha);
//	PID_Init(&velControl->accelPid);
}

void VelocityControl_SetVelocityTarget(VelocityControl_t *velControl,
		float velocity) {
	velControl->velocitySetPoint = velocity;
}

float VelocityControl_GetVelocityTarget(VelocityControl_t *velControl) {
	return velControl->velocitySetPoint;
}

void VelocityControl_SetFilterAlpha(VelocityControl_t *velControl,
		float alpha) {
	LowPassFilter_SetAlpha(&velControl->lpfVelocity, alpha);
}

//void VelocityControl_SetAccelerationLimit(VelocityControl_t *velControl,
//		float accelerationLimit) {
//	velControl->accelerationLimit = accelerationLimit;
//}

PID_t *VelocityControl_GetVelocityPID(VelocityControl_t *velControl) {
	return &velControl->velPid;
}

float VelocityControl_GetVelocity(VelocityControl_t *velControl) {
	return velControl->velocity;
}

//PID_t *VelocityControl_GetAccelerationPID(VelocityControl_t *velControl) {
//	return &velControl->accelPid;
//}

void VelocityControl_UpdateVelocity(VelocityControl_t *velControl,
		float measuredPosition, float deltaTime) {
	velControl->velocity = LowPassFilter_Update(&velControl->lpfVelocity,
				(measuredPosition - velControl->prevPosition)/deltaTime);

	// Update for next iteration
	velControl->prevPosition = measuredPosition;
}

float VelocityControl_CalcTorque(VelocityControl_t *velControl,
		float deltaTime) {

	return PID_Calc(&velControl->velPid,
			velControl->velocitySetPoint, velControl->velocity, deltaTime);
}
