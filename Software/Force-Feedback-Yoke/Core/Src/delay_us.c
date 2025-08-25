/*
 * delay_us.c
 *
 *  Created on: Aug 3, 2025
 *      Author: Jennyston
 */

#include "delay_us.h"

static TIM_HandleTypeDef *htim;

void DelayUs_Init(TIM_HandleTypeDef *htimUs) {
	htim = htimUs;
}

void DelayUs_Delay(uint16_t microseconds) {
	// Reset counter
	__HAL_TIM_SET_COUNTER(htim, 0);
	// Wait until microseconds is reached
	while(__HAL_TIM_GET_COUNTER(htim) < microseconds);
}
