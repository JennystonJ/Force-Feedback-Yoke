/*
 * as5048a.h
 *
 *  Created on: Apr 21, 2025
 *      Author: Jennyston
 */

#ifndef INC_DEVICES_AS5048A_H_
#define INC_DEVICES_AS5048A_H_

#define AS5048A_MAX_COUNT 16383
#define AS5048A_MIN_COUNT 0
#define AS5048A_MID_COUNT ((AS5048A_MAX_COUNT-AS5048A_MIN_COUNT)/2)

#include <stm32f4xx_hal.h>
#include <stdint.h>
#include <stdbool.h>

#include "peripherals/gpio.h"

typedef enum {
	AS5048A_IT_IDLE,
	AS5048A_IT_REQUESTING_MAG,
	AS5048A_IT_REQUESTING_ANGLE,
	AS5048A_IT_REQUESTING_NOP
} AS5048AITState_e;

typedef struct AS5048A AS5048A_t;

struct AS5048A {
	SPI_HandleTypeDef *hspi;
	GPIO_t nCS;

	AS5048AITState_e itState;
	uint16_t spiTxBuffer;
	uint16_t spiRxBuffer;
	uint16_t magnitude;
	uint16_t angle;


	bool spiError;
	void (*errorCallback)(AS5048A_t *device);
};

void AS5048AInit(AS5048A_t *device, SPI_HandleTypeDef *hspi, GPIO_t nCS);
uint16_t AS5048AGetAngle(AS5048A_t *device);
void AS5048AStartIT(AS5048A_t * device);
AS5048AITState_e AS5048AGetITState(AS5048A_t *device);
void AS5048AUpdate(AS5048A_t *device);
uint16_t AS5048AGetReadITAngle(AS5048A_t *device);
void AS5048ARegisterErrorCallback(AS5048A_t *device,
		void (*errorCallback)(AS5048A_t *device));

#endif /* INC_DEVICES_AS5048A_H_ */
