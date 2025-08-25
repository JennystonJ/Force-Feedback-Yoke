/*
 * gpio.h
 *
 *  Created on: Mar 2, 2023
 *      Author: Jennyston
 */

#ifndef INC_PERIPHERALS_GPIO_H_
#define INC_PERIPHERALS_GPIO_H_

#include "stm32f4xx.h"
#include <stdint.h>

typedef enum {
	GPIO_HIGH,
	GPIO_LOW
}GPIOState;

typedef struct GPIO {
	GPIO_TypeDef *port;
	uint16_t pin;
//	COMP_HandleTypeDef *hcomp;
} GPIO_t;

void GPIOInit(GPIO_t *gpio, GPIO_TypeDef *port, uint16_t pin);
//void GPIOInitComp(GPIO_t *gpio, COMP_HandleTypeDef *hcomp);
GPIOState GPIOGetState(GPIO_t *gpio);
void GPIOSetState(GPIO_t *gpio, GPIOState state);

#endif /* INC_PERIPHERALS_GPIO_H_ */
