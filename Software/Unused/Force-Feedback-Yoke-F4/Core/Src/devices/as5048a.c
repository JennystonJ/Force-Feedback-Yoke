/*
 * as5048a.c
 *
 *  Created on: Apr 21, 2025
 *      Author: Jennyston
 */

#include "devices/as5048a.h"
#include "devices/as5048a_registers.h"

#include "utilities/utilities.h"
#include "delay.h"

#define HAL_TIMEOUT 10

#define COMMAND_WRITE 0
#define COMMAND_READ 1

static void AssertCS(AS5048A_t *device);
static void UnassertCS(AS5048A_t *device);

static void WriteRegister(AS5048A_t *device, AS5048AReg reg, uint16_t value);
static uint16_t ReadRegister(AS5048A_t *device, AS5048AReg reg);
static uint16_t SendCommand(AS5048A_t *device, AS5048AReg reg, uint16_t rw);
static void SendCommandIT(AS5048A_t *device, AS5048AReg reg, uint16_t rw);
static uint16_t ProcessITData(AS5048A_t *device);

static void HandleSPIError(AS5048A_t *device);

static bool VerifyParity(uint16_t value);

void AS5048AInit(AS5048A_t *device, SPI_HandleTypeDef *hspi, GPIO_t nCS) {
	device->hspi = hspi;
	device->nCS = nCS;

	device->spiError = false;
	device->errorCallback = NULL;

	device->itState = AS5048A_IT_IDLE;
	device->magnitude = 0;
	device->angle = 0;

	// Ensure chip select is not asserted
	UnassertCS(device);

	uint16_t errorFlags = ReadRegister(device, AS5048A_CLR_ERR_FLAG);
}

void AS5048AStartIT(AS5048A_t *device) {
	UnassertCS(device);
	SendCommandIT(device, AS5048A_MAGNITUDE, COMMAND_READ);
	device->itState = AS5048A_IT_REQUESTING_MAG;
}

AS5048AITState_e AS5048AGetITState(AS5048A_t *device) {
	return device->itState;
}

void AS5048AUpdate(AS5048A_t *device) {
	switch(device->itState) {
	case AS5048A_IT_IDLE:
		// Do nothing
		break;
	case AS5048A_IT_REQUESTING_MAG:
		UnassertCS(device);
		SendCommandIT(device, AS5048A_ANGLE, COMMAND_READ);
		device->itState = AS5048A_IT_REQUESTING_ANGLE;
		break;
	case AS5048A_IT_REQUESTING_ANGLE:
		UnassertCS(device);

		device->magnitude = ProcessITData(device);
		// Check if device is in abnormal operating conditions
		if(device->magnitude == 0) {
			HandleSPIError(device);
		}

		SendCommandIT(device, AS5048A_NOP, COMMAND_READ);
		device->itState = AS5048A_IT_REQUESTING_NOP;
		break;
	case AS5048A_IT_REQUESTING_NOP:
		UnassertCS(device);

		device->angle = ProcessITData(device);

		device->itState = AS5048A_IT_IDLE;
		break;
	default:
		// Invalid state
	}
}

uint16_t AS5048AGetReadITAngle(AS5048A_t *device) {
	return device->angle;
}

uint16_t AS5048AGetAngle(AS5048A_t *device) {
	uint16_t magnitude = ReadRegister(device, AS5048A_MAGNITUDE);

	// Check if device is in abnormal operating conditions
	if(magnitude == 0) {
		HandleSPIError(device);
	}

	return ReadRegister(device, AS5048A_ANGLE);
}

void AS5048ARegisterErrorCallback(AS5048A_t *device,
	void (*errorCallback)(AS5048A_t *device)) {
	device->errorCallback = errorCallback;
}

static void AssertCS(AS5048A_t *device) {
	GPIOSetState(&device->nCS, GPIO_LOW);
}

static void UnassertCS(AS5048A_t *device) {
	GPIOSetState(&device->nCS, GPIO_HIGH);
}

