/*
 * ffb_home.h
 *
 *  Created on: May 19, 2026
 *      Author: Jennyston
 */

#ifndef INC_CONTROL_FFB_HOME_H_
#define INC_CONTROL_FFB_HOME_H_

#include <control/motion_command.h>
#include "axis_kinematics.h"
#include "config/ffb_axis_config.h"
#include <stdbool.h>

typedef enum FFBHomeState {
	FFB_HOME_UNHOMED,
	FFB_HOME_START,
	FFB_HOME_FIND_MIN,
	FFB_HOME_FIND_MAX,
	FFB_HOME_CENTER,
	FFB_HOME_DONE
} FFBAxisHome_e;

typedef struct FFBHome {
	FFBAxisHome_e state;
	float searchMotorTorque;
	float searchVelocity;
	float searchAcceleration;
	int holdCount;

	AxisRange_t discoveredRange;
} FFBHome_t;

void FFBHome_Init(FFBHome_t *ffbHome, const FFBHomeConfig_t *config);
void FFBHome_Start(FFBHome_t *ffbHome);
float FFBHome_GetSearchMotorTorque(FFBHome_t *ffbHome);
MotionControlCommand_t FFBHome_CalcMotionCommand(FFBHome_t *ffbHome,
		const AxisKinematics_t *kinematics, float accelTarget,
		float deltaTime);
bool FFBHome_IsHomingDone(FFBHome_t *ffbHome);
AxisRange_t FFBHome_GetDiscoveredRange(FFBHome_t *ffbHome);

#endif /* INC_CONTROL_FFB_HOME_H_ */
