/*
 * internal_adc.c
 *
 *  Created on: Nov 22, 2024
 *      Author: Jennyston
 */

#include <peripherals/internal_injected_adc.h>
#include "string.h"

static const uint32_t rankMapping[INTERNAL_INJECTED_ADC_NUM_RANKS] = {
		ADC_INJECTED_RANK_1,
		ADC_INJECTED_RANK_2,
		ADC_INJECTED_RANK_3,
		ADC_INJECTED_RANK_4
};

void InternalInjectedADC_Init(InternalInjectedADC_t *adc,
		ADC_HandleTypeDef *hadc, float vref) {
	adc->hadc = hadc;
	HAL_ADCEx_Calibration_Start(hadc, ADC_CALIB_OFFSET,
			ADC_SINGLE_ENDED);
}

void InternalInjectedADC_StartIT(InternalInjectedADC_t *adc) {
	HAL_ADCEx_InjectedStart_IT(adc->hadc);
}

uint32_t InternalInjectedADC_ReadValue(InternalInjectedADC_t *adc,
		uint8_t rank) {
	return adc->adcBuffer[rank];
//	return HAL_ADCEx_InjectedGetValue(adc->hadc, rankMapping[rank]);
}

float InternalInjectedADC_GetVref(InternalInjectedADC_t *adc) {
	return adc->vref;
}

void InternalInjectedADC_UpdateIT(InternalInjectedADC_t *adc) {
	for(int rank = 0; rank < INTERNAL_INJECTED_ADC_NUM_RANKS; rank++) {
		adc->adcBuffer[rank] =
				HAL_ADCEx_InjectedGetValue(adc->hadc, rankMapping[rank]);
	}
}
