/*
 * MT6835.c
 *
 *  Created on: Jul 5, 2025
 *      Author: Jennyston
 */

#include "devices/mt6835.h"
#include "devices/mt6835_registers.h"

#include <stddef.h>
#include <string.h>

#define HAL_TIMEOUT 10

typedef enum {
	MT6835Command_READ = 0b0011,
	MT6835Command_WRITE = 0b0110,
	MT6835Command_PRGM_EEPROM = 0b1100,
	MT6835Command_SET_ZERO = 0b0101,
	MT6835Command_BURST_READ = 0b1010
} MT6835Command_e;

typedef enum EdgeChannel {
	EDGE_CHANNEL_A,
	EDGE_CHANNEL_B
} EdgeChannel_e;

typedef enum EdgeDirection {
	EDGE_DIR_NONE,
	EDGE_DIR_FORWARD,
	EDGE_DIR_REVERSE
} EdgeDirection_e;

static const EdgeDirection_e dirTable[16] =
{
		EDGE_DIR_NONE, EDGE_DIR_FORWARD, EDGE_DIR_REVERSE,  EDGE_DIR_NONE,
		EDGE_DIR_REVERSE,  EDGE_DIR_NONE,  EDGE_DIR_NONE, EDGE_DIR_FORWARD,
		EDGE_DIR_FORWARD,  EDGE_DIR_NONE,  EDGE_DIR_NONE, EDGE_DIR_REVERSE,
		EDGE_DIR_NONE, EDGE_DIR_REVERSE, EDGE_DIR_FORWARD,  EDGE_DIR_NONE
};


typedef struct EdgeTiming {
	uint32_t time;
	EdgeDirection_e direction;
} EdgeTiming_t;

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
static void WriteRegisterCommandTo(MT6835_t *device, MT6835Command_e cmd,
		MT6835Reg_e reg, uint8_t *buffer);

static void HandleDeviceWarning(MT6835_t *device);
static void HandleSPIError(MT6835_t *device);

static int32_t CalcDmaHeadIndex(DMA_HandleTypeDef *hdma,
		uint16_t bufferLength);
static int32_t CalcCircularCount(int32_t headIndex, int32_t tailIndex,
		int32_t length);
static uint8_t GetCurrentQuadratureState(GPIO_t *gpioA, GPIO_t *gpioB);
static bool ProcessNextEdgeTiming(MT6835EdgeMeasure_t *edgeDevice,
		int32_t dmaAHeadIndex, int32_t dmaBHeadIndex, EdgeTiming_t *out);

void MT6835_Init(MT6835_t *device, SPI_HandleTypeDef *hspi, GPIO_t nCS,
		MT6835Buffer_t *buffer) {
	device->hspi = hspi;
	device->nCS = nCS;
	device->hcrc = NULL;

	device->htim = NULL;

	device->dataReady = false;
	device->buffer = buffer;


	device->encoderWarning = false;
	device->spiError = false;
	device->encoderWarningCallback = NULL;
	device->errorCallback = NULL;

	device->angle = 0;

	device->edge.edgeCount = 0;

	// Ensure chip select is not asserted
	UnassertCS(device);

	// For Debug
//	uint8_t upperByte = ReadRegister(device, MT6835Reg_ABZ_RES_13_6);
//	uint8_t lowerByte = ReadRegister(device, MT6835Reg_ABZ_RES_5_0_OFF_SWAP);

//	// Set number of ABZ pulses to 16384, ABZ ON, Swap OFF
	WriteRegister(device, MT6835Reg_ABZ_RES_13_6, 0xFF);
	WriteRegister(device, MT6835Reg_ABZ_RES_5_0_OFF_SWAP, 0xFD);

}

void MT6835_SetCRC(MT6835_t *device, CRC_HandleTypeDef *hcrc) {
	device->hcrc = hcrc;
}

void MT6835_SetABTim(MT6835_t *device, TIM_HandleTypeDef *htim) {
	device->htim = htim;
	CalibrateABCount(device);
}

