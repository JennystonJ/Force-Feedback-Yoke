/*
 * ffb_home.c
 *
 *  Created on: May 19, 2026
 *      Author: Jennyston
 */

#include "control/motion_command.h"
#include "control/ffb_home.h"
#include <math.h>

void FFBHome_Init(FFBHome_t *ffbHome, const FFBHomeConfig_t *config) {
	ffbHome->state = FFB_HOME_UNHOMED;
	ffbHome->searchMotorTorque = config->searchMotorTorque;
	ffbHome->searchVelocity = config->searchVelocity;
	ffbHome->searchAcceleration = config->searchAcceleration;

	ffbHome->discoveredRange.min = 0;
	ffbHome->discoveredRange.max = 0;
}

void FFBHome_Start(FFBHome_t *ffbHome) {
	ffbHome->state = FFB_HOME_START;
}

float FFBHome_GetSearchMotorTorque(FFBHome_t *ffbHome) {
	return ffbHome->searchMotorTorque;
}

MotionControlCommand_t FFBHome_CalcMotionCommand(FFBHome_t *ffbHome,
		const AxisKinematics_t *kinematics, float accelTarget,
		float deltaTime) {

	MotionControlCommand_t motion;
	switch(ffbHome->state) {
		case FFB_HOME_UNHOMED:
		case FFB_HOME_DONE:
			break;
		case FFB_HOME_FIND_START:
		{
			motion.type = MOTION_CONTROL_TYPE_VELOCITY;

			VelocityControlCommand_t *velCommand = &motion.data.velocityCommand;
			velCommand->velocityTarget = -ffbHome->searchVelocity;
			velCommand->torqueLimit = ffbHome->searchMotorTorque;
			velCommand->accelerationLimit = ffbHome->searchAcceleration;

			ffbHome->state = FFB_HOME_FIND_MIN;
			break;
		}
		case FFB_HOME_FIND_MIN:
		{
			motion.type = MOTION_CONTROL_TYPE_VELOCITY;

			VelocityControlCommand_t *velCommand = &motion.data.velocityCommand;
			velCommand->velocityTarget = -ffbHome->searchVelocity;
			velCommand->torqueLimit = ffbHome->searchMotorTorque;
			velCommand->accelerationLimit = ffbHome->searchAcceleration;

			if(accelTarget == 0 && kinematics->velocity > -1.5) {
				ffbHome->holdCount++;
				if(ffbHome->holdCount >= 500) {

					ffbHome->holdCount = 0;

					velCommand->velocityTarget = ffbHome->searchVelocity;
					velCommand->torqueLimit = ffbHome->searchMotorTorque;
					velCommand->accelerationLimit = ffbHome->searchAcceleration;

					// Store minimum position, now find maximum
					ffbHome->discoveredRange.min = kinematics->position;
					ffbHome->state = FFB_HOME_FIND_MAX;
				}
			}

			break;
		}
		case FFB_HOME_FIND_MAX:
		{
			motion.type = MOTION_CONTROL_TYPE_VELOCITY;

			VelocityControlCommand_t *velCommand = &motion.data.velocityCommand;
			velCommand->velocityTarget = ffbHome->searchVelocity;
			velCommand->torqueLimit = ffbHome->searchMotorTorque;
			velCommand->accelerationLimit = ffbHome->searchAcceleration;


			if(accelTarget == 0 && kinematics->velocity < 1.5) {
				ffbHome->holdCount++;
				if(ffbHome->holdCount >= 500) {

					ffbHome->holdCount = 0;

					velCommand->velocityTarget = 0;
					velCommand->torqueLimit = ffbHome->searchMotorTorque;
					velCommand->accelerationLimit = 0;

					// Store maximum position, now go to center
					ffbHome->discoveredRange.max = kinematics->position;
					ffbHome->state = FFB_HOME_CENTER;
				}
			}

			break;
		}
		case FFB_HOME_CENTER:
		{
			motion.type = MOTION_CONTROL_TYPE_POSITION;

			PositionControlCommand_t *posCommand = &motion.data.positionCommand;
			// Calculate center position
			float centerPosition = (ffbHome->discoveredRange.min +
					ffbHome->discoveredRange.max )/2;

			posCommand->accelerationLimit = ffbHome->searchAcceleration;
			posCommand->position = centerPosition;
			posCommand->torqueLimit = ffbHome->searchMotorTorque;
			posCommand->velocityLimit = ffbHome->searchVelocity;

			if(fabsf(kinematics->position - centerPosition) < 0.05f) {
				motion.type = MOTION_CONTROL_TYPE_TORQUE;
				TorqueControlCommand_t *torqueCommand = &motion.data.torqueCommand;
				torqueCommand->torqueLimit = 0;
				torqueCommand->torqueTarget = 0;

				ffbHome->state = FFB_HOME_DONE;
			}


			//			if(kinematics->position > centerPosition) {
			//				motion.targetVelocity = -ffbHome->searchVelocity;
			//				motion.torqueLimit = ffbHome->searchMotorTorque;
			//			}
			//			else {
			//				motion.targetVelocity = 0;
			//				motion.torqueLimit = 0;
			//				motion.accelerationLimit = 0;
			//
			//				ffbHome->state = FFB_HOME_DONE;
			//			}
			break;
		}
		default:
			// Invalid state, do nothing
			break;
	}

	return motion;
}

bool FFBHome_IsHomingDone(FFBHome_t *ffbHome) {
	return ffbHome->state == FFB_HOME_DONE;
}

AxisRange_t FFBHome_GetDiscoveredRange(FFBHome_t *ffbHome) {
	return ffbHome->discoveredRange;
}
