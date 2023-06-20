/*
 * motor.h
 *
 *  Created on: Feb 21, 2023
 *      Author: Jennyston
 */

#ifndef INC_DEVICES_MOTOR_H_
#define INC_DEVICES_MOTOR_H_

#include <stm32f3xx.h>
#include <stdint.h>
#include "../peripherals/gpio.h"

#define MAX_MOTOR_PWM 65535
#define MIN_MOTOR_PWM 0

typedef enum MotorDirection {
	DIR_REVERSE,
	DIR_STOP,
	DIR_FORWARD
} MotorDirection_t;

typedef struct Motor{
	TIM_HandleTypeDef *htim;
	uint32_t pwmCh;
	GPIO_t forwardGpio;
	GPIO_t reverseGpio;
	MotorDirection_t direction;
	uint16_t speed;
	uint16_t offset;
} Motor_t;

	void MotorInit(Motor_t *motor, TIM_HandleTypeDef *htim, uint32_t pwmCh,
			GPIO_t reverseGpio, GPIO_t forwardGpio);
	void MotorStartPWM(Motor_t *motor);
	void MotorSetOffset(Motor_t *motor, uint16_t offset);
	uint16_t MotorGetOffset(Motor_t *motor);
	void MotorSetDirection(Motor_t *motor, MotorDirection_t dir);
	MotorDirection_t MotorGetDirection(Motor_t *motor);
	void MotorSetSpeed(Motor_t *motor, uint16_t speed);
	uint16_t MotorGetSpeed(Motor_t *motor);
	void MotorSetPower(Motor_t *motor, int32_t power);

#endif /* INC_DEVICES_MOTOR_H_ */
