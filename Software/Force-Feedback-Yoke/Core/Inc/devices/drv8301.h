/*
 * DRV8301.h
 *
 *  Created on: Jun 20, 2025
 *      Author: Jennyston
 */

#ifndef INC_DEVICES_DRV8301_H_
#define INC_DEVICES_DRV8301_H_

#include <stm32h7xx.h>
#include "peripherals/gpio.h"
#include <stdbool.h>

#define DRV8301_MAX_PWM (6000-1)

typedef struct DRV8301 {
	GPIO_t driverEn;

	TIM_HandleTypeDef *pwmTim;
	uint32_t pwmChU;
	uint32_t pwmChV;
	uint32_t pwmChW;

	float dutyU;
	float dutyV;
	float dutyW;

	float busVoltage;
} DRV8301_t;

void DRV8301_Init(DRV8301_t *driver, GPIO_t driverEn, TIM_HandleTypeDef *pwmTim,
		uint32_t pwmChU, uint32_t pwmChV, uint32_t pwmChW, float busVoltage);
void DRV8301_SetDriverEnable(DRV8301_t *driver, bool enable);
void DRV8301_SetPhaseVoltages(DRV8301_t *driver, float u, float v, float w);
void DRV8301_SetPhaseDutyCycles(DRV8301_t *driver, float u, float v, float w);
float DRV8301_GetBusVoltage(DRV8301_t *driver);

#endif /* INC_DEVICES_DRV8301_H_ */
