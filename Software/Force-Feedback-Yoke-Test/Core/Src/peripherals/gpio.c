/*
 * gpio.c
 *
 *  Created on: Mar 2, 2023
 *      Author: Jennyston
 */

#include "../Inc/peripherals/gpio.h"

void GPIOInit(GPIO_t *gpio, GPIO_TypeDef *port, uint16_t pin) {
	gpio->port = port;
	gpio->pin = pin;
}

GPIOState GPIOGetState(GPIO_t *gpio) {
	return HAL_GPIO_ReadPin(gpio->port, gpio->pin) == GPIO_PIN_SET ?
			GPIO_HIGH : GPIO_LOW;
}

void GPIOSetState(GPIO_t *gpio, GPIOState state) {
	HAL_GPIO_WritePin(gpio->port, gpio->pin, state == GPIO_HIGH ? GPIO_PIN_SET :
			GPIO_PIN_RESET);
}
