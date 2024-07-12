/*
 * motor_controller.c
 *
 *  Created on: May 29, 2023
 *      Author: Jennyston
 */

#include "motor_controller.h"
#include <stdbool.h>

static float testCurrent;

static void MotorControllerPositionUpdate(MotorController_t *controller,
		float deltaTime);

static void MotorControllerCurrentUpdate(MotorController_t *controller,
		float deltaTime);

void MotorControllerInit(MotorController_t *controller,
		MotorControllerInit_t init) {
	controller->init = init;
//	controller->init.motor = motor;
//	controller->init.encoder = encoder;
//
//	controller->init.positionPid = positionPid;
//	controller->init.currentPid = currentPid;

	controller->mode = MOTOR_CONTROL_POWER;
	controller->currentSetPoint = 0;
	controller->positionSetPoint = 0;
}

void MotorControllerSetPower(MotorController_t *controller, int32_t power) {
	controller->mode = MOTOR_CONTROL_POWER;
	MotorSetPower(controller->init.motor, power);
}

//void MotorControllerSetPosition(MotorController_t *controller,
//		int32_t targetPosition) {
//	bool targetReached = false;
//	int steadyCount = 0;
//	while(!targetReached) {
//
//		/*
//		 * Calculate motor power to advance to target position based on current
//		 * position.
//		 */
//		int32_t currentPosition = RotaryEncGetCount(controller->init.encoder);
//		int32_t motorPower = ComputePID(controller->init.positionPid,
//				targetPosition, currentPosition);
//
//
//		//Minimum PID motor power
//		if(motorPower < 0) {
//			motorPower -= 100;
//		}
//		else if(motorPower > 0) {
//			motorPower += 100;
//		}
//
//		MotorSetPower(controller->init.motor, motorPower);
//
//		if(RotaryEncGetCount(controller->init.encoder) == targetPosition) {
//
//			steadyCount++;
//
//			//Target position is reached when encoder count is stable
//			if(steadyCount == 50) {
//				MotorSetPower(controller->init.motor, 0);
//
//				//terminate loop
//				targetReached = true;
//			}
//		}
//		else {
//
//			/*
//			 * Reset steady count when encoder count does not match target
//			 * position
//			 */
//			steadyCount = 0;
//		}
//
//		HAL_Delay(10);
//
//	}
//}

void MotorControllerSetPosition(MotorController_t *controller,
		int32_t targetPosition) {



	bool targetReached = false;
	int steadyCount = 0;
	while(!targetReached) {

		/*
		 * Calculate motor power to advance to target position based on current
		 * position.
		 */
		int32_t currentPosition = RotaryEncGetCount(controller->init.encoder);
		int32_t motorPower = CalcPID(controller->init.positionPid,
				targetPosition, currentPosition);


		//Minimum PID motor power
		if(motorPower < 0) {
			motorPower -= 100;
		}
		else if(motorPower > 0) {
			motorPower += 100;
		}

		MotorSetPower(controller->init.motor, motorPower);

		if(RotaryEncGetCount(controller->init.encoder) == targetPosition) {

			steadyCount++;

			//Target position is reached when encoder count is stable
			if(steadyCount == 50) {
				MotorSetPower(controller->init.motor, 0);

				//terminate loop
				targetReached = true;
			}
		}
		else {

			/*
			 * Reset steady count when encoder count does not match target
			 * position
			 */
			steadyCount = 0;
		}

		HAL_Delay(10);

	}
}

void MotorControllerSetCurrent(MotorController_t *controller, float current) {
	controller->currentSetPoint = current;
	controller->mode = MOTOR_CONTROL_CURRENT;
}

int32_t MotorControllerGetPosition(MotorController_t *controller) {
	return RotaryEncGetCount(controller->init.encoder);
}

float MotorControllerGetCurrent(MotorController_t *controller) {
	return CurrentSenseGetCurrent(controller->init.currentSensor);
}

float MotorControllerGetSpeed(MotorController_t *controller) {
	return RotaryEncGetSpeed(controller->init.encoder);
}

void MotorControllerUpdate(MotorController_t *controller, float deltaTime) {
	if(controller->mode == MOTOR_CONTROL_POSITION) {
		MotorControllerPositionUpdate(controller, deltaTime);
	}
	else if(controller->mode == MOTOR_CONTROL_CURRENT) {
		MotorControllerCurrentUpdate(controller, deltaTime);
	}
}

//TODO: implement
static void MotorControllerPositionUpdate(MotorController_t *controller,
		float deltaTime) {

}

static void MotorControllerCurrentUpdate(MotorController_t *controller,
		float deltaTime) {
	float actualCurrent = CurrentSenseGetCurrent(
			controller->init.currentSensor);

	//determine actual current direction
	if(MotorGetDirection(controller->init.motor) == DIR_FORWARD) {
		//do nothing
	}
	else if(MotorGetDirection(controller->init.motor) == DIR_REVERSE) {
		//flip actual current direction
		actualCurrent *= -1;
	}

	//calculate PID for motor output power
	int32_t motorPower = CalcPID(controller->init.currentPid,
			controller->currentSetPoint, actualCurrent);
	MotorSetPower(controller->init.motor, motorPower);

	testCurrent = actualCurrent;
}
