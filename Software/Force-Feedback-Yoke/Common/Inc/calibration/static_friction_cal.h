/*
 * static_friction_cal.h
 *
 *  Created on: Jun 26, 2026
 *      Author: Jennyston
 */

#ifndef INC_CALIBRATION_STATIC_FRICTION_CAL_H_
#define INC_CALIBRATION_STATIC_FRICTION_CAL_H_

#include "control/motion_command.h"
#include "control/axis_kinematics.h"
#include "config/calibration_config.h"
#include <stdbool.h>

typedef enum StaticFrictionCalState {
	STATIC_FRICTION_CAL_STATE_IDLE,
	STATIC_FRICTION_CAL_STATE_CENTERING,
	STATIC_FRICTION_CAL_STATE_PAUSE,
	STATIC_FRICTION_CAL_STATE_RUNNING,
} StaticFrictionCalState_e;

typedef struct StaticFrictionCal {
	const StaticFrictionCalConfig_t *config;

	StaticFrictionCalState_e state;

	int testCount;
	float settleTime;
	float torqueSum;
	float currentTorque;
	float lastPosition;

	float breakawayTorque;
} StaticFrictionCal_t;

void StaticFrictionCal_Init(StaticFrictionCal_t *cal,
		const StaticFrictionCalConfig_t *config);

void StaticFrictionCal_Start(StaticFrictionCal_t *cal);
MotionControlCommand_t StaticFrictionCal_CalcMotion(StaticFrictionCal_t *cal,
		const AxisKinematics_t *kinematics, float deltaTime);

bool StaticFrictionCal_IsDone(StaticFrictionCal_t *cal);

#endif /* INC_CALIBRATION_STATIC_FRICTION_CAL_H_ */
