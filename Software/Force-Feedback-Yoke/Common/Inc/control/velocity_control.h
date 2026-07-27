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
#include <stdbool.h>

typedef struct VelocityControl {
	float accelerationTarget;
	float radsTarget;
	float radsSetPoint;
	PID_t velPid;
	float kv;
	float ffTorque;
	float stictionTorqueConstant;
	float ffStiction;

	bool targetReached;

	float accelerationLimit;
//	PID_t accelPid;
	float output;
} VelocityControl_t;

void VelocityControl_Init(VelocityControl_t *velControl);

void VelocityControl_SetRadSTarget(VelocityControl_t *velControl,
		float velocity);
float VelocityControl_GetRadSTarget(VelocityControl_t *velControl);
void VelocityControl_SetAccelerationLimit(VelocityControl_t *velControl,
		float accelerationLimit);
float VelocityControl_GetAccelerationTarget(VelocityControl_t *velControl);
bool VelocityControl_IsVelocityTargetReached(VelocityControl_t *velControl);

PID_t *VelocityControl_GetVelocityPID(VelocityControl_t *velControl);
//PID_t *VelocityControl_GetAccelerationPID(VelocityControl_t *velControl);

float VelocityControl_CalcTorque(VelocityControl_t *velControl, float velocity,
		float deltaTime);

#endif /* INC_VELOCITY_CONTROL_H_ */
