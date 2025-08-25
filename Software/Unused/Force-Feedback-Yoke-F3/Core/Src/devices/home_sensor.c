/*
 * home_sensor.c
 *
 *  Created on: May 28, 2023
 *      Author: Jennyston
 */

#include "devices/home_sensor.h"

void HomeSensorInit(HomeSensor_t *homeSensor, GPIO_t gpio) {
	homeSensor->gpio = gpio;
}

void HomeSensorHome(HomeSensor_t *homeSensor, Motor_t *motor) {

//	//get motor spinning
//	MotorSetPower(motor, HOME_MOTOR_MAX_SPEED);
//	HAL_Delay(1000);

	//run motor at max speed and find home position
	MotorSetPower(motor, HOME_MOTOR_MAX_SPEED);
	while(GPIOGetState(&(homeSensor->gpio)) == GPIO_LOW) {
		//wait (do nothing)
	}

	//dead time
	MotorSetPower(motor, 0);
	HAL_Delay(500);

	//home position has been found, back off slowly
	MotorSetPower(motor, -HOME_MOTOR_MIN_SPEED);
	while(GPIOGetState(&(homeSensor->gpio)) == GPIO_HIGH) {
		//wait (do nothing)
	}
	HAL_Delay(250);

	//dead time
	MotorSetPower(motor, 0);
	HAL_Delay(500);

	//move forward back to home position slowly
	MotorSetPower(motor, HOME_MOTOR_MIN_SPEED);
	while(GPIOGetState(&(homeSensor->gpio)) == GPIO_LOW) {
		//wait (do nothing)
	}

	MotorSetPower(motor, 0);

	//done
}

