/*
 * velocity_control.h
 *
 *  Created on: Aug 7, 2025
 *      Author: Jennyston
 */

#ifndef INC_VELOCITY_CONTROL_H_
#define INC_VELOCITY_CONTROL_H_

#include "pid.h"
#include "utilities/filters.h"

typedef struct VelocityControl {
	float velocitySetPoint;
	float velocity;
	float prevPosition;
	PID_t velPid;
	LowPass_t lpfVelocity;

//	float accelerationLimit;
//	PID_t accelPid;
} VelocityControl_t;

void VelocityControl_Init(VelocityControl_t *velControl, int currentPosition,
		float lpfAlpha);

void VelocityControl_SetVelocityTarget(VelocityControl_t *velControl,
		float velocity);
float VelocityControl_GetVelocityTarget(VelocityControl_t *velControl);
void VelocityControl_SetFilterAlpha(VelocityControl_t *velControl,
		float alpha);
//void VelocityControl_SetAccelerationLimit(VelocityControl_t *velControl,
//		float accelerationLimit);

PID_t *VelocityControl_GetVelocityPID(VelocityControl_t *velControl);
//PID_t *VelocityControl_GetAccelerationPID(VelocityControl_t *velControl);
float VelocityControl_GetVelocity(VelocityControl_t *velControl);

void VelocityControl_UpdateVelocity(VelocityControl_t *velControl,
		float measuredPosition, float deltaTime);

float VelocityControl_CalcTorque(VelocityControl_t *velControl,
		float deltaTime);

#endif /* INC_VELOCITY_CONTROL_H_ */
