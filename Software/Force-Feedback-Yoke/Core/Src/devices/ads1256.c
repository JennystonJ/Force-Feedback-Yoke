/*
 * ads1256.c
 *
 *  Created on: Dec 17, 2024
 *      Author: Jennyston
 */

#include "devices/ads1256.h"
#include "devices/ads1256_registers.h"
#include "devices/ads1256_commands.h"
#include <string.h>
#include "delay.h"

#define HAL_TIMEOUT 10

// Private forward prototypes
static void Wakeup(ADS1256_t *adc);
static int32_t ReadData(ADS1256_t *adc);
static void ReadDataContinuous(ADS1256_t *adc);
static void StopReadDataContinuous(ADS1256_t *adc);
static void SelfCalibration(ADS1256_t *adc);
static void ResetDevice(ADS1256_t *adc);

static uint8_t ReadRegister(ADS1256_t *adc, ADS1256Reg_e reg);
static void WriteRegister(ADS1256_t *adc, ADS1256Reg_e reg, uint8_t value);

static void HandleSPIError(ADS1256_t *adc);
static void ReadDataDMA(ADS1256_t *adc);

static void SendCommandIT(ADS1256_t *adc);
static void ReceiveIT(ADS1256_t *adc);

static void SendCommandDMA(ADS1256_t *adc);
static void ReceiveDMA(ADS1256_t *adc);
static void CloseDMA(ADS1256_t *adc);

static uint8_t _test = 0;

static bool inStart = false, inClose = false;

void ADS1256_Init(ADS1256_t *adc, SPI_HandleTypeDef *hspi, GPIO_t nCS,
		GPIO_t nDRdy) {
	adc->readingBufferTailIndex = 0;

	adc->lockUpdate = true;
	adc->hspi = hspi;
	adc->nCS = nCS;
	adc->nDRdy = nDRdy;

	adc->errorCallback = NULL;

	ResetDevice(adc);

	// Select AIN0 as positive input channel and AIN1 as negative input
	uint8_t test = ReadRegister(adc, ADS1256_MUX);
	WriteRegister(adc, ADS1256_MUX, 0x01);

	// Set data rate to 500 SPS
//	WriteRegister(adc, ADS1256_DRATE, 0b10010010);
	WriteRegister(adc, ADS1256_DRATE, 0b10100001);

	test = ReadRegister(adc, ADS1256_DRATE);

	// Enable analog input buffer
//	WriteRegister(adc, ADS1256_STATUS, 0b00000010);
	// Disable analog input buffer
	WriteRegister(adc, ADS1256_STATUS, 0b00000000);
	test = ReadRegister(adc, ADS1256_STATUS);

	// Clock out off, sensor detect off, PGA 1
	WriteRegister(adc, ADS1256_ADCON, 0b00000000);

	SelfCalibration(adc);

	delayMs(10);

//	prevSample = ReadData(adc);


	HighPassFilter_Init(&adc->filter, 0.01);

	adc->spiTransferIndex = 0;
	adc->transferInProgress = false;
	adc->retryCount = 0;
	adc->dmaState = ADS1256_DMA_IDLE;
	adc->lockUpdate = false;
	adc->readDataContinuous = false;

	adc->dmaCount = 0;
	adc->errorCount = 0;
}

int32_t ADS1256_Read(ADS1256_t *adc) {
	return adc->reading;
}


void ADS1256_StartDMA(ADS1256_t *adc) {

//	if(adc->dmaState == ADS1256_DMA_IDLE) {
		// Ensure SPI is ready before proceeding
	if(adc->readDataContinuous &&
			HAL_SPI_GetState(adc->hspi) == HAL_SPI_STATE_READY) {

//		// Un-assert chip select signal
//		GPIOSetState(&adc->nCS, GPIO_HIGH);

//		SendCommandIT(adc);
//		adc->dmaState = ADS1256_DMA_COMMAND_SENT;
		HAL_SPI_TransmitReceive_DMA(adc->hspi, adc->bufferTx, adc->bufferRx, 3);
	}
//	}
}

void ADS1256UpdateDMA(ADS1256_t *adc) {

	switch(adc->dmaState) {
	case ADS1256_DMA_IDLE:
		// DMA has not been started
		break;
	case ADS1256_DMA_COMMAND_SENT:
		// Next state
		adc->dmaState = ADS1256_DMA_DATA_RECEIVED;
		// Command has been sent, now receive data
		ReceiveDMA(adc);
		break;
	case ADS1256_DMA_DATA_RECEIVED:
		// Data has been received, now close DMA transfer
		CloseDMA(adc);
		//Next state
		adc->dmaState = ADS1256_DMA_IDLE;
		adc->dmaCount++;
		break;
	}
}

