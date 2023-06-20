/*
 * motor_controller.h
 *
 *  Created on: May 29, 2023
 *      Author: Jennyston
 */

#ifndef INC_MOTOR_CONTROLLER_H_
#define INC_MOTOR_CONTROLLER_H_

#include "devices/motor.h"
#include "rotary_encoder.h"
#include "devices/ina219.h"
#include "pid.h"
#include <stdint.h>

#define MOTOR_CONTROL_MAX_DPS 100
//#define MOTOR_CONTROL_MAX_ACCEL 50
//#define MOTOR_CONTROL_MAX_JERK 25

typedef enum {
	MOTOR_CONTROL_POWER,
	MOTOR_CONTROL_POSITION,
	MOTOR_CONTROL_CURRENT,
} MotorControllerMode;

typedef struct MotorControllerInit {
	Motor_t *motor;
	RotaryEncoder_t *encoder;
	Ina219_t *currentSensor;
	PID_t *speedPid;
//	PID_t *accelPid;
//	PID_t *jerkPid;
	PID_t *positionPid;
	PID_t *currentPid;
} MotorControllerInit_t;

typedef struct MotorController {
	MotorControllerInit_t init;
	int32_t positionSetPoint;
	float currentSetPoint;
	MotorControllerMode mode;
} MotorController_t;

void MotorControllerInit(MotorController_t *controller,
		MotorControllerInit_t init);
void MotorControllerSetPower(MotorController_t *controller, int32_t power);
void MotorControllerSetPosition(MotorController_t *controller,
		int32_t targetPosition);
void MotorControllerSetCurrent(MotorController_t *controller, float current);
int32_t MotorControllerGetPosition(MotorController_t *controller);
float MotorControllerGetCurrent(MotorController_t *controller);
float MotorControllerGetSpeed(MotorController_t *controller);
void MotorControllerUpdate(MotorController_t *controller, float deltaTime);

#endif /* INC_MOTOR_CONTROLLER_H_ */
