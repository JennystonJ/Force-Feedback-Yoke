/*
 * position_control.c
 *
 *  Created on: Jun 7, 2026
 *      Author: Jennyston
 */

#include "control/position_control.h"
#include <math.h>

void PositionControl_Init(PositionControl_t *posControl) {
	posControl->torqueLimit = 0;
	posControl->accelerationLimit = 0;
	posControl->velocityLimit = 0;
	posControl->positionTarget = 0;
	posControl->targetReached = false;
	PID_Init(&posControl->positionPid);

	posControl->epsilon = 0.01;
	posControl->output = 0;
}

void PositionControl_SetPositionTarget(PositionControl_t *posControl, float target) {
	posControl->positionTarget = target;
}

void PositionControl_SetVelocityLimit(PositionControl_t *posControl, float velocity) {
	posControl->velocityLimit = velocity;
}

void PositionControl_SetAccelerationLimit(PositionControl_t *posControl,
		float acceleration) {
	posControl->accelerationLimit = acceleration;
}

void PositionControl_SetTorqueLimit(PositionControl_t *posControl, float torque) {
	posControl->torqueLimit = torque;
}

PID_t *PositionControl_GetPositionPID(PositionControl_t *posControl) {
	return &posControl->positionPid;
}


VelocityControlCommand_t PositionControl_CalcVelocity(PositionControl_t *posControl,
		const AxisKinematics_t *kinematics, float deltaTime) {
	VelocityControlCommand_t velCommand = {
			.accelerationLimit = posControl->accelerationLimit,
			.torqueLimit = posControl->torqueLimit
	};

	float velocity = PID_Calc(&posControl->positionPid,
			posControl->positionTarget, kinematics->position, deltaTime);
	// Limit velocity
	velCommand.velocityTarget = fminf(velocity, posControl->velocityLimit);

	posControl->output = velocity;

	return velCommand;
}
