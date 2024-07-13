/*
 * motor.c
 *
 *  Created on: Mar 18, 2024
 *      Author: Jennyston
 */

#include "motor.h"
#include "utilities/utilities.h"
#include <stdbool.h>

void MotorInit(Motor_t *motor, void(*SetPower)(int power),
		int(*GetPower)()) {
	motor->SetPower = SetPower;
	motor->GetPower = GetPower;
}

void MotorSetPower(Motor_t *motor, int power) {
	motor->SetPower(power);
}

int MotorGetPower(Motor_t *motor) {
	return motor->GetPower();
}
