/*
 * internal_injected_adc.h
 *
 *  Created on: Nov 22, 2024
 *      Author: Jennyston
 */

#ifndef INC_PERIPHERALS_INTERNAL_INJECTED_ADC_H_
#define INC_PERIPHERALS_INTERNAL_INJECTED_ADC_H_

#include <stm32h7xx.h>
#include <stdint.h>

#define INTERNAL_INJECTED_ADC_NUM_RANKS 4

typedef struct InternalInjectedADC {
	ADC_HandleTypeDef *hadc;
	uint32_t adcBuffer[INTERNAL_INJECTED_ADC_NUM_RANKS];
	float vref;
} InternalInjectedADC_t;

void InternalInjectedADC_Init(InternalInjectedADC_t *adc,
		ADC_HandleTypeDef *hadc, float vref);
void InternalInjectedADC_StartIT(InternalInjectedADC_t *adc);
uint32_t InternalInjectedADC_ReadValue(InternalInjectedADC_t *adc,
		uint8_t rank);
float InternalInjectedADC_GetVref(InternalInjectedADC_t *adc);
void InternalInjectedADC_UpdateIT(InternalInjectedADC_t *adc);

#endif /* INC_PERIPHERALS_INTERNAL_INJECTED_ADC_H_ */
