/*
 * static_friction_cal.c
 *
 *  Created on: Jun 26, 2026
 *      Author: Jennyston
 */

#include "calibration/static_friction_cal.h"
#include "math.h"
#include "log.h"

void StaticFrictionCal_Init(StaticFrictionCal_t *cal,
		const StaticFrictionCalConfig_t *config) {
	cal->state = STATIC_FRICTION_CAL_STATE_IDLE;
	cal->config = config;

	cal->testCount = 0;
	cal->settleTime = 0;
	cal->torqueSum = 0;
	cal->currentTorque = 0;
	cal->lastPosition = 0;
	cal->breakawayTorque = 0;
}

void StaticFrictionCal_Start(StaticFrictionCal_t *cal) {
	cal->testCount = 0;
	cal->settleTime = 0;
	cal->torqueSum = 0;
	cal->currentTorque = 0;
	cal->lastPosition = 0;
	cal->breakawayTorque = 0;

	Log_Print(LOG_LEVEL_INFO, __FILE__, __LINE__,
				"Starting static friction calibration...");
	cal->state = STATIC_FRICTION_CAL_STATE_CENTERING;
}

MotionControlCommand_t StaticFrictionCal_CalcMotion(StaticFrictionCal_t *cal,
		const AxisKinematics_t *kinematics, float deltaTime) {

	MotionControlCommand_t motion;

	switch(cal->state) {
		case STATIC_FRICTION_CAL_STATE_IDLE:
			// Calibration has not been started
			motion.type = MOTION_CONTROL_TYPE_TORQUE;
			motion.data.torqueCommand.torqueLimit = 0.0f;
			motion.data.torqueCommand.torqueTarget = 0.0f;
			break;
		case STATIC_FRICTION_CAL_STATE_CENTERING:
			motion.type = MOTION_CONTROL_TYPE_POSITION;
			PositionControlCommand_t *posCommand = &motion.data.positionCommand;
			posCommand->accelerationLimit = 16.0f;
			posCommand->torqueLimit = 0.5f;
			posCommand->velocityLimit = 6.28;
			posCommand->position = 0.0f;

			if(fabsf(kinematics->position) < M_PI) {
				cal->state = STATIC_FRICTION_CAL_STATE_PAUSE;
			}
			break;
		case STATIC_FRICTION_CAL_STATE_PAUSE:
			// Turn off motor and wait for position to settle after centering
			motion.type = MOTION_CONTROL_TYPE_TORQUE;
			motion.data.torqueCommand.torqueLimit = 0.0f;
			motion.data.torqueCommand.torqueTarget = 0.0f;

			cal->settleTime += deltaTime;
			if(cal->settleTime >= cal->config->maxSettleTime) {
				cal->settleTime = 0;
				cal->currentTorque = 0;
				cal->lastPosition = kinematics->position;
				cal->state = STATIC_FRICTION_CAL_STATE_RUNNING;
			}
		case STATIC_FRICTION_CAL_STATE_RUNNING:
			motion.type = MOTION_CONTROL_TYPE_TORQUE;
			motion.data.torqueCommand.torqueLimit = 1.0f;
			// Alternate between forward and revere directions
			motion.data.torqueCommand.torqueTarget = cal->testCount % 2 == 0 ?
					cal->currentTorque : -cal->currentTorque;
			cal->settleTime+= deltaTime;
			if(cal->settleTime >= cal->config->maxSettleTime) {
				cal->settleTime = 0;

				if(fabs(kinematics->position - cal->lastPosition) > M_PI/2) {
					// Record to torque sum
					cal->torqueSum += fabsf(cal->currentTorque);
					cal->testCount++;

					if(cal->testCount >= cal->config->maxTests) {
						// Calibration data collection is complete
						// Calculate breakaway torque
						cal->breakawayTorque = cal->torqueSum / cal->testCount;

						motion.type = MOTION_CONTROL_TYPE_TORQUE;
						motion.data.torqueCommand.torqueLimit = 0.0f;
						motion.data.torqueCommand.torqueTarget = 0.0f;


						Log_Print(LOG_LEVEL_INFO, __FILE__, __LINE__,
									"Static friction calibration complete: " \
									"Breakaway torque: %f",
									cal->breakawayTorque);

						cal->state = STATIC_FRICTION_CAL_STATE_IDLE;
					}
					else {
						// Go to center for next test
						cal->currentTorque = 0;
						cal->state = STATIC_FRICTION_CAL_STATE_CENTERING;
					}
				}
				else {
					cal->currentTorque += cal->config->torqueStepRate;
					cal->state = STATIC_FRICTION_CAL_STATE_RUNNING;
				}
			}

			break;
		default:
			// Invalid state, do nothing
	}

	return motion;
}

bool StaticFrictionCal_IsDone(StaticFrictionCal_t *cal) {
	return cal->state == STATIC_FRICTION_CAL_STATE_IDLE;
}

