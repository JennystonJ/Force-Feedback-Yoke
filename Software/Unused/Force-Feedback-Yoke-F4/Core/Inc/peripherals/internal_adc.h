/*
 * internal_adc.h
 *
 *  Created on: Nov 22, 2024
 *      Author: Jennyston
 */

#ifndef INC_PERIPHERALS_INTERNAL_ADC_H_
#define INC_PERIPHERALS_INTERNAL_ADC_H_

#include <stm32f4xx.h>
#include <stdint.h>
#include "utilities/filters.h"

#define ADC_NUM_CHANNELS 1
#define ADC_NUM_AVG_SAMPLES 32
#define ADC_BUFFER_SIZE (ADC_NUM_AVG_SAMPLES*ADC_NUM_CHANNELS)

typedef enum {
	ADC_POLL_TRANSFER,
	ADC_INTERRUPT_TRANSFER,
	ADC_DMA_TRANSFER
} ADCTransferType_e;

typedef struct InternalADC {
	ADC_HandleTypeDef *hadc;
	ADCTransferType_e transferType;
	uint16_t buffer[ADC_BUFFER_SIZE];
	float result[ADC_NUM_CHANNELS];
	MovingAvg_t avgFilter;
} InternalADC_t;

void InternalADCInit(InternalADC_t *adc, ADC_HandleTypeDef *hadc);
void InternalADCStartIT(InternalADC_t *adc);
void InternalADCUpdateIT(InternalADC_t *adc);
void InternalADCStartDMA(InternalADC_t *adc);
float InternalADCReadChannel(InternalADC_t *adc, unsigned int channel);

#endif /* INC_PERIPHERALS_INTERNAL_ADC_H_ */
