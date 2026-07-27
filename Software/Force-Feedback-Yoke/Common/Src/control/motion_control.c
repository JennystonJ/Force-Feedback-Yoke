/*
 * motion_control.c
 *
 *  Created on: Jun 6, 2026
 *      Author: Jennyston
 */

#include "control/motion_control.h"
#include <math.h>

static float MotionControl_CalcFeedForward(MotionControl_t *control,
		const AxisKinematics_t *kinematics);

void MotionControl_Init(MotionControl_t *control, VelocityControl_t *velControl,
		PositionControl_t *posControl) {
	control->velControl = velControl;
	control->posControl = posControl;
}

MotionControlCal_t *MotionControl_GetCalibration(MotionControl_t *control) {
	return &control->calibration;
}

void MotionControl_SetCommand(MotionControl_t *control,
		const MotionControlCommand_t *command) {
	control->command = *command;

	switch(control->command.type) {
		case MOTION_CONTROL_TYPE_TORQUE:
			// No setup needed, do nothing
			break;
		case MOTION_CONTROL_TYPE_VELOCITY:
		{
			// Set up velocity controller parameters
			VelocityControlCommand_t *velCommand =
					&control->command.data.velocityCommand;
			VelocityControl_SetAccelerationLimit(control->velControl,
					velCommand->accelerationLimit);
			VelocityControl_SetRadSTarget(control->velControl,
					velCommand->velocityTarget);
			break;
		}
		case MOTION_CONTROL_TYPE_POSITION:
		{
			// Set up position controller parameters
			PositionControlCommand_t *posCommand =
					&control->command.data.positionCommand;
			PositionControl_SetAccelerationLimit(control->posControl,
					posCommand->accelerationLimit);
			PositionControl_SetVelocityLimit(control->posControl,
					posCommand->velocityLimit);
			PositionControl_SetPositionTarget(control->posControl,
					posCommand->position);
			break;
		}
		default:
			// Invalid type, do nothing
	}
}

void MotionControl_SetTorqueCommand(MotionControl_t *control, float torqueTarget,
		float torqueLimit) {
	control->command.type = MOTION_CONTROL_TYPE_TORQUE;
	control->command.data.torqueCommand.torqueTarget = torqueTarget;
	control->command.data.torqueCommand.torqueLimit = torqueLimit;
}

TorqueControlCommand_t MotionControl_CalcTorque(MotionControl_t *control,
		const AxisKinematics_t *kinematics,
		float deltaTime) {
	TorqueControlCommand_t torqueCommand = {
			.torqueTarget = 0.0f,
			.torqueLimit = 0.0f,
	};

	switch(control->command.type) {
		case MOTION_CONTROL_TYPE_TORQUE:
			// Copy torque parameters directly
			torqueCommand = control->command.data.torqueCommand;
			break;
		case MOTION_CONTROL_TYPE_VELOCITY:
			// Calculate torque
			torqueCommand.torqueTarget =
					VelocityControl_CalcTorque(control->velControl,
							kinematics->velocity, deltaTime);
			torqueCommand.torqueLimit =
					control->command.data.velocityCommand.torqueLimit;
			break;
		case MOTION_CONTROL_TYPE_POSITION:
		{
			// Calculate velocity command
			VelocityControlCommand_t velCommand =
					PositionControl_CalcVelocity(control->posControl,
							kinematics, deltaTime);

			// Set up velocity controller parameters
			VelocityControl_SetAccelerationLimit(control->velControl,
					velCommand.accelerationLimit);
			VelocityControl_SetRadSTarget(control->velControl,
					velCommand.velocityTarget);

			// Calculate torque
			torqueCommand.torqueTarget =
					VelocityControl_CalcTorque(control->velControl,
							kinematics->velocity, deltaTime);
			torqueCommand.torqueLimit =
					control->command.data.positionCommand.torqueLimit;
			break;
		}
		default:
			// Invalid type
			return torqueCommand;
	}

	// Calculate and add feed forward torque
	torqueCommand.torqueTarget += MotionControl_CalcFeedForward(control,
			kinematics);

	control->calcTorqueOutput = torqueCommand.torqueTarget;
	return torqueCommand;
}

static float MotionControl_CalcFeedForward(MotionControl_t *control,
		const AxisKinematics_t *kinematics) {

	if(control->calibration.sigma <= 0 || control->calibration.vs <= 0) {
		return 0.0f;
	}

	// Friction torque calculation
	float staticExtra = (control->calibration.fs > control->calibration.fc) ?
			(control->calibration.fs - control->calibration.fc) : 0.0f;
	float stribeckMultiplier = expf(-fabsf(kinematics->velocity) /
			control->calibration.vs);

	float totalDryFriction = control->calibration.fc +
			(staticExtra * stribeckMultiplier);

	float tDry = totalDryFriction * tanhf(kinematics->velocity /
			control->calibration.sigma);

	float tViscous = control->calibration.fv * kinematics->velocity;

	return tDry + tViscous;
}

