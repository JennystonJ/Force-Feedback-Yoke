/*
 * friction_bias_cal.h
 *
 *  Created on: Jun 5, 2026
 *      Author: Jennyston
 */

#ifndef INC_CALIBRATION_FRICTION_BIAS_CAL_H_
#define INC_CALIBRATION_FRICTION_BIAS_CAL_H_

#include "control/axis_kinematics.h"
#include "control/motion_command.h"
#include <stdbool.h>

typedef enum FrictionBiasCalState {
	FRICTION_BIAS_CAL_STATE_IDLE,
	FRICTION_BIAS_CAL_STATE_START,
	FRICTION_BIAS_CAL_STATE_FORWARD,
	FRICTION_BIAS_CAL_STATE_REVERSE,
	FRICTION_BIAS_CAL_STATE_DONE
} FrictionBiasCalState_e;

typedef struct FrictionBiasCal {
	FrictionBiasCalState_e state;

	float torqueSampleAccumulator;
	int torqueSampleCount;

	float forwardTorque;
	float reverseTorque;

	float biasTorque;
} FrictionBiasCal_t;

void FrictionBiasCal_Init(FrictionBiasCal_t *biasCal);
void FrictionBiasCal_Start(FrictionBiasCal_t *biasCal);
MotionControlCommand_t FrictionBiasCal_CalcMotionControlCommand(FrictionBiasCal_t *biasCal,
		const AxisKinematics_t *kinematics);
bool FrictionBiasCal_IsDone(FrictionBiasCal_t *biasCal);

float FrictionBiasCal_GetBiasTorqueResult(FrictionBiasCal_t *biasCal);

#endif /* INC_CALIBRATION_FRICTION_BIAS_CAL_H_ */
