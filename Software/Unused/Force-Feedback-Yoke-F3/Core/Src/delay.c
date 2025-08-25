/*
 * delay.c
 *
 *  Created on: Jul 25, 2024
 *      Author: Jennyston
 */

#include "delay.h"
#include <stm32f3xx_hal.h>

void delayMs(int milliseconds) {
	HAL_Delay(ms);
}