void ADS1256_Update(ADS1256_t *adc) {
	//Convert 24-bit signed integer to 32-bit signed integer (skip index 0)
	int32_t value = (((int32_t)adc->bufferRx[0]) << 16) |
					(((int32_t)adc->bufferRx[1]) << 8) |
					adc->bufferRx[2];
	// check if sign bit is negative
	if(value >= ((int32_t)1) << 23) {
		value |= 0xFF000000;
	}

//	adc->reading = HighPassFilterUpdate(&adc->filter, value);
	adc->reading = value;
}

void ADS1256_RegisterErrorCallback(ADS1256_t *adc,
		void (*errorCallback)(ADS1256_t *adc)) {
	adc->errorCallback = errorCallback;
}

void ADS1256_StartReading(ADS1256_t *adc) {
	ReadDataContinuous(adc);
	adc->readDataContinuous = true;
}

float ADS1256_GetVref(ADS1256_t *adc) {
	return ADS1256_VREF;
}


// Private functions

static void Wakeup(ADS1256_t *adc) {
	uint8_t command = (uint8_t)ADS1256_WAKEUP;

	// Assert chip select signal
	GPIOSetState(&adc->nCS, GPIO_LOW);

	HAL_StatusTypeDef status = HAL_SPI_Transmit(adc->hspi, &command, 1,
			HAL_TIMEOUT);
	if(status != HAL_OK) {
		HandleSPIError(adc);
	}

	// Un-assert chip select signal
	GPIOSetState(&adc->nCS, GPIO_HIGH);
}

static int32_t ReadData(ADS1256_t *adc) {
	//uint8_t command = (uint8_t)ADS1256_RDATA;

	// Assert chip select signal
	GPIOSetState(&adc->nCS, GPIO_LOW);

//	// Transmit command
//	HAL_StatusTypeDef status = HAL_SPI_Transmit(adc->hspi, &command, 1,
//			HAL_TIMEOUT);
//	if(status != HAL_OK) {
//		HandleSPIError(adc);
//	}
//
//	// Read data
//	uint8_t data[3];
//	status = HAL_SPI_Receive(adc->hspi, data, sizeof(data), HAL_TIMEOUT);
//	if(status != HAL_OK) {
//		HandleSPIError(adc);
//	}
//
//	// Un-assert chip select signal
//	GPIOSetState(&adc->nCS, GPIO_HIGH);
//
//	//Convert 24-bit signed integer to 32-bit signed integer
//	int32_t value = (((int32_t)data[0]) << 16) |
//					(((int32_t)data[1]) << 8) |
//					data[2];
//	// check if sign bit is negative
//	if(value >= ((int32_t)1) << 23) {
//		return value | 0xFF000000;
//	}
//	else {
//		return value;
//	}

	//return value;
//
//	// Faster implementation
//	uint8_t command[4] = { 0 };
//	command[0] = (uint8_t)ADS1256_RDATA;
//	uint8_t data[4];
//
//	HAL_StatusTypeDef status = HAL_SPI_TransmitReceive(adc->hspi, command,
//			data, sizeof(data), HAL_TIMEOUT);
//	if(status != HAL_OK) {
//		HandleSPIError(adc);
//	}

//	// Transmit command
//	HAL_StatusTypeDef status = HAL_SPI_Transmit(adc->hspi, &command, 1,
//			HAL_TIMEOUT);
//	if(status != HAL_OK) {
//		HandleSPIError(adc);
//	}
//
//	// Read data
//	uint8_t data[3];
//	status = HAL_SPI_Receive_IT(adc->hspi, data, sizeof(data), HAL_TIMEOUT);
//	if(status != HAL_OK) {
//		HandleSPIError(adc);
//	}

	// Un-assert chip select signal
	GPIOSetState(&adc->nCS, GPIO_HIGH);

//	//Convert 24-bit signed integer to 32-bit signed integer (ignore index 0)
//	int32_t value = (((int32_t)data[1]) << 16) |
//					(((int32_t)data[2]) << 8) |
//					data[3];
//	// check if sign bit is negative
//	if(value >= ((int32_t)1) << 23) {
//		return value | 0xFF000000;
//	}
//	else {
//		return value;
//	}
}

