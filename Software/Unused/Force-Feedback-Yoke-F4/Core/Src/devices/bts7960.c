/*
 * bts7960.c
 *
 *  Created on: Jul 12, 2024
 *      Author: Jennyston
 */

#include "devices/bts7960.h"
#include "utilities/utilities.h"

// Forward function prototypes
static void BTS7960SetPowerBrake(BTS7960_t *driver, int power);
static void BTS7960SetPowerCoast(BTS7960_t *driver, int power);

void BTS7960InitEn(BTS7960_t *driver, TIM_HandleTypeDef *htim,
		uint32_t forwardPwmCh, uint32_t reversePwmCh, GPIO_t enable) {
	driver->enableInit = true;
	driver->enable = enable;
	driver->htim = htim;
	driver->forwardPwmCh = forwardPwmCh;
	driver->reversePwmCh = reversePwmCh;
	driver->controlMode = BTS7960_POWER_BRAKE;

	// Ensure motor is powered off for safety
	BTS7960SetDriverEStop(driver, true);
}

void BTS7960InitPowerBrake(BTS7960_t *driver, TIM_HandleTypeDef *htim,
		uint32_t forwardPwmCh, uint32_t reversePwmCh) {
	driver->enableInit = false;
	driver->htim = htim;
	driver->forwardPwmCh = forwardPwmCh;
	driver->reversePwmCh = reversePwmCh;
	driver->controlMode = BTS7960_POWER_BRAKE;

	// Ensure motor is powered off for safety
	BTS7960SetPower(driver, 0);
}

void BTS7960InitPowerCoast(BTS7960_t *driver, TIM_HandleTypeDef *htim,
		uint32_t pwmCh, GPIO_t forwardEn, GPIO_t reverseEn) {
	driver->enableInit = false;
	driver->htim = htim;
	driver->forwardPwmCh = pwmCh;
	driver->reversePwmCh = pwmCh;
	driver->forwardEn = forwardEn;
	driver->reverseEn = reverseEn;
	driver->controlMode = BTS7960_POWER_COAST;

	// Ensure motor is powered off for safety
	BTS7960SetPower(driver, 0);
}

void BTS7960SetPower(BTS7960_t *driver, int power) {
	// Determine control mode and call appropriate set power function
	if(driver->controlMode == BTS7960_POWER_BRAKE) {
		BTS7960SetPowerBrake(driver, power);
	}
	else if(driver->controlMode == BTS7960_POWER_COAST){
		BTS7960SetPowerCoast(driver, power);
	}
	else {
		// Invalid control mode
	}
}

static void BTS7960SetPowerBrake(BTS7960_t *driver, int power) {

	if(driver->driverEStop) {
		power = 0;
	}

	driver->power = Constrain(power, -BTS7960_MAX_PWM_POWER,
			BTS7960_MAX_PWM_POWER);

	// Determine direction signals
	if(driver->power > 0) {
		if(driver->enableInit) {
			GPIOSetState(&driver->enable, GPIO_HIGH);
		}
		__HAL_TIM_SET_COMPARE(driver->htim, driver->forwardPwmCh,
				(int)(driver->power * BTS7960_FORWARD_DIR_POWER_SCALE));
		__HAL_TIM_SET_COMPARE(driver->htim, driver->reversePwmCh, 0);

//		__HAL_TIM_SET_COMPARE(driver->htim, driver->forwardPwmCh,
//				BTS7960_MAX_PWM_POWER);
//		__HAL_TIM_SET_COMPARE(driver->htim, driver->reversePwmCh,
//				BTS7960_MAX_PWM_POWER -
//				(int)(driver->power * BTS7960_FORWARD_DIR_POWER_SCALE));
	}
	else if(driver->power < 0) {
		if(driver->enableInit) {
			GPIOSetState(&driver->enable, GPIO_HIGH);
		}

		__HAL_TIM_SET_COMPARE(driver->htim, driver->forwardPwmCh, 0);
		__HAL_TIM_SET_COMPARE(driver->htim, driver->reversePwmCh,
				-(int)(driver->power * BTS7960_REVERSE_DIR_POWER_SCALE));

//		__HAL_TIM_SET_COMPARE(driver->htim, driver->forwardPwmCh,
//				BTS7960_MAX_PWM_POWER -
//				(-(int)(driver->power * BTS7960_REVERSE_DIR_POWER_SCALE)));
//		__HAL_TIM_SET_COMPARE(driver->htim, driver->reversePwmCh,
//				BTS7960_MAX_PWM_POWER);

	}
	else {
		if(driver->enableInit) {
			GPIOSetState(&driver->enable, GPIO_LOW);
		}

//		__HAL_TIM_SET_COMPARE(driver->htim, driver->forwardPwmCh,
//				BTS7690_MAX_PWM_POWER);
//		__HAL_TIM_SET_COMPARE(driver->htim, driver->reversePwmCh,
//						BTS7690_MAX_PWM_POWER);
		__HAL_TIM_SET_COMPARE(driver->htim, driver->forwardPwmCh, 0);
		__HAL_TIM_SET_COMPARE(driver->htim, driver->reversePwmCh, 0);
	}
}

static void BTS7960SetPowerCoast(BTS7960_t *driver, int power) {

	if(driver->driverEStop) {
		power = 0;
	}

	driver->power = Constrain(power, -BTS7960_MAX_PWM_POWER,
			BTS7960_MAX_PWM_POWER);

	//Determine direction signals
	if(driver->power > 0) {
		GPIOSetState(&driver->forwardEn, GPIO_HIGH);
		GPIOSetState(&driver->reverseEn, GPIO_LOW);
	}
	else if(driver->power < 0) {
		GPIOSetState(&driver->forwardEn, GPIO_LOW);
		GPIOSetState(&driver->reverseEn, GPIO_HIGH);
	}
	else {
		GPIOSetState(&driver->forwardEn, GPIO_LOW);
		GPIOSetState(&driver->reverseEn, GPIO_LOW);
	}

	int outputPower = Abs(power);

	// Set motor power
	__HAL_TIM_SET_COMPARE(driver->htim, driver->forwardPwmCh, outputPower);
}

int BTS7960GetPower(BTS7960_t *driver) {
	return driver->power;
}

void BTS7960SetDriverEStop(BTS7960_t *driver, bool estop) {
	if(estop) {

		// Shut motor off
		BTS7960SetPower(driver, 0);
	}
	driver->driverEStop = estop;
}

