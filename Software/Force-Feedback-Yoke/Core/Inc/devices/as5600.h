/*
 * AS5600.h
 *
 *  Created on: Mar 13, 2024
 *      Author: Jennyston
 */

#ifndef INC_AS5600_H_
#define INC_AS5600_H_

#define AS5600_I2C_ADDR (0x36<<1)
#define AS5600_MAX_COUNT 4095
#define AS5600_MIN_COUNT 0
#define AS5600_MID_COUNT ((AS5600_MAX_COUNT-AS5600_MIN_COUNT)/2)

#include <stm32f4xx_hal.h>
#include <stdint.h>

typedef struct AS5600 AS5600_t;

struct AS5600 {
	I2C_HandleTypeDef *hi2c;
	void (*errorCallback)(AS5600_t *device);
};


void AS5600Init(AS5600_t *device, I2C_HandleTypeDef *hi2c);
uint8_t AS5600GetStatus(AS5600_t *device);
uint16_t AS5600GetAngle(AS5600_t *device);
void AS5600RegisterErrorCallback(AS5600_t *device,
		void (*errorCallback)(AS5600_t *device));

#endif /* INC_AS5600_H_ */
