/*
 * bts7960.h
 *
 *  Created on: Jul 12, 2024
 *      Author: Jennyston
 */

#ifndef INC_DEVICES_BTS7960_H_
#define INC_DEVICES_BTS7960_H_

#include "peripherals/gpio.h"
#include <stm32f3xx.h>
#include <stdint.h>

#define BTS7690_MAX_PWM_POWER (2400-1)

typedef struct BTS7960 {
	GPIO_t forwardEn;
	GPIO_t reverseEn;
	TIM_HandleTypeDef *htim;
	uint32_t forwardPwmCh;
	uint32_t reversePwmCh;
	int power;
} BTS7960_t;

void BTS7960Init(BTS7960_t *driver, GPIO_t forwardEn, GPIO_t reverseEn,
		TIM_HandleTypeDef *htim, uint32_t forwardPwmCh, uint32_t reversePwmCh);
void BTS7960SetPower(BTS7960_t *driver, int power);
int BTS7960GetPower(BTS7960_t *driver);

#endif /* INC_DEVICES_BTS7960_H_ */
