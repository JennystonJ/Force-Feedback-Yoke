/*
 * MT6835.h
 *
 *  Created on: Jul 5, 2025
 *      Author: Jennyston
 */

#ifndef INC_DEVICES_MT6835_H_
#define INC_DEVICES_MT6835_H_

#include <stm32h7xx_hal.h>
#include <stdbool.h>
#include <stdint.h>
#include "peripherals/gpio.h"

#define MT6835_COUNT_PER_REV 2097152
#define MT6835_AB_COUNT_PER_REV 65536

//typedef enum {
//	MT6835_MODE_NULL,
//	MT6835_MODE_SPI,
//	MT6835_MODE_AB,
//	MT6835_MODE_AB_SPI
//} MT6835_Mode_e;

typedef struct MT6835 MT6835_t;

struct MT6835 {
	SPI_HandleTypeDef *hspi;
	GPIO_t nCS;

	TIM_HandleTypeDef *htim;

	uint32_t spiTxBuffer;
	uint32_t spiRxBuffer;
	uint32_t angle;
	uint8_t status;

	bool encoderWarning;
	bool spiError;
	void (*encoderWarningCallback)(MT6835_t *device);
	void (*errorCallback)(MT6835_t *device);
};

void MT6835_Init(MT6835_t *device, SPI_HandleTypeDef *hspi, GPIO_t nCS);
//void MT6835_SetSPI(MT6835_t *device, SPI_HandleTypeDef *hspi, GPIO_t nCS);

void MT6835_SetABTim(MT6835_t *device, TIM_HandleTypeDef *htim);
void MT6835_SetABCount(MT6835_t *device, uint32_t count);
uint32_t MT6835_GetABCount(MT6835_t *device);

uint32_t MT6835_GetAngle(MT6835_t *device);
uint32_t MT6835_ReadAngle(MT6835_t *device);

void MT6835_Update(MT6835_t *device);

void MT6835_RegisterEncoderWarningCallback(MT6835_t *device,
		void (*encoderWarningCallback)(MT6835_t *device));
void MT6835_RegisterErrorCallback(MT6835_t *device,
		void (*errorCallback)(MT6835_t *device));

#endif /* INC_DEVICES_MT6835_H_ */
