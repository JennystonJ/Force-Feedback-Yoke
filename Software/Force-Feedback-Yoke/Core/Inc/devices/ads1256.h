/*
 * ads1256.h
 *
 *  Created on: Dec 17, 2024
 *      Author: Jennyston
 */

#ifndef INC_DEVICES_ADS1256_H_
#define INC_DEVICES_ADS1256_H_

#define ADS1256_VREF 2.5f

#define ADS1256_BUFFER_SIZE 3
#define ADS1256_TRANSFER_BUFFER_SIZE 4

#include "stm32h7xx.h"
#include <stdint.h>
#include <stdbool.h>
#include "peripherals/gpio.h"
#include "utilities/filters.h"

typedef enum {
	ADS1256_DMA_IDLE,
	ADS1256_DMA_COMMAND_SENT,
	ADS1256_DMA_DATA_RECEIVED
} ADS1256DMAState_e;

typedef struct ADS1256 ADS1256_t;

struct ADS1256 {

	SPI_HandleTypeDef *hspi;
	GPIO_t nCS;
	GPIO_t nDRdy;

	uint8_t spiTransferIndex;
	volatile bool transferInProgress;
	bool readDataContinuous;

	int32_t reading;
	int32_t readingBuffer[ADS1256_BUFFER_SIZE];
	int readingBufferTailIndex;
	int32_t medianFilterBuffer[ADS1256_BUFFER_SIZE];
	bool lockUpdate;
	ADS1256DMAState_e dmaState;
	uint8_t bufferTx[ADS1256_TRANSFER_BUFFER_SIZE];
	uint8_t bufferRx[ADS1256_TRANSFER_BUFFER_SIZE];
	void (*errorCallback)(ADS1256_t *adc);

	int retryCount;

	HighPass_t filter;

	// Debug
	long dmaCount;
	long errorCount;
};

void ADS1256_Init(ADS1256_t *adc, SPI_HandleTypeDef *hspi, GPIO_t nCS,
		GPIO_t nDRdy);
int32_t ADS1256_Read(ADS1256_t *adc);
void ADS1256_Update(ADS1256_t *adc);

void ADS1256StartIT(ADS1256_t *adc);
void ADS1256StartIT2(ADS1256_t *adc);
void ADS1256UpdateIT(ADS1256_t *adc);
void ADS1256UpdateIT2(ADS1256_t *adc);
void ADS1256CloseIT(ADS1256_t *adc);
void ADS1256CloseIT2(ADS1256_t *adc);

void ADS1256_StartReading(ADS1256_t *adc);

void ADS1256_StartDMA(ADS1256_t *adc);
void ADS1256UpdateDMA(ADS1256_t *adc);

void ADS1256_Calibrate(ADS1256_t *adc);

void ADS1256_RegisterErrorCallback(ADS1256_t *adc,
		void (*errorCallback)(ADS1256_t *adc));

float ADS1256_GetVref(ADS1256_t *adc);

#endif /* INC_DEVICES_ADS1256_H_ */
