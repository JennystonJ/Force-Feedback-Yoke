/*
 * dwt.c
 *
 *  Created on: Jul 26, 2026
 *      Author: Jennyston
 */

#include "peripherals/dwt.h"
#include "main.h"
#include "hardware_config.h"

void DWT_Init(void) {
    // Enable trace and debug block
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

    // Reset cycle counter
    DWT->CYCCNT = 0;

    // Enable cycle counter
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

uint32_t DWT_GetCount(void) {
	return DWT->CYCCNT;
}

float DWT_ConvertCyclesToUs(uint32_t cycles) {
	return (float)cycles / CLOCKSPEED_MHZ;
}
