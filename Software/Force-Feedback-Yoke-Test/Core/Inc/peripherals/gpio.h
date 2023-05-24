/*
 * gpio.h
 *
 *  Created on: Mar 2, 2023
 *      Author: Jennyston
 */

#ifndef INC_PERIPHERALS_GPIO_H_
#define INC_PERIPHERALS_GPIO_H_

#include "stm32f3xx_hal.h"
#include <stdint.h>

typedef enum {
	GPIO_HIGH,
	GPIO_LOW
}GPIOState;

typedef struct GPIO {
	GPIO_TypeDef *port;
	uint16_t pin;
} GPIO_t;

void GPIOInit(GPIO_t *gpio, GPIO_TypeDef *port, uint16_t pin);
GPIOState GPIOGetState(GPIO_t *gpio);
void GPIOSetState(GPIO_t *gpio, GPIOState state);

#endif /* INC_PERIPHERALS_GPIO_H_ */
