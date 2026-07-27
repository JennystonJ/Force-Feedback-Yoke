/*
 * friction_bias_cal.c
 *
 *  Created on: Jun 5, 2026
 *      Author: Jennyston
 */

#include "calibration/friction_bias_cal.h"

void FrictionBiasCal_Init(FrictionBiasCal_t *biasCal) {
	biasCal->state = FRICTION_BIAS_CAL_STATE_IDLE;

	biasCal->forwardTorque = 0;
	biasCal->reverseTorque = 0;
	biasCal->biasTorque = 0;
	biasCal->torqueSampleAccumulator = 0;
	biasCal->torqueSampleCount = 0;
}

void FrictionBiasCal_Start(FrictionBiasCal_t *biasCal) {
	biasCal->biasTorque = 0;
	biasCal->torqueSampleAccumulator = 0;
	biasCal->torqueSampleCount = 0;

	biasCal->state = FRICTION_BIAS_CAL_STATE_START;
}

MotionControlCommand_t FrictionBiasCal_CalcMotionControlCommand(
	FrictionBiasCal_t *biasCal, const AxisKinematics_t *kinematics) {

	MotionControlCommand_t motion;

	switch(biasCal->state) {
		case FRICTION_BIAS_CAL_STATE_IDLE:
			break;
		case FRICTION_BIAS_CAL_STATE_START:
			motion.data.velocityCommand.velocityTarget = -3;
			motion.data.velocityCommand.accelerationLimit = 16.0f;
			motion.data.velocityCommand.torqueLimit = 0.15f;
			break;
		case FRICTION_BIAS_CAL_STATE_FORWARD:
			break;
		case FRICTION_BIAS_CAL_STATE_REVERSE:
			break;
		case FRICTION_BIAS_CAL_STATE_DONE:
			break;
		default:
			// Invalid state, do nothing
	}
}

bool FrictionBiasCal_IsDone(FrictionBiasCal_t *biasCal) {

}


float FrictionBiasCal_GetBiasTorqueResult(FrictionBiasCal_t *biasCal) {

}

