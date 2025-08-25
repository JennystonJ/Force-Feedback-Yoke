/*
 * MT6835.c
 *
 *  Created on: Jul 5, 2025
 *      Author: Jennyston
 */

#include "devices/mt6835.h"
#include "devices/mt6835_registers.h"

#include <stddef.h>

#define HAL_TIMEOUT 10

typedef enum {
	MT6835Command_READ = 0b0011,
	MT6835Command_WRITE = 0b0110,
	MT6835Command_PRGM_EEPROM = 0b1100,
	MT6835Command_SET_ZERO = 0b0101,
	MT6835Command_BURST_READ = 0b1010
} MT6835Command_e;

// Private function prototypes
static void AssertCS(MT6835_t *device);
static void UnassertCS(MT6835_t *device);

static void WriteRegister(MT6835_t *device, MT6835Reg_e reg, uint8_t data);
static uint8_t ReadRegister(MT6835_t *device, MT6835Reg_e reg);
static void StartBurstReadAngle(MT6835_t *device);
static void StopBurstReadAngle(MT6835_t *device);

static void CalibrateABCount(MT6835_t *device);

static void SendRegisterCommand(MT6835_t *device, MT6835Command_e cmd,
		MT6835Reg_e reg);

static void HandleDeviceWarning(MT6835_t *device);
static void HandleSPIError(MT6835_t *device);

void MT6835_Init(MT6835_t *device, SPI_HandleTypeDef *hspi, GPIO_t nCS) {
	device->hspi = hspi;
	device->nCS = nCS;

	device->htim = NULL;

	device->encoderWarning = false;
	device->spiError = false;
	device->encoderWarningCallback = NULL;
	device->errorCallback = NULL;

	device->angle = 0;

	// Ensure chip select is not asserted
	UnassertCS(device);

	// For Debug
	uint8_t upperByte = ReadRegister(device, MT6835Reg_ABZ_RES_13_6);
	uint8_t lowerByte = ReadRegister(device, MT6835Reg_ABZ_RES_5_0_OFF_SWAP);

//	// Set number of ABZ pulses to 16384, ABZ ON, Swap OFF
	WriteRegister(device, MT6835Reg_ABZ_RES_13_6, 0xFF);
	WriteRegister(device, MT6835Reg_ABZ_RES_5_0_OFF_SWAP, 0xFD);

}

void MT6835_SetABTim(MT6835_t *device, TIM_HandleTypeDef *htim) {
	device->htim = htim;
	CalibrateABCount(device);
}

void MT6835_SetABCount(MT6835_t *device, uint32_t count) {
	if(device->htim != NULL) {
		__HAL_TIM_SET_COUNTER(device->htim, count);
	}
}

uint32_t MT6835_GetABCount(MT6835_t *device) {
	if(device->htim != NULL) {
		return __HAL_TIM_GET_COUNTER(device->htim);
	}

	return 0;
}

uint32_t MT6835_GetAngle(MT6835_t *device) {
	return device->angle;
}

uint32_t MT6835_ReadAngle(MT6835_t *device) {
	MT6835_Update(device);
	return MT6835_GetAngle(device);
}

void MT6835_Update(MT6835_t *device) {

	StartBurstReadAngle(device);

	// Read angle registers, status, and CRC
	uint8_t data[4];
	HAL_StatusTypeDef status = HAL_SPI_Receive(device->hspi, data,
			sizeof(data), HAL_TIMEOUT);

	if(status != HAL_OK) {
		HandleSPIError(device);
	}

	// Process read data
	device->angle = ((uint32_t)data[0] << 13) |
					((uint32_t)data[1] << 5) |
					((uint32_t)data[2] >> 3);
	device->status = data[2] & 0x07;

	// Check if warning bit(s) are set
	if(device->status != 0x00) {
		HandleDeviceWarning(device);
	}

	// TODO: process CRC to detect communication errors
	uint8_t crc = data[3];

	StopBurstReadAngle(device);
}

void MT6835_RegisterEncoderWarningCallback(MT6835_t *device,
		void (*encoderWarningCallback)(MT6835_t *device)) {
	device->encoderWarningCallback = encoderWarningCallback;
}

void MT6835_RegisterErrorCallback(MT6835_t *device,
		void (*errorCallback)(MT6835_t *device)) {
	device->errorCallback = errorCallback;
}

static void AssertCS(MT6835_t *device) {
	GPIOSetState(&device->nCS, GPIO_LOW);
}

static void UnassertCS(MT6835_t *device) {
	GPIOSetState(&device->nCS, GPIO_HIGH);
}

static void WriteRegister(MT6835_t *device, MT6835Reg_e reg, uint8_t data) {
	AssertCS(device);

	SendRegisterCommand(device, MT6835Command_WRITE, reg);

	// Write byte
	HAL_StatusTypeDef status = HAL_SPI_Transmit(device->hspi, &data, 1,
			HAL_TIMEOUT);
	if(status != HAL_OK) {
		HandleSPIError(device);
	}

	UnassertCS(device);
}

static uint8_t ReadRegister(MT6835_t *device, MT6835Reg_e reg) {
	AssertCS(device);

	SendRegisterCommand(device, MT6835Command_READ, reg);

	// Read byte
	uint8_t data;
	HAL_StatusTypeDef status = HAL_SPI_Receive(device->hspi, &data, 1,
			HAL_TIMEOUT);
	if(status != HAL_OK) {
		HandleSPIError(device);
	}

	UnassertCS(device);

	return data;
}

static void StartBurstReadAngle(MT6835_t *device) {
	AssertCS(device);

	// Initiate burst transfer
	SendRegisterCommand(device, MT6835Command_BURST_READ,
			MT6835Reg_ANGLE_20_13);

	// Leave CS asserted
}

static void StopBurstReadAngle(MT6835_t *device) {
	UnassertCS(device);
}

static void CalibrateABCount(MT6835_t *device) {
	uint32_t angle = MT6835_ReadAngle(device);
	MT6835_SetABCount(device, angle >> 5);
}

static void SendRegisterCommand(MT6835_t *device, MT6835Command_e cmd,
		MT6835Reg_e reg) {

	uint16_t cmdRegAddr = ((uint16_t)cmd << 12) |
			((uint16_t)reg & 0x0FFF);

	uint8_t txBytes[2];
	txBytes[0] = (uint8_t)(cmdRegAddr >> 8);
	txBytes[1] = (uint8_t)(cmdRegAddr & 0xFF);

	HAL_StatusTypeDef status = HAL_SPI_Transmit(device->hspi, txBytes,
			sizeof(txBytes), HAL_TIMEOUT);
	if(status != HAL_OK) {
		HandleSPIError(device);
	}
}

// Warning handler for encoder status warnings
static void HandleDeviceWarning(MT6835_t *device) {
	device->encoderWarning = true;
	if(device->encoderWarningCallback != NULL) {
		device->encoderWarningCallback(device);
	}
}

// Error handler for SPI communication issues
static void HandleSPIError(MT6835_t *device) {
	device->spiError = true;
	if(device->errorCallback != NULL) {
		device->errorCallback(device);
	}
}
