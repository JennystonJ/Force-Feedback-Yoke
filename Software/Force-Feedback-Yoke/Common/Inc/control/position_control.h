/*
 * position_control.h
 *
 *  Created on: Jun 7, 2026
 *      Author: Jennyston
 */

#ifndef INC_CONTROL_POSITION_CONTROL_H_
#define INC_CONTROL_POSITION_CONTROL_H_

#include "control/motion_command.h"
#include "control/axis_kinematics.h"
#include "pid.h"
#include <stdbool.h>

typedef struct PositionControl {
	float positionTarget;
	float torqueLimit;
	float accelerationLimit;
	float velocityLimit;
	PID_t positionPid;

	bool targetReached;

	float epsilon;

	float output;
} PositionControl_t;

void PositionControl_Init(PositionControl_t *posControl);

void PositionControl_SetPositionTarget(PositionControl_t *posControl, float target);
void PositionControl_SetVelocityLimit(PositionControl_t *posControl, float velocity);
void PositionControl_SetAccelerationLimit(PositionControl_t *posControl,
		float acceleration);
void PositionControl_SetTorqueLimit(PositionControl_t *posControl, float torque);

PID_t *PositionControl_GetPositionPID(PositionControl_t *posControl);

VelocityControlCommand_t PositionControl_CalcVelocity(PositionControl_t *posControl,
		const AxisKinematics_t *kinematics, float deltaTime);

#endif /* INC_CONTROL_POSITION_CONTROL_H_ */
