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

typedef struct MotorInterface MotorInterface_t;

struct MotorInterface {
	void *hardwareMotor;
	int (*MotorGetPower)(MotorInterface_t *motor);
	void (*MotorSetPower)(MotorInterface_t *motor, int power);
};

typedef struct Motor {
	MotorInterface_t interface;
} Motor_t;

void MotorInit(Motor_t *motor, MotorInterface_t interface);
int MotorGetPower(Motor_t *motor);
void MotorSetPower(Motor_t *motor, int power);


#ifdef __cplusplus
}
#endif

#endif /* INC_MOTOR_H_ */
