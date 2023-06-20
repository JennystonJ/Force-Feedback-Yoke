/*
 * motor_logger.h
 *
 *  Created on: Jun 2, 2023
 *      Author: Jennyston
 */

#ifndef INC_TESTING_MOTOR_LOGGER_H_
#define INC_TESTING_MOTOR_LOGGER_H_

#include "motor_controller.h"
#include <stdint.h>

#define MOTOR_LOGGER_A_MAX_POINTS 100

typedef struct MotorLogger {
	MotorController_t *controller;
} MotorLogger_t;

void MotorLoggerInit(MotorLogger_t *mLogger, MotorController_t *controller);
void MotorLoggerVRun(MotorLogger_t *mLogger, int32_t maxPower,
		int32_t rampTime);
void MotorLoggerARun(MotorLogger_t *mLogger, int32_t power, int32_t timeStep);

#endif /* INC_TESTING_MOTOR_LOGGER_H_ */