void MT6835_SetABEdgeDMA(MT6835_t *device, DMA_HandleTypeDef *hdmaA,
		DMA_HandleTypeDef *hdmaB, uint32_t *edgeBuffer, uint16_t length) {
	MT6835EdgeMeasure_t *edge = &device->edge;
	edge->hdmaA = hdmaA;
	edge->hdmaB = hdmaB;
	edge->edgeBuffer = edgeBuffer;
	// TODO: log if length is less than 2
	edge->bufferLength = length;
	edge->tailIndexA = 0;
	edge->tailIndexB = 0;
}

void MT6835_SetABEdgeTim(MT6835_t *device, TIM_HandleTypeDef *htimEdge,
		uint32_t chA, uint32_t chB, GPIO_t gpioA, GPIO_t gpioB) {
	MT6835EdgeMeasure_t *edge = &device->edge;
	edge->htim = htimEdge;
	edge->htimEdgeChA = chA;
	edge->htimEdgeChB = chB;
	edge->gpioA = gpioA;
	edge->gpioB = gpioB;

	edge->valid = false;
}

void MT6835_StartEdgeTim(MT6835_t *device) {
	MT6835EdgeMeasure_t *edge = &device->edge;
	HAL_TIM_IC_Start_DMA(edge->htim, edge->htimEdgeChA, edge->edgeBuffer,
			edge->bufferLength/2);
	HAL_TIM_IC_Start_DMA(edge->htim, edge->htimEdgeChB,
			&edge->edgeBuffer[edge->bufferLength/2], edge->bufferLength/2);

	edge->prevEdgeTime = __HAL_TIM_GET_COUNTER(edge->htim);
	edge->currentEdgeTime = edge->prevEdgeTime;
	edge->edgeCount = 0;

	edge->currentState = GetCurrentQuadratureState(&edge->gpioA, &edge->gpioB);
	edge->previousState = edge->currentState;

	edge->valid = false;
}

void MT6835_UpdateEdgeTimeDMA(MT6835_t *device) {
	MT6835EdgeMeasure_t *edge = &device->edge;
	int32_t channelBufferLength = edge->bufferLength/2;

	int32_t dmaAHeadIndex = CalcDmaHeadIndex(edge->hdmaA, channelBufferLength);
	int32_t dmaBHeadIndex = CalcDmaHeadIndex(edge->hdmaB, channelBufferLength);

	int32_t countA = CalcCircularCount(dmaAHeadIndex, edge->tailIndexA,
			channelBufferLength);
	int32_t countB = CalcCircularCount(dmaBHeadIndex, edge->tailIndexB,
			channelBufferLength);

	if(edge->valid == false && (countA == 0 || countB == 0)) {
		// There is no initial measurement for comparison, return
		return;
	}
	else {
		edge->valid = true;
	}

	EdgeTiming_t timing;
	uint32_t currentEdgeTime = edge->prevEdgeTime;
	edge->edgeCount = 0;
	while(ProcessNextEdgeTiming(edge, dmaAHeadIndex, dmaBHeadIndex, &timing)) {
		switch(timing.direction) {
			case EDGE_DIR_FORWARD:
				edge->edgeCount++;
				currentEdgeTime = timing.time;
				break;
			case EDGE_DIR_REVERSE:
				edge->edgeCount--;
				currentEdgeTime = timing.time;
				break;
			case EDGE_DIR_NONE:
				break;
			default:
				// Invalid direction, do nothing
		}
	}

	edge->prevEdgeTime = edge->currentEdgeTime;
	edge->currentEdgeTime = currentEdgeTime;

}

void MT6835_GetEdgeData(MT6835_t *device, uint32_t *edgeTime,
		int32_t *edgeCount) {
	MT6835EdgeMeasure_t *edge = &device->edge;
	*edgeTime = edge->currentEdgeTime - edge->prevEdgeTime;
	*edgeCount = edge->edgeCount;
}

