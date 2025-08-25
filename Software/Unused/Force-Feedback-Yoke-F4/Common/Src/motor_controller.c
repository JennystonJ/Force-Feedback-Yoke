/*
 * motor_controller.c
 *
 *  Created on: Nov 8, 2024
 *      Author: Jennyston
 */

#include "motor_controller.h"

void MotorControllerInit(MotorController_t *controller, Motor_t *motor,
		CurrentSensor_t *currentSensor) {
	controller->motor = motor;
	controller->currentSensor = currentSensor;
	controller->kT = 1;

	PIDInit(&controller->pid);
	PIDSetKP(&controller->pid, 1);
	PIDSetKI(&controller->pid, 0);
	PIDSetKD(&controller->pid, 0);
}

void MotorControllerSetTorque(MotorController_t *controller, float torque) {
	controller->setPointCurrent = controller->kT * torque;
}

void MotorControllerSetKT(MotorController_t *controller, float kT) {
	controller->kT = kT;
}

float MotorControllerGetKT(MotorController_t *controller) {
	return controller->kT;
}

void MotorControllerUpdate(MotorController_t *controller) {
	int output = CalcPID(&controller->pid, controller->setPointCurrent,
			CurrentSensorGetCurrent(controller->currentSensor));
	MotorSetPower(controller->motor, output);
}
