/*
 * motor.c
 *
 *  Created on: Feb 21, 2023
 *      Author: Jennyston
 */


#include "devices/motor.h"
#include "utilities/utilities.h"

void MotorInit(Motor_t *motor, TIM_HandleTypeDef *htim, uint32_t pwmCh,
		GPIO_t reverseGpio, GPIO_t forwardGpio) {
	motor->htim = htim;
	motor->pwmCh = pwmCh;
	motor->reverseGpio = reverseGpio;
	motor->forwardGpio = forwardGpio;
	motor->offset = 0;
	MotorSetDirection(motor, DIR_STOP);
}

void MotorStartPWM(Motor_t *motor) {
	//make sure motor is stopped
	MotorSetDirection(motor, DIR_STOP);

	HAL_TIM_PWM_Start(motor->htim, motor->pwmCh);
}

void MotorSetOffset(Motor_t *motor, uint16_t offset) {
	motor->offset = offset;
}

uint16_t MotorGetOffset(Motor_t *motor) {
	return motor->offset;
}

void MotorSetDirection(Motor_t *motor, MotorDirection_t dir) {

	//Set appropriate GPIO based on requested direction
	switch(dir) {
	case DIR_FORWARD:
		HAL_GPIO_WritePin(motor->forwardGpio.port, motor->forwardGpio.pin,
				GPIO_PIN_SET);
		HAL_GPIO_WritePin(motor->reverseGpio.port, motor->reverseGpio.pin,
				GPIO_PIN_RESET);
		break;
	case DIR_REVERSE:
		HAL_GPIO_WritePin(motor->forwardGpio.port, motor->forwardGpio.pin,
				GPIO_PIN_RESET);
		HAL_GPIO_WritePin(motor->reverseGpio.port, motor->reverseGpio.pin,
				GPIO_PIN_SET);
		break;
	default:
		break;
	}

	motor->direction = dir;

	MotorSetSpeed(motor, 0);
}

MotorDirection_t MotorGetDirection(Motor_t *motor) {
	return motor->direction;
}


void MotorSetSpeed(Motor_t *motor, uint16_t speed) {
	motor->speed = speed;

	if(motor->speed > 0) {
		uint32_t pwmVal = (uint32_t)motor->speed + motor->offset;
		__HAL_TIM_SET_COMPARE(motor->htim, motor->pwmCh, pwmVal);
	}
	else {
		__HAL_TIM_SET_COMPARE(motor->htim, motor->pwmCh, 0);
	}
}

uint16_t MotorGetSpeed(Motor_t *motor) {
	return motor->speed;
}

void MotorSetPower(Motor_t *motor, int32_t power) {
	//determine direction based on sign of power
	if(power < 0) {
		MotorSetDirection(motor, DIR_REVERSE);
	}
	else if(power > 0) {
		MotorSetDirection(motor, DIR_FORWARD);
	}

	MotorSetSpeed(motor, (uint16_t)Abs(power));
}

