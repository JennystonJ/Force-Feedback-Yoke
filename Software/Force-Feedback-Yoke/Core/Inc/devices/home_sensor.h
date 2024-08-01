/*
 * home_sensor.h
 *
 *  Created on: May 28, 2023
 *      Author: Jennyston
 */

#ifndef INC_DEVICES_HOME_SENSOR_H_
#define INC_DEVICES_HOME_SENSOR_H_

#include <stm32f4xx.h>
#include <stdint.h>
#include "motor.h"
#include "peripherals/gpio.h"

#define HOME_MOTOR_MAX_SPEED 1400
#define HOME_MOTOR_MIN_SPEED 1100

typedef struct HomeSensor {
	GPIO_t gpio;

} HomeSensor_t;

/**
 * Initializes home sensor structure.
 * parameter homeSensor: pointer to home sensor structure.
 * parameter gpio: home sensor GPIO
 */
void HomeSensorInit(HomeSensor_t *homeSensor, GPIO_t gpio);

/**
 * Moves motor to home position.
 * parameter homeSensor: pointer to home sensor structure.
 * parameter motor: pointer to structure of motor to be moved.
 */
void HomeSensorHome(HomeSensor_t *homeSensor, Motor_t *motor);

#endif /* INC_DEVICES_HOME_SENSOR_H_ */
