/*
 * motor_controller.h
 *
 *  Created on: Nov 8, 2024
 *      Author: Jennyston
 */

#ifndef INC_MOTOR_CONTROLLER_H_
#define INC_MOTOR_CONTROLLER_H_

#include "current_sensor.h"
#include "motor.h"
#include "pid.h"

#define MOTOR_CONTROLLER_DEFAULT_KP 1
#define MOTOR_CONTROLLER_DEFAULT_KI 0
#define MOTOR_CONTROLLER_DEFAULT_KD 0

typedef struct MotorController {
	Motor_t *motor;
	CurrentSensor_t *currentSensor;
	float kT;
	PID_t pid;
	float setPointCurrent;
} MotorController_t;

void MotorControllerInit(MotorController_t *controller, Motor_t *motor,
		CurrentSensor_t *currentSensor);
void MotorControllerSetTorque(MotorController_t *controller, float torque);
void MotorControllerSetKT(MotorController_t *controller, float kT);
float MotorControllerGetKT(MotorController_t *controller);
void MotorControllerUpdate(MotorController_t *controller);

#endif /* INC_MOTOR_CONTROLLER_H_ */
