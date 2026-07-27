/*
 * friction_cal.h
 *
 *  Created on: Jun 5, 2026
 *      Author: Jennyston
 */

#ifndef INC_CALIBRATION_FRICTION_CAL_H_
#define INC_CALIBRATION_FRICTION_CAL_H_

#include "control/axis_kinematics.h"
#include "calibration/friction_bias_cal.h"
#include <stdbool.h>
#include "config/calibration_config.h"
#include "control/axis_limits.h"

typedef enum FrictionCalState {
	FRICTION_CAL_STATE_IDLE,
	FRICTION_CAL_STATE_PREPARING,
	FRICTION_CAL_STATE_RUNNING_FORWARD,
	FRICTION_CAL_STATE_RUNNING_REVERSE
} FrictionCalState_e;

typedef enum FrictionCalDirection {
	FRICTION_CAL_DIRECTION_FORWARD,
	FRICTION_CAL_DIRECTION_REVERSE,
} FrictionCalDirection_e;

typedef struct FrictionCal{
	const FrictionCalConfig_t *config;
	FrictionCalState_e state;
	FrictionCalDirection_e direction;
	float velocitySum;
	float torqueSum;
	int velocityHoldCount;
	int dataCount;
	int testIndex;

	float torqueVelDataForward[10][2];
	float torqueVelDataReverse[10][2];
	float gravityTorque[10];

	float coulombTorque;
	float viscousTorqueCoeff;
} FrictionCal_t;


void FrictionCal_Init(FrictionCal_t *cal,
		const  FrictionCalConfig_t *config);
void FrictionCal_Start(FrictionCal_t *cal);
MotionControlCommand_t FrictionCal_CalcMotion(FrictionCal_t *cal,
		const AxisKinematics_t *kinematics, const AxisLimits_t *limits);
bool FrictionCal_IsCalDone(FrictionCal_t *cal);

#endif /* INC_CALIBRATION_FRICTION_CAL_H_ */
