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

#define BTS7960_MAX_PWM_POWER (2400-1)

// Compensate for difference in forward and reverse power
#define BTS7960_FORWARD_DIR_POWER_SCALE 1.0f
#define BTS7960_REVERSE_DIR_POWER_SCALE 1.0f

typedef enum {
	BTS7960_POWER_BRAKE,
	BTS7960_POWER_COAST,
} BTS7960ControlMode_e;

typedef struct BTS7960 {
	bool enableInit;
	GPIO_t enable;
	GPIO_t forwardEn;
	GPIO_t reverseEn;

	TIM_HandleTypeDef *htim;

	uint32_t forwardPwmCh;
	uint32_t reversePwmCh;

	int power;
	bool driverEStop;

	BTS7960ControlMode_e controlMode;
} BTS7960_t;

void BTS7960InitEn(BTS7960_t *driver, TIM_HandleTypeDef *htim,
		uint32_t forwardPwmCh, uint32_t reversePwmCh, GPIO_t enable);
void BTS7960InitPowerBrake(BTS7960_t *driver, TIM_HandleTypeDef *htim,
		uint32_t forwardPwmCh, uint32_t reversePwmCh);
void BTS7960InitPowerCoast(BTS7960_t *driver, TIM_HandleTypeDef *htim,
		uint32_t pwmCh, GPIO_t forwardEn, GPIO_t reverseEn);
void BTS7960SetPower(BTS7960_t *driver, int power);
int BTS7960GetPower(BTS7960_t *driver);
void BTS7960SetDriverEStop(BTS7960_t *driver, bool estop);

#endif /* INC_DEVICES_BTS7960_H_ */
