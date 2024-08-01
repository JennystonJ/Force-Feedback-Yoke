/*
 * delay.c
 *
 *  Created on: Jul 25, 2024
 *      Author: Jennyston
 */

#include "delay.h"
#include <stm32f4xx_hal.h>

void delayMs(int milliseconds) {
	HAL_Delay(milliseconds);
}