static void ReadDataDMA(ADS1256_t *adc) {

	// Prevent transaction conflicts
	if(adc->lockUpdate) {
		return;
	}
	adc->lockUpdate = true;

	// Assert chip select signal
	GPIOSetState(&adc->nCS, GPIO_LOW);

	memset(adc->bufferTx, 0x00, ADS1256_TRANSFER_BUFFER_SIZE);
	adc->bufferTx[0] = (uint8_t)ADS1256_RDATA;

	HAL_StatusTypeDef status = HAL_SPI_TransmitReceive_DMA(adc->hspi,
			adc->bufferTx,
			adc->bufferRx,
			ADS1256_TRANSFER_BUFFER_SIZE);
	if(status != HAL_OK) {
		HandleSPIError(adc);
	}
}


static void ReadDataContinuous(ADS1256_t *adc) {
	// Wait for data ready
	while(GPIOGetState(&adc->nDRdy) == GPIO_HIGH) {
		// Do nothing
	}

	// Assert chip select signal
	GPIOSetState(&adc->nCS, GPIO_LOW);

	// Transmit command
	uint8_t command = (uint8_t)ADS1256_RDATAC;
	HAL_StatusTypeDef status = HAL_SPI_Transmit(adc->hspi, &command, 1,
			HAL_TIMEOUT);
	if(status != HAL_OK) {
		HandleSPIError(adc);
	}

//	GPIOSetState(&adc->nCS, GPIO_HIGH);

	for(int i = 0; i < 65535; i++) {

	}

	status = HAL_SPI_Receive(adc->hspi, adc->bufferRx, 3, HAL_TIMEOUT);
	if(status != HAL_OK) {
		HandleSPIError(adc);
	}
}

static void StopReadDataContinuous(ADS1256_t *adc) {
	// Wait for data ready
	while(GPIOGetState(&adc->nDRdy) == GPIO_HIGH) {
		// Do nothing
	}

	// Assert chip select signal
	GPIOSetState(&adc->nCS, GPIO_LOW);

	// Transmit command
	uint8_t command = (uint8_t)ADS1256_SDATAC;
	HAL_StatusTypeDef status = HAL_SPI_Transmit(adc->hspi, &command, 1,
			HAL_TIMEOUT);
	if(status != HAL_OK) {
		HandleSPIError(adc);
	}

	GPIOSetState(&adc->nCS, GPIO_HIGH);
}

static void SelfCalibration(ADS1256_t *adc) {
	// Assert chip select signal
	GPIOSetState(&adc->nCS, GPIO_LOW);

	// Transmit command
	uint8_t command = (uint8_t)ADS1256_SELFCAL;
	HAL_StatusTypeDef status = HAL_SPI_Transmit(adc->hspi, &command, 1,
			HAL_TIMEOUT);
	if(status != HAL_OK) {
		HandleSPIError(adc);
	}

	GPIOSetState(&adc->nCS, GPIO_HIGH);

	// Wait until calibration is complete
	while(GPIOGetState(&adc->nDRdy) == GPIO_HIGH) {
		// Do nothing
	}
}

static void SystemCalibration(ADS1256_t *adc) {
	// Assert chip select signal
	GPIOSetState(&adc->nCS, GPIO_LOW);

	// Transmit command
	uint8_t command = (uint8_t)ADS1256_SELFCAL;
	HAL_StatusTypeDef status = HAL_SPI_Transmit(adc->hspi, &command, 1,
			HAL_TIMEOUT);
	if(status != HAL_OK) {
		HandleSPIError(adc);
	}

	GPIOSetState(&adc->nCS, GPIO_HIGH);

	// Wait until calibration is complete
	while(GPIOGetState(&adc->nDRdy) == GPIO_HIGH) {
		// Do nothing
	}
}

