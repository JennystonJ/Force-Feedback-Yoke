/*
 * motor.c
 *
 *  Created on: Mar 18, 2024
 *      Author: Jennyston
 */

#include "motor.h"
#include "utilities/utilities.h"
#include <stdbool.h>

void MotorInit(Motor_t *motor, MotorInterface_t interface) {
	motor->interface = interface;
}

int MotorGetPower(Motor_t *motor) {
	return motor->interface.MotorGetPower(&motor->interface);
}

void MotorSetPower(Motor_t *motor, int power) {
	motor->interface.MotorSetPower(&motor->interface, power);
}
