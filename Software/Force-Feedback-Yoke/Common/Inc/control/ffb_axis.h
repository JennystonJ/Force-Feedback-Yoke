/*
 * ffb_axis.h
 *
 *  Created on: Apr 27, 2026
 *      Author: Jennyston
 */

#ifndef INC_CONTROL_FFB_AXIS_H_
#define INC_CONTROL_FFB_AXIS_H_

#include "config/ffb_axis_config.h"
#include "motor.h"
#include "axis_geometry.h"
#include "axis_kinematics.h"
#include "axis_limits.h"
#include "axis_range.h"
#include "ffb_home.h"
#include "force_feedback/force_feedback_controller.h"
#include "encoder.h"
#include "load_cell.h"
#include "utilities/filters.h"
#include "velocity_estimator.h"
#include <stdbool.h>
#include "force_feedback/force_feedback_assist.h"
#include "control/motion_control.h"

typedef enum FFBAxisStatus {
	FFB_AXIS_STATUS_OK,
	FFB_AXIS_STATUS_ERROR,
} FFBAxisStatus_e;

typedef enum FFBAxisMode {
	FFB_AXIS_MODE_DISABLED,
	FFB_AXIS_MODE_IDLE,
	FFB_AXIS_MODE_FFB_ACTIVE,
	FFB_AXIS_MODE_CAL,
	FFB_AXIS_MODE_HOMING,
	FFB_AXIS_MODE_FAULT
} FFBAxisMode_e;

typedef enum AxisMotionControlMode {
	AXIS_MOTION_CONTROL_MODE_OFF,
	AXIS_MOTION_CONTROL_MODE_TORQUE,
	AXIS_MOTION_CONTROL_MODE_VELOCITY
} AxisMotionControlMode_e;


typedef struct FFBAxis {
	Motor_t *motor;
	Encoder_t *encoder;
	LoadCell_t *loadCell;
	bool reverse;

	FFBController_t ffb;
	FFBAssist_t assist;
	VelocityControl_t velControl;
	PositionControl_t posControl;

	AxisGeometry_t geom;
	AxisKinematics_t kinematics;

	AxisLimits_t limits;

	MotionControl_t motionControl;
	AxisMotionControlMode_e controlMode;

	FFBAxisMode_e mode;
	FFBHome_t home;
	float homeMaxMotorTorque;

	VelocityEstimator_t ve;
	LowPass_t lpfAccel;
} FFBAxis_t;

void FFBAxis_Init(FFBAxis_t *axis, const FFBAxisConfig_t *config);

void FFBAxis_StartCalibration(FFBAxis_t *axis);
bool FFBAxis_IsCalibrationDone(FFBAxis_t *axis);

void FFBAxis_StartHoming(FFBAxis_t *axis);
bool FFBAxis_IsHomingDone(FFBAxis_t *axis);

void FFBAxis_Update(FFBAxis_t *axis, float deltaTime);
void FFBAxis_ControlISR(FFBAxis_t *axis, float deltaTimeMs);

FFBAxisStatus_e FFBAxis_SetFFBOn(FFBAxis_t *axis);
FFBAxisStatus_e FFBAxis_SetFFBOff(FFBAxis_t *axis);

AxisRange_t FFBAxis_GetSafeAxisPositionRange(FFBAxis_t *axis);
bool FFBAxis_IsWithinOperatingPositionRange(FFBAxis_t *axis);
float FFBAxis_GetSafeMaxTorque(FFBAxis_t *axis);

MotionControl_t *FFBAxis_GetMotionControl(FFBAxis_t *axis);

void FFBAxis_MotionControlUpdate(FFBAxis_t *axis, float deltaTime);
void FFBAxis_ApplyMotionCommand(FFBAxis_t *axis,
		const MotionControlCommand_t *command, float deltaTime);
void FFBAxis_SetAxisVelocity(FFBAxis_t *axis,
		const MotionControlCommand_t *command);
void FFBAxis_SetAxisTorque(FFBAxis_t *axis,
		const TorqueControlCommand_t *torqueCommand);
void FFBAxis_SetForces(FFBAxis_t *axis, const FFBForces_t *forces);

VelocityControl_t *FFBAxis_GetVelocityControl(FFBAxis_t *axis);
const AxisKinematics_t *FFBAxis_GetAxisKinematics(FFBAxis_t *axis);
AxisLimits_t *FFBAxis_GetAxisLimits(FFBAxis_t *axis);

#endif /* INC_CONTROL_FFB_AXIS_H_ */
