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

typedef struct MT6835Buffer {
	uint8_t tx[6];
	uint8_t rx[6];
} MT6835Buffer_t;

typedef struct MT6835 MT6835_t;

typedef struct MT6835EdgeMeasure {
	TIM_HandleTypeDef *htim;
	TIM_HandleTypeDef *htimEdge;
	uint32_t htimEdgeChA;
	uint32_t htimEdgeChB;
	GPIO_t gpioA;
	GPIO_t gpioB;

	DMA_HandleTypeDef *hdmaA;
	DMA_HandleTypeDef *hdmaB;
	uint32_t *edgeBuffer;
	uint16_t tailIndexA;
	uint16_t tailIndexB;
	uint16_t bufferLength;

	int32_t edgeCount;
	uint32_t prevEdgeTime;
	uint32_t currentEdgeTime;

	uint8_t currentState;
	uint8_t previousState;

	bool valid;
} MT6835EdgeMeasure_t;

struct MT6835 {
	SPI_HandleTypeDef *hspi;
	GPIO_t nCS;

	TIM_HandleTypeDef *htim;

	MT6835EdgeMeasure_t edge;

	MT6835Buffer_t *buffer;
	CRC_HandleTypeDef *hcrc;


	uint32_t angle;
	uint8_t status;

	bool dataReady;

	bool encoderWarning;
	bool spiError;
	void (*encoderWarningCallback)(MT6835_t *device);
	void (*errorCallback)(MT6835_t *device);
};

void MT6835_Init(MT6835_t *device, SPI_HandleTypeDef *hspi, GPIO_t nCS,
		MT6835Buffer_t *buffer);
void MT6835_SetCRC(MT6835_t *device, CRC_HandleTypeDef *hcrc);

void MT6835_SetABTim(MT6835_t *device, TIM_HandleTypeDef *htim);
void MT6835_SetABCount(MT6835_t *device, uint32_t count);
uint32_t MT6835_GetABCount(MT6835_t *device);

void MT6835_SetABEdgeDMA(MT6835_t *device, DMA_HandleTypeDef *hdmaA,
		DMA_HandleTypeDef *hdmaB, uint32_t *edgeBuffer, uint16_t length);
void MT6835_SetABEdgeTim(MT6835_t *device, TIM_HandleTypeDef *htimEdge,
		uint32_t chA, uint32_t chB, GPIO_t gpioA, GPIO_t gpioB);
void MT6835_StartEdgeTim(MT6835_t *device);
void MT6835_UpdateEdgeTimeDMA(MT6835_t *device);

void MT6835_GetEdgeData(MT6835_t *device, uint32_t *edgeTime,
		int32_t *edgeCount);

uint16_t MT6835_GetABPulseCount(MT6835_t *device);

uint32_t MT6835_GetAngle(MT6835_t *device);
uint32_t MT6835_ReadAngle(MT6835_t *device);

bool MT6835_GetDataReady(MT6835_t *device);

void MT6835_Update(MT6835_t *device);
void MT6835_UpdateComplete(MT6835_t *device);

void MT6835_RegisterEncoderWarningCallback(MT6835_t *device,
		void (*encoderWarningCallback)(MT6835_t *device));
void MT6835_RegisterErrorCallback(MT6835_t *device,
		void (*errorCallback)(MT6835_t *device));

#endif /* INC_DEVICES_MT6835_H_ */
