/*
 * serial_daq.c
 *
 *  Created on: Jul 16, 2025
 *      Author: Jennyston
 */

#include "devices/serial_daq.h"
#include <stddef.h>
#include <string.h>
#include "utilities/utilities.h"

void SerialDAQ_Init(SerialDAQ_t *daq, UART_HandleTypeDef *huart) {
	daq->huart = huart;
	daq->updateCompleteCallback = NULL;

	daq->rxLength = 0;
	memset(daq->txBuffer, 0, sizeof(daq->txBuffer));
	memset(daq->rxBuffer, 0, sizeof(daq->rxBuffer));

	daq->state = SERIAL_DAQ_IDLE;
}

void SerialDAQ_Receive(SerialDAQ_t *daq) {
	daq->state = SERIAL_DAQ_READING_LENGTH;

	// Receive length of next data packet
	HAL_UART_Receive_IT(daq->huart, &daq->rxLength, 1);
}

void SerialDAQ_Transmit(SerialDAQ_t *daq, const uint8_t *data, size_t len) {
	// Append length to start of TX buffer packet
	daq->txBuffer[0] = len;

	// Copy data to TX buffer
	memcpy(daq->txBuffer+1, data, len);

	//Transmit data, including length byte
	HAL_UART_Transmit_DMA(daq->huart, daq->txBuffer, len+1);
}

uint8_t *SerialDAQ_GetReadBuffer(SerialDAQ_t *daq, size_t *len) {
	*len = daq->rxLength;
	return daq->rxBuffer;
}

void SerialDAQ_RegisterUpdateCompleteCallback(SerialDAQ_t *daq,
		void (*updateCompleteCallback)(SerialDAQ_t *daq)) {
	daq->updateCompleteCallback = updateCompleteCallback;
}

void SerialDAQ_Update(SerialDAQ_t *daq) {
	switch(daq->state) {
		case SERIAL_DAQ_IDLE:
			break;
		case SERIAL_DAQ_READING_LENGTH:
			daq->state = SERIAL_DAQ_DMA_IN_PROGRESS;
			// Prevent buffer overflows from invalid length
			daq->rxLength = Min(daq->rxLength, sizeof(daq->rxBuffer));

			// Receive data
			HAL_UART_Receive_DMA(daq->huart, daq->rxBuffer,
					daq->rxLength);

			// Write confirmation byte
			daq->txBuffer[0] = 0x00;
			HAL_UART_Transmit_IT(daq->huart, daq->txBuffer, 1);
			break;
		case SERIAL_DAQ_DMA_IN_PROGRESS:
			if(daq->updateCompleteCallback != NULL) {
				daq->updateCompleteCallback(daq);
			}
			daq->state = SERIAL_DAQ_READING_LENGTH;

			// Read length of next data packet
			HAL_UART_Receive_IT(daq->huart, &daq->rxLength, 1);
			break;
		default:
			// Invalid state, do nothing
			break;
	}
}
