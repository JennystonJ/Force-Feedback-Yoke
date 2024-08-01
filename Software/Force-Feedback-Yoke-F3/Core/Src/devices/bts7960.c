/*
 * bts7960.c
 *
 *  Created on: Jul 12, 2024
 *      Author: Jennyston
 */

#include "devices/bts7960.h"
#include "utilities/utilities.h"

void BTS7960Init(BTS7960_t *driver, GPIO_t forwardEn, GPIO_t reverseEn,
		TIM_HandleTypeDef *htim, uint32_t forwardPwmCh, uint32_t reversePwmCh) {
	driver->forwardEn = forwardEn;
	driver->reverseEn = reverseEn;
	driver->htim = htim;
	driver->forwardPwmCh = forwardPwmCh;
	driver->reversePwmCh = reversePwmCh;

	// Ensure motor is powered off for safety
	BTS7960SetPower(driver, 0);
}

void BTS7960SetPower(BTS7960_t *driver, int power) {
	driver->power = Constrain(power, -BTS7690_MAX_PWM_POWER,
			BTS7690_MAX_PWM_POWER);

	// Determine direction signals
	if(driver->power > 0) {
		GPIOSetState(&driver->forwardEn, GPIO_HIGH);
		GPIOSetState(&driver->reverseEn, GPIO_LOW);

		__HAL_TIM_SET_COMPARE(driver->htim, driver->forwardPwmCh,
				driver->power);
		__HAL_TIM_SET_COMPARE(driver->htim, driver->reversePwmCh, 0);
	}
	else if(driver->power < 0) {
		GPIOSetState(&driver->forwardEn, GPIO_LOW);
		GPIOSetState(&driver->reverseEn, GPIO_HIGH);
		__HAL_TIM_SET_COMPARE(driver->htim, driver->forwardPwmCh, 0);
		__HAL_TIM_SET_COMPARE(driver->htim, driver->reversePwmCh,
				-(driver->power));
	}
	else {
		GPIOSetState(&driver->forwardEn, GPIO_LOW);
		GPIOSetState(&driver->reverseEn, GPIO_LOW);

		__HAL_TIM_SET_COMPARE(driver->htim, driver->forwardPwmCh, 0);
		__HAL_TIM_SET_COMPARE(driver->htim, driver->reversePwmCh, 0);
	}
}

int BTS7960GetPower(BTS7960_t *driver) {
	return driver->power;
}