uint16_t MT6835_GetABPulseCount(MT6835_t *device) {

//	uint32_t count = 0;
//	if(device->htimPulse != NULL) {
//		count = __HAL_TIM_GET_COMPARE(device->htimPulse, device->htimPulseCh);
//	}
//	else {
//		// Pulse timer not set, do nothing
//	}

//	return count;
	return 0;
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

bool MT6835_GetDataReady(MT6835_t *device) {
	return device->dataReady;
}


void MT6835_Update(MT6835_t *device) {

//	StartBurstReadAngle(device);
//
//	// Read angle registers, status, and CRC
//	uint8_t data[4];
//	HAL_StatusTypeDef status = HAL_SPI_Receive(device->hspi, data,
//			sizeof(data), HAL_TIMEOUT);
//
//	if(status != HAL_OK) {
//		HandleSPIError(device);
//	}
//
//	// Process read data
//	device->angle = ((uint32_t)data[0] << 13) |
//					((uint32_t)data[1] << 5) |
//					((uint32_t)data[2] >> 3);
//	device->status = data[2] & 0x07;
//
//	// Check if warning bit(s) are set
//	if(device->status != 0x00) {
//		HandleDeviceWarning(device);
//	}
//
//	// TODO: process CRC to detect communication errors
//	uint8_t crc = data[3];
//
//	StopBurstReadAngle(device);

	AssertCS(device);

	//TODO: Add null buffer logging
	WriteRegisterCommandTo(device, MT6835Command_BURST_READ,
			MT6835Reg_ANGLE_20_13, device->buffer->tx);

	device->dataReady = false;
	HAL_StatusTypeDef status = HAL_SPI_TransmitReceive_DMA(device->hspi,
			device->buffer->tx, device->buffer->rx, 6);
	if(status != HAL_OK) {
		HandleSPIError(device);
	}
}

void MT6835_UpdateComplete(MT6835_t *device) {
	// Stop burst read angle
	UnassertCS(device);

	// Process read data
	uint8_t *rxBuffer = device->buffer->rx;
	device->angle = ((uint32_t)rxBuffer[2] << 13) |
					((uint32_t)rxBuffer[3] << 5) |
					((uint32_t)rxBuffer[4] >> 3);
	device->status = rxBuffer[4] & 0x07;

	// Check if warning bit(s) are set
	if(device->status != 0x00) {
		HandleDeviceWarning(device);
	}

	// TODO: process CRC to detect communication errors
	__attribute__((aligned(4))) uint8_t crcBuffer[4];
	crcBuffer[0] = 0;
	memcpy(crcBuffer+1, rxBuffer+2, sizeof(crcBuffer)-1);
	uint8_t crc = rxBuffer[5];
	if(device->hcrc) {
		uint32_t crcResult = HAL_CRC_Calculate(device->hcrc,
				(uint32_t *)(crcBuffer), sizeof(crcBuffer));
		if(crc != crcResult) {
			HandleSPIError(device);
		}
	}

	device->dataReady = true;
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
	GPIO_SetState(&device->nCS, GPIO_LOW);
}

static void UnassertCS(MT6835_t *device) {
	GPIO_SetState(&device->nCS, GPIO_HIGH);
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

	uint8_t txBytes[2];
	WriteRegisterCommandTo(device, cmd, reg, txBytes);

	HAL_StatusTypeDef status = HAL_SPI_Transmit(device->hspi, txBytes,
			sizeof(txBytes), HAL_TIMEOUT);
	if(status != HAL_OK) {
		HandleSPIError(device);
	}
}

static void WriteRegisterCommandTo(MT6835_t *device, MT6835Command_e cmd,
		MT6835Reg_e reg, uint8_t *buffer) {

	//TODO: Add null buffer logging

	uint16_t cmdRegAddr = ((uint16_t)cmd << 12) |
			((uint16_t)reg & 0x0FFF);

	buffer[0] = (uint8_t)(cmdRegAddr >> 8);
	buffer[1] = (uint8_t)(cmdRegAddr & 0xFF);
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

static int32_t CalcDmaHeadIndex(DMA_HandleTypeDef *hdma,
		uint16_t bufferLength) {
	int32_t dmaHeadIndex = bufferLength - __HAL_DMA_GET_COUNTER(hdma) -
			1;
	// Wrap around
	if(dmaHeadIndex < 0) {
		dmaHeadIndex = bufferLength - 1;
	}

	return dmaHeadIndex;
}

static int32_t CalcCircularCount(int32_t headIndex, int32_t tailIndex,
		int32_t length) {
	return (headIndex - tailIndex + length) % length;
}

static uint8_t GetCurrentQuadratureState(GPIO_t *gpioA, GPIO_t *gpioB) {
	return ((GPIO_GetState(gpioA) == GPIO_HIGH) << 1) |
			(GPIO_GetState(gpioB) == GPIO_LOW);
}

static bool ProcessNextEdgeTiming(MT6835EdgeMeasure_t *edgeDevice,
		int32_t dmaAHeadIndex, int32_t dmaBHeadIndex, EdgeTiming_t *out) {



//	int32_t channelBufferLength = edgeDevice->bufferLength/2;

	int32_t timeA = (int32_t)edgeDevice->edgeBuffer[edgeDevice->tailIndexA];
	int32_t timeB = (int32_t)edgeDevice->edgeBuffer[edgeDevice->bufferLength/2
													+ edgeDevice->tailIndexB];
	bool aReady = (edgeDevice->tailIndexA != dmaAHeadIndex);
	bool bReady = (edgeDevice->tailIndexB != dmaBHeadIndex);

	if(!aReady && !bReady) {
		return false;
	}

	bool processA;
	if(aReady && bReady) {
		processA = ((int32_t)(timeA - timeB) < 0);
	}
	else {
		processA = aReady;
	}

	edgeDevice->previousState = edgeDevice->currentState;
	if(processA) {
		out->time = (uint32_t)timeA;
		// Flip edge A
		edgeDevice->currentState ^= 0b10;
		// Increment and wrap around
		edgeDevice->tailIndexA =
				(edgeDevice->tailIndexA + 1) % (edgeDevice->bufferLength/2);
	}
	else {
		out->time = (uint32_t)timeB;
		// Flip edge B
		edgeDevice->currentState ^= 0b01;
		// Increment and wrap around
		edgeDevice->tailIndexB =
				(edgeDevice->tailIndexB + 1) % (edgeDevice->bufferLength/2);
	}

	uint8_t index = (edgeDevice->previousState << 2) | edgeDevice->currentState;
	out->direction = dirTable[index];

	return true;


//	edgeDevice->previousState = edgeDevice->currentState;
//	if(edgeDevice->tailIndexA != dmaAHeadIndex &&
//			(edgeDevice->edgeBuffer[edgeDevice->tailIndexA] <
//			edgeDevice->edgeBuffer[channelBufferLength +
//								   edgeDevice->tailIndexB])) {
//		out->time = edgeDevice->edgeBuffer[edgeDevice->tailIndexA];
//		// Flip edge A
//		edgeDevice->currentState ^= 0b10;
//
//		// Increment and wrap around
//		edgeDevice->tailIndexA =
//				(edgeDevice->tailIndexA + 1) % channelBufferLength;
//
//		valid = true;
//	}
//	else if (edgeDevice->tailIndexB != dmaBHeadIndex) {
//		out->time = edgeDevice->edgeBuffer[edgeDevice->tailIndexB];
//		// Flip edge B
//		edgeDevice->currentState ^= 0b01;
//
//		// Increment and wrap around
//		edgeDevice->tailIndexB =
//				(edgeDevice->tailIndexB + 1) % channelBufferLength;
//
//		valid = true;
//	}
//	else {
//		valid = false;
//	}
//
//	uint8_t index = (edgeDevice->previousState << 2) | edgeDevice->currentState;
//	out->direction = dirTable[index];
//
//	return valid;
}

