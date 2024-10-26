/*
 * delay.c
 *
 *  Created on: Jul 25, 2024
 *      Author: Jennyston
 */

#include "delay.h"

static void(*delayMs_fptr)(uint32_t milliseconds);

void delayMsInit(void (*delayMs_func)(uint32_t milliseconds)) {
	delayMs_fptr = delayMs_func;
}

void delayMs(uint32_t milliseconds) {
	delayMs_fptr(milliseconds);
}