static void SendCommandIT(AS5048A_t *device, AS5048AReg reg, uint16_t rw) {

	// Prepare register address
	uint16_t data = (uint16_t)reg | rw << 14;
	data = ((uint16_t)CalcEvenParity((uint8_t *)&data, sizeof(data)) << 15) |
			data;
	// Convert to big endian (swap byte order)
	uint16_t dataBigEndian = ((data << 8) | (data >> 8));

	// Prepare buffers
	device->spiTxBuffer = dataBigEndian;
	device->spiRxBuffer = 0;

	// Start interrupt transfer
	AssertCS(device);
	HAL_StatusTypeDef status = HAL_SPI_TransmitReceive_IT(device->hspi,
			(uint8_t *)&device->spiTxBuffer,
			(uint8_t *)&device->spiRxBuffer, sizeof(device->spiRxBuffer));

	if(status != HAL_OK) {
		HandleSPIError(device);
	}
}

static uint16_t SendCommand(AS5048A_t *device, AS5048AReg reg, uint16_t rw){
	AssertCS(device);


	// Write register address
	uint16_t data = (uint16_t)reg | rw << 14;
	data = ((uint16_t)CalcEvenParity((uint8_t *)&data, sizeof(data)) << 15) |
			data;
	// Convert to big endian (swap byte order)
	uint16_t dataBigEndian = ((data << 8) | (data >> 8));
	uint16_t result = 0;
	HAL_StatusTypeDef status = HAL_SPI_TransmitReceive(device->hspi,
			(uint8_t *)&dataBigEndian,
			(uint8_t *)&result, sizeof(dataBigEndian), HAL_TIMEOUT);

	UnassertCS(device);

	if(status != HAL_OK) {
		HandleSPIError(device);
	}

	return result;
}

static void WriteRegister(AS5048A_t *device, AS5048AReg reg, uint16_t value) {

	// Send register address
	SendCommand(device, reg, COMMAND_WRITE);

	// Write register data
	AssertCS(device);
	HAL_StatusTypeDef status;
	uint16_t data = ((uint16_t)CalcEvenParity((uint8_t *)&value,
			sizeof(value)) << 15) |
			value;
	status = HAL_SPI_Transmit(device->hspi, (uint8_t *)&data, sizeof(data),
			HAL_TIMEOUT);
	if(status != HAL_OK) {
		HandleSPIError(device);
	}
	UnassertCS(device);

	// Read written register data for verification
	uint16_t readValue = SendCommand(device, AS5048A_NOP, COMMAND_READ);

	// Check for parity and value not matching errors
	if(!VerifyParity(readValue) || value != (readValue & 0x7FFF)) {
		HandleSPIError(device);
	}
	else {
		// Register written successfully
	}
}

static uint16_t ReadRegister(AS5048A_t *device, AS5048AReg reg) {

	// Send register address to read from
	SendCommand(device, reg, COMMAND_READ);

	// Read data
	uint16_t readValue = SendCommand(device, AS5048A_NOP, COMMAND_READ);

	// Swap byte order (convert to little endian)
	readValue = ((readValue << 8) | (readValue >> 8));

	// Check for parity errors
	if(!VerifyParity(readValue)) {
		HandleSPIError(device);
	}

	// Remove parity bit and return
	return readValue & 0x7FFF;
}

static uint16_t ProcessITData(AS5048A_t *device) {
	uint16_t readValue = device->spiRxBuffer;

	// Swap byte order (convert to little endian)
	readValue = ((readValue << 8) | (readValue >> 8));

	// Check for parity errors
	if(!VerifyParity(readValue)) {
		HandleSPIError(device);
	}

	// Remove parity bit and return
	return readValue & 0x7FFF;
}

// Error handler for SPI communication issues.
static void HandleSPIError(AS5048A_t *device) {
	device->spiError = true;
	if(device->errorCallback != NULL) {
		device->errorCallback(device);
	}
}

// Returns true if check passes, otherwise false
static bool VerifyParity(uint16_t value) {
	return CalcEvenParity((uint8_t *)&value, sizeof(value)) == 0 ? true : false;
}
