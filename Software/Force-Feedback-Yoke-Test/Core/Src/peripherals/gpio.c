/*
 * gpio.c
 *
 *  Created on: Mar 2, 2023
 *      Author: Jennyston
 */

#include "peripherals/gpio.h"

void GPIOInit(GPIO_t *gpio, GPIO_TypeDef *port, uint16_t pin) {
	gpio->port = port;
	gpio->pin = pin;
//	gpio->hcomp = NULL;
}

//void GPIOInitComp(GPIO_t *gpio, COMP_HandleTypeDef *hcomp) {
//	gpio->port = NULL;
//	gpio->pin = 0;
//	gpio->hcomp = hcomp;
//}

GPIOState GPIOGetState(GPIO_t *gpio) {
	if(gpio->port != NULL) {
		return HAL_GPIO_ReadPin(gpio->port, gpio->pin) == GPIO_PIN_SET ?
				GPIO_HIGH : GPIO_LOW;
	}
//	else if (gpio->hcomp != NULL) {
//		return HAL_COMP_GetOutputLevel(gpio->hcomp) == COMP_OUTPUTLEVEL_HIGH ?
//				GPIO_HIGH : GPIO_LOW;
//	}
	else {
		return GPIO_LOW;
	}
}

void GPIOSetState(GPIO_t *gpio, GPIOState state) {
	if(gpio->port != NULL) {
		HAL_GPIO_WritePin(gpio->port, gpio->pin, state == GPIO_HIGH ?
				GPIO_PIN_SET : GPIO_PIN_RESET);
	}
}