static uint8_t ReadRegister(ADS1256_t *adc, ADS1256Reg_e reg) {
	uint8_t wData[2];
	wData[0] = (uint8_t)(ADS1256_RREG | reg);
	// read only from one register (0x00)
	wData[1] = 0x00;

	// Assert chip select signal
	GPIOSetState(&adc->nCS, GPIO_LOW);

	delayMs(1);

	HAL_StatusTypeDef status;
	// Transmit command
	status = HAL_SPI_Transmit(adc->hspi, wData, sizeof(wData), HAL_TIMEOUT);
	if(status != HAL_OK) {
		HandleSPIError(adc);
	}

	// Pause for data to be ready to read
	delayMs(1);

	// Read data
	uint8_t rData = 0xBE;
	status = HAL_SPI_Receive(adc->hspi, &rData, 1, HAL_TIMEOUT);
	if(status != HAL_OK) {
		HandleSPIError(adc);
	}

	// Un-assert chip select signal
	GPIOSetState(&adc->nCS, GPIO_HIGH);

	return rData;
}

static void WriteRegister(ADS1256_t *adc, ADS1256Reg_e reg, uint8_t value) {
	uint8_t data[3];
	data[0] = (uint8_t)(ADS1256_WREG | reg);
	// write only to one register (0x00)
	data[1] = 0x00;
	data[2] = value;

	// Assert chip select signal
	GPIOSetState(&adc->nCS, GPIO_LOW);


	HAL_StatusTypeDef status = HAL_SPI_Transmit(adc->hspi, data, sizeof(data),
			HAL_TIMEOUT);
	if(status != HAL_OK) {
		HandleSPIError(adc);
	}

	// Un-assert chip select signal
	GPIOSetState(&adc->nCS, GPIO_HIGH);
}

static void ResetDevice(ADS1256_t *adc) {

	// Wait for data ready to go low
	while(GPIOGetState(&adc->nDRdy) == GPIO_HIGH) {
		// Do nothing
	}

	// Assert chip select signal
	GPIOSetState(&adc->nCS, GPIO_LOW);

	// Transmit command
	uint8_t command = (uint8_t)ADS1256_RESET;
	HAL_StatusTypeDef status = HAL_SPI_Transmit(adc->hspi, &command, 1,
			HAL_TIMEOUT);
	if(status != HAL_OK) {
		HandleSPIError(adc);
	}

	GPIOSetState(&adc->nCS, GPIO_HIGH);
}

static void SendCommandIT(ADS1256_t *adc) {
	// Assert chip select signal
	GPIOSetState(&adc->nCS, GPIO_LOW);

	adc->bufferTx[0] = (uint8_t)ADS1256_RDATA;
	adc->bufferRx[0] = 0;
	HAL_StatusTypeDef status = HAL_SPI_TransmitReceive_IT(adc->hspi,
			adc->bufferTx, adc->bufferRx, 1);
	if(status != HAL_OK) {
		HandleSPIError(adc);
	}
}

static void ReceiveIT(ADS1256_t *adc) {
	memset(adc->bufferTx, 0, 3);
	HAL_StatusTypeDef status = HAL_SPI_TransmitReceive_IT(adc->hspi,
			adc->bufferTx, adc->bufferRx, 3);
	if(status != HAL_OK) {
		HandleSPIError(adc);
	}
}

static void SendCommandDMA(ADS1256_t *adc) {
	// Assert chip select signal
	GPIOSetState(&adc->nCS, GPIO_LOW);

	adc->bufferTx[0] = (uint8_t)ADS1256_RDATA;
	adc->bufferRx[0] = 0;
	HAL_StatusTypeDef status = HAL_SPI_TransmitReceive_DMA(adc->hspi,
			adc->bufferTx, adc->bufferRx, 1);
	if(status != HAL_OK) {
		HandleSPIError(adc);
	}
}

static void ReceiveDMA(ADS1256_t *adc) {
	memset(adc->bufferTx, 0, 3);
	HAL_StatusTypeDef status = HAL_SPI_TransmitReceive_DMA(adc->hspi,
			adc->bufferTx, adc->bufferRx, 3);
	if(status != HAL_OK) {
		HandleSPIError(adc);
	}
}

static void CloseDMA(ADS1256_t *adc) {

	// Un-assert chip select signal
	GPIOSetState(&adc->nCS, GPIO_HIGH);

	//Convert 24-bit signed integer to 32-bit signed integer
	int32_t value = (((int32_t)adc->bufferRx[0]) << 16) |
					(((int32_t)adc->bufferRx[1]) << 8) |
					adc->bufferRx[2];
	// check if sign bit is negative
	if(value >= ((int32_t)1) << 23) {
		value |= 0xFF000000;
	}

	adc->reading = value;
}

static void HandleSPIError(ADS1256_t *adc) {
	if(adc->errorCallback != NULL) {
		adc->errorCallback(adc);
	}
}
