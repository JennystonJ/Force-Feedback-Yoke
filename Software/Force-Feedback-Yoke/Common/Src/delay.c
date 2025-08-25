/*
 * delay.c
 *
 *  Created on: Jul 25, 2024
 *      Author: Jennyston
 */

#include "delay.h"

static void(*delayMs_fptr)(uint32_t milliseconds);
static void(*delayUs_fptr)(uint16_t microseconds);

void delayMsInit(void (*delayMs_func)(uint32_t milliseconds)) {
	delayMs_fptr = delayMs_func;
}

void delayMs(uint32_t milliseconds) {
	delayMs_fptr(milliseconds);
}

void delayUsInit(void (*delayUs_func)(uint16_t microseconds)) {
	delayUs_fptr = delayUs_func;
}

void delayUs(uint16_t microseconds) {
	delayUs_fptr(microseconds);
}
