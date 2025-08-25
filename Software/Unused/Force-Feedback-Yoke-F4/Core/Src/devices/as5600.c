/*
 * AS5600.c
 *
 *  Created on: Mar 13, 2024
 *      Author: Jennyston
 */

#include <devices/as5600_registers.h>
#include "devices/as5600.h"

#define HAL_TIMEOUT 10

static void WriteRegister(AS5600_t *device, AS5600Reg reg, uint8_t value);
static uint8_t ReadRegister(AS5600_t *device, AS5600Reg reg);
static void ReadRegisterBurst(AS5600_t *device, AS5600Reg reg, uint8_t *data,
		uint8_t length);
static uint16_t ReadRegister16(AS5600_t *device, AS5600Reg reg);
static void HandleI2CError(AS5600_t *device);

void AS5600Init(AS5600_t *device, I2C_HandleTypeDef *hi2c) {
	device->hi2c = hi2c;
	device->i2cError = false;
	device->errorCallback = NULL;
}

uint8_t AS5600GetStatus(AS5600_t *device) {
	return ReadRegister(device, AS5600_STATUS);
}

uint16_t AS5600GetAngle(AS5600_t *device) {
	return ReadRegister16(device, AS5600_RAW_ANGLE_1);
}


void AS5600RegisterErrorCallback(AS5600_t *device,
		void (*errorCallback)(AS5600_t *device)) {
	device->errorCallback = errorCallback;
}

static void WriteRegister(AS5600_t *device, AS5600Reg reg, uint8_t value) {

	HAL_StatusTypeDef status;
	uint8_t data[2] = {(uint8_t)reg, value};
	status = HAL_I2C_Master_Transmit(device->hi2c, AS5600_I2C_ADDR, data, 2,
			HAL_TIMEOUT);
	if(status != HAL_OK) {
		HandleI2CError(device);
	}
}

static uint8_t ReadRegister(AS5600_t *device, AS5600Reg reg) {
	uint8_t data;
	HAL_StatusTypeDef status;

	status = HAL_I2C_Master_Transmit(device->hi2c, AS5600_I2C_ADDR,
				&reg, 1, HAL_TIMEOUT);
	if(status != HAL_OK) {
		HandleI2CError(device);
		return 0xFF;
	}

	status = HAL_I2C_Master_Receive(device->hi2c, AS5600_I2C_ADDR, &data, 1,
			HAL_TIMEOUT);
	if(status != HAL_OK) {
		HandleI2CError(device);
		return 0xFF;
	}

	return data;
}

static void ReadRegisterBurst(AS5600_t *device, AS5600Reg reg, uint8_t *data,
		uint8_t length) {

	HAL_StatusTypeDef status;

	// Transmit the register address.
	status = HAL_I2C_Master_Transmit(device->hi2c, AS5600_I2C_ADDR,
			(uint8_t *)&reg, 1, HAL_TIMEOUT);
	if(status != HAL_OK) {
		HandleI2CError(device);
		return;
	}

	// Receive the requested data.
	status = HAL_I2C_Master_Receive(device->hi2c, AS5600_I2C_ADDR, data, length,
			HAL_TIMEOUT);
	if(status != HAL_OK) {
		HandleI2CError(device);
	}
}

static uint16_t ReadRegister16(AS5600_t *device, AS5600Reg reg) {
	uint16_t data;
	ReadRegisterBurst(device, reg, (uint8_t *)&data, 2);

	//swap byte order (to little endian).
	uint8_t temp = (uint8_t)(data >> 8);
	data = (data << 8) | temp;

	return data;
}

// Error handler for I2C communication issues.
static void HandleI2CError(AS5600_t *device) {
	device->i2cError = true;
	if(device->errorCallback != NULL) {
		device->errorCallback(device);
	}
}

