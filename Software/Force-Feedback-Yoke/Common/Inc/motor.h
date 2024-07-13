/*
 * motor.h
 *
 *  Created on: Mar 18, 2024
 *      Author: Jennyston
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MOTOR_POWER_MAX (2400-1)

typedef struct Motor {
	void(*SetPower)(int power);
	int(*GetPower)();
} Motor_t;

void MotorInit(Motor_t *motor, void(*SetPower)(int power),
		int(*GetPower)());

void MotorSetPower(Motor_t *motor, int power);
int MotorGetPower(Motor_t *motor);


#ifdef __cplusplus
}
#endif

#endif /* INC_MOTOR_H_ */
