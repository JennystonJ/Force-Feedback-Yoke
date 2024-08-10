/*
 * bts7960.h
 *
 *  Created on: Jul 12, 2024
 *      Author: Jennyston
 */

#ifndef INC_DEVICES_BTS7960_H_
#define INC_DEVICES_BTS7960_H_

#include "peripherals/gpio.h"
#include <stm32f4xx.h>
#include <stdint.h>
#include <stdbool.h>

#define BTS7690_MAX_PWM_POWER (4800-1)

// Compensate for difference in forward and reverse power
#define BTS7690_FORWARD_DIR_POWER_SCALE 1.0f
#define BTS7690_REVERSE_DIR_POWER_SCALE 1.0f

typedef struct BTS7960 {
	bool enableInit;
	GPIO_t forwardEn;
	GPIO_t reverseEn;
	TIM_HandleTypeDef *htim;
	uint32_t forwardPwmCh;
	uint32_t reversePwmCh;
	int power;
} BTS7960_t;

void BTS7960InitEn(BTS7960_t *driver, GPIO_t forwardEn, GPIO_t reverseEn,
		TIM_HandleTypeDef *htim, uint32_t forwardPwmCh, uint32_t reversePwmCh);
void BTS7960Init(BTS7960_t *driver, TIM_HandleTypeDef *htim,
		uint32_t forwardPwmCh, uint32_t reversePwmCh);
void BTS7960SetPower(BTS7960_t *driver, int power);
int BTS7960GetPower(BTS7960_t *driver);

#endif /* INC_DEVICES_BTS7960_H_ */
