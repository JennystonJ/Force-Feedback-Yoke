/*
 * DRV8301.c
 *
 *  Created on: Jun 20, 2025
 *      Author: Jennyston
 */

#include <devices/drv8301.h>
#include "utilities/utilities.h"

static inline void SetPWMDutyCycle(TIM_HandleTypeDef *htim, uint32_t channel,
		float dutyCycle);

void DRV8301_Init(DRV8301_t *driver, GPIO_t driverEn, TIM_HandleTypeDef *pwmTim,
		uint32_t pwmChU, uint32_t pwmChV, uint32_t pwmChW, float busVoltage) {

	driver->driverEn = driverEn;

	driver->pwmTim = pwmTim;
	driver->pwmChU = pwmChU;
	driver->pwmChV = pwmChV;
	driver->pwmChW = pwmChW;

	driver->dutyU = 0;
	driver->dutyV = 0;
	driver->dutyW = 0;

	driver->busVoltage = busVoltage;

	// Ensure motor is off
	DRV8301_SetPhaseDutyCycles(driver, 0.5f, 0.5f, 0.5f);
}

void DRV8301_SetDriverEnable(DRV8301_t *driver, bool enable) {
	GPIOSetState(&driver->driverEn, enable ? GPIO_HIGH : GPIO_LOW);
}

void DRV8301_SetPhaseVoltages(DRV8301_t *driver, float u, float v, float w) {
	// Map phase voltages to duty cycles
	float dutyU = 0.5f + (u / driver->busVoltage);
	float dutyV = 0.5f + (v / driver->busVoltage);
	float dutyW = 0.5f + (w / driver->busVoltage);

//	float dutyU = (u / driver->busVoltage);
//	float dutyV = (v / driver->busVoltage);
//	float dutyW = (w / driver->busVoltage);

	DRV8301_SetPhaseDutyCycles(driver, dutyU, dutyV, dutyW);
}

void DRV8301_SetPhaseDutyCycles(DRV8301_t *driver, float u, float v, float w) {
	driver->dutyU = ConstrainFloat(u, 0, 1);
	driver->dutyV = ConstrainFloat(v, 0, 1);
	driver->dutyW = ConstrainFloat(w, 0, 1);

	SetPWMDutyCycle(driver->pwmTim, driver->pwmChU, driver->dutyU);
	SetPWMDutyCycle(driver->pwmTim, driver->pwmChV, driver->dutyV);
	SetPWMDutyCycle(driver->pwmTim, driver->pwmChW, driver->dutyW);
}

float DRV8301_GetBusVoltage(DRV8301_t *driver) {
	return driver->busVoltage;
}

static inline void SetPWMDutyCycle(TIM_HandleTypeDef *htim, uint32_t channel,
		float dutyCycle) {
	uint16_t compare = (uint16_t)(DRV8301_MAX_PWM * dutyCycle);
	__HAL_TIM_SET_COMPARE(htim, channel, compare);
}
