/*
 * serial_daq.h
 *
 *  Created on: Jul 16, 2025
 *      Author: Jennyston
 */

#ifndef INC_DEVICES_SERIAL_DAQ_H_
#define INC_DEVICES_SERIAL_DAQ_H_

#include <stm32h7xx_hal.h>
#include <stdint.h>
#include "config.h"

typedef enum SerialDAQState {
	SERIAL_DAQ_IDLE,
	SERIAL_DAQ_READING_LENGTH,
	SERIAL_DAQ_DMA_IN_PROGRESS
} SerialDAQState_e;

typedef struct SerialDAQ SerialDAQ_t;

struct SerialDAQ {
	UART_HandleTypeDef *huart;
	SerialDAQState_e state;
	void (*updateCompleteCallback)(SerialDAQ_t *daq);

	// include length byte in TX buffer
	uint8_t txBuffer[SERIAL_TX_BUFFER_SIZE+1];
	uint8_t rxLength;
	uint8_t rxBuffer[SERIAL_RX_BUFFER_SIZE];
};

void SerialDAQ_Init(SerialDAQ_t *daq, UART_HandleTypeDef *huart);
void SerialDAQ_RegisterUpdateCompleteCallback(SerialDAQ_t *daq,
		void (*updateCompleteCallback)(SerialDAQ_t *daq));
void SerialDAQ_Receive(SerialDAQ_t *daq);
void SerialDAQ_Transmit(SerialDAQ_t *daq, const uint8_t *data, size_t len);
uint8_t *SerialDAQ_GetReadBuffer(SerialDAQ_t *daq, size_t *len);
void SerialDAQ_Update(SerialDAQ_t *daq);

#endif /* INC_DEVICES_SERIAL_DAQ_H_ */
