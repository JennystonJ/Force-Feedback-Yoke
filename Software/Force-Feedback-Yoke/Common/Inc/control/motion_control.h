/*
 * motion_control.h
 *
 *  Created on: Jun 6, 2026
 *      Author: Jennyston
 */

#ifndef INC_CONTROL_MOTION_CONTROL_H_
#define INC_CONTROL_MOTION_CONTROL_H_

#include "motion_command.h"
#include "control/velocity_control.h"
#include "control/position_control.h"
#include "control/axis_kinematics.h"

typedef struct MotionControlCal {
	float fs;
	float fc;
	float fv;
	float sigma;
	float vs;
} MotionControlCal_t;

typedef struct MotionControl {
	VelocityControl_t *velControl;
	PositionControl_t *posControl;
	MotionControlCommand_t command;

	MotionControlCal_t calibration;

	// For Debug
	float calcTorqueOutput;
} MotionControl_t;

void MotionControl_Init(MotionControl_t *control, VelocityControl_t *velControl,
		PositionControl_t *posControl);
MotionControlCal_t *MotionControl_GetCalibration(MotionControl_t *control);

void MotionControl_SetCommand(MotionControl_t *control,
		const MotionControlCommand_t *command);
void MotionControl_SetTorqueCommand(MotionControl_t *control, float torqueTarget,
		float torqueLimit);
TorqueControlCommand_t MotionControl_CalcTorque(MotionControl_t *control,
		const AxisKinematics_t *kinematics,
		float deltaTime);

#endif /* INC_CONTROL_MOTION_CONTROL_H_ */
