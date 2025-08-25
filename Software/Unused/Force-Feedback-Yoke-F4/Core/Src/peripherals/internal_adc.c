/*
 * internal_adc.c
 *
 *  Created on: Nov 22, 2024
 *      Author: Jennyston
 */

#include "peripherals/internal_adc.h"
#include "string.h"

void InternalADCInit(InternalADC_t *adc, ADC_HandleTypeDef *hadc) {
	adc->hadc = hadc;
	adc->transferType = ADC_POLL_TRANSFER;

	memset(adc->buffer, 0, sizeof(adc->buffer));
	memset(adc->result, 0, sizeof(adc->result));

	MovingAvgInit(&adc->avgFilter, (int *)adc->buffer,
			sizeof(adc->buffer)/sizeof(uint32_t));
}

void InternalADCStartIT(InternalADC_t *adc) {
	HAL_ADC_Start_IT(adc->hadc);
	adc->transferType = ADC_INTERRUPT_TRANSFER;
}

void InternalADCUpdateIT(InternalADC_t *adc) {
	MovingAvgAdd(&adc->avgFilter, (int)HAL_ADC_GetValue(adc->hadc));
	// TODO: Implement other channels
	adc->result[0] = MovingAvgCalcF(&adc->avgFilter);
}

void InternalADCStartDMA(InternalADC_t *adc) {
	HAL_ADC_Start_DMA(adc->hadc, (uint32_t *)adc->buffer,
			ADC_BUFFER_SIZE);
	adc->transferType = ADC_DMA_TRANSFER;
}

float InternalADCReadChannel(InternalADC_t *adc, unsigned int channel) {
	if(channel >= ADC_NUM_CHANNELS) {
		Error_Handler();
	}

	switch(adc->transferType) {
	case ADC_POLL_TRANSFER:
		return 0;
		break;
	case ADC_INTERRUPT_TRANSFER:
		return adc->result[channel];
		break;
	case ADC_DMA_TRANSFER:
		// Calculate average ADC value
		int sum = 0;
		for(int i = channel; i < ADC_BUFFER_SIZE; i += ADC_NUM_CHANNELS) {
			sum += adc->buffer[i];
		}
		return (float)sum / ADC_NUM_AVG_SAMPLES;
		break;
	default:
		return 0;
	}

	return 0;
}
