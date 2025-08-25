/*
 * pid_tuner.c
 *
 *  Created on: Jul 15, 2025
 *      Author: Jennyston
 */

#include "pid_tuner.h"

#include "bsp.h"

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef enum RxDataType {
	RX_DATA_TYPE_SYNC,
	RX_DATA_TYPE_READ_PID,
	RX_DATA_TYPE_READ_ACTUAL,
	RX_DATA_TYPE_INVALID,
} RxDataType_e;

// Private variables
static bool pidTunerInitialized = false;
static bool pidTunerStarted = false;

static struct {
	PID_t *pidVar;
	void (*setSetPointFunc)(float setPoint);
	float (*getActualFunc)(void);
	float (*getPowerFunc)(void);
} pidTuner;

// Private forward function prototypes
static void SerialDAQUpdateCpltCallback(SerialDAQ_t *serialDaq);
static RxDataType_e ProcessDAQRxData(const uint8_t *data, size_t len);
static void TransmitActual(SerialDAQ_t *serialDaq);
static void TransmitPID(SerialDAQ_t *serialDaq);
static float ReadNextFloat(const uint8_t *buffer, size_t *index);

void PIDTuner_Init(SerialDAQ_t *serialDaq, PID_t *pidVar,
		void (*setSetPointFunc)(float setPoint),
		float (*getActualFunc)(void),
		float (*getPowerFunc)(void)) {
	pidTunerInitialized = false;
	pidTunerStarted = false;

	pidTuner.pidVar = pidVar;
	pidTuner.setSetPointFunc = setSetPointFunc;
	pidTuner.getActualFunc = getActualFunc;
	pidTuner.getPowerFunc = getPowerFunc;

//	Bsp_RegisterSerialDAQTxCallback(&SerialDAQTxCallback);
//	Bsp_RegisterSerialDAQRxCallback(&SerialDAQRxCallback);
	SerialDAQ_RegisterUpdateCompleteCallback(serialDaq,
			&SerialDAQUpdateCpltCallback);

	pidTunerInitialized = true;
}

void PIDTuner_Start(SerialDAQ_t *serialDaq) {
	if(!pidTunerInitialized) {
		// PID tuner has not been initialized
		return;
	}

	pidTunerStarted = true;

	SerialDAQ_Receive(serialDaq);
}

void PIDTuner_Stop(void) {
	pidTunerStarted = false;
}

// Private functions

static void SerialDAQUpdateCpltCallback(SerialDAQ_t *serialDaq) {
	if(!pidTunerStarted) {
		return;
	}

	size_t len;
	uint8_t *buffer = SerialDAQ_GetReadBuffer(serialDaq, &len);
	uint8_t data[SERIAL_RX_BUFFER_SIZE];
	// Copy buffer to preserve contents from overwrite
	memcpy(data, buffer, len);

	RxDataType_e rxType = ProcessDAQRxData(data, len);

	switch(rxType) {
		case RX_DATA_TYPE_READ_ACTUAL:
			TransmitActual(serialDaq);
			break;
		case RX_DATA_TYPE_READ_PID:
			TransmitPID(serialDaq);
			break;
		case RX_DATA_TYPE_SYNC:
			// Do nothing
			break;
		case RX_DATA_TYPE_INVALID:
			// Do nothing
			break;
		default:
			break;
	}

}

static RxDataType_e ProcessDAQRxData(const uint8_t *data, size_t len) {

	RxDataType_e rxType;

	if(len == sizeof(float)*4) {
		size_t index = 0;
		float setPoint = ReadNextFloat(data, &index);
		float kP = ReadNextFloat(data, &index);
		float kI = ReadNextFloat(data, &index);
		float kD = ReadNextFloat(data, &index);

//		PID_SetGains(pidTuner.pidVar, kP, kI, kD);
//		pidTuner.setSetPointFunc(setPoint);

		rxType = RX_DATA_TYPE_READ_ACTUAL;
	}
	else if(len == 1) {
		// Ignore 1 byte data field
		rxType = RX_DATA_TYPE_READ_PID;
	}
	else if(len == 0){
		// Sync
		rxType = RX_DATA_TYPE_SYNC;
	}
	else {
		// Invalid data, do nothing
		rxType = RX_DATA_TYPE_INVALID;
	}

	return rxType;
}

static void TransmitActual(SerialDAQ_t *serialDaq) {
	uint8_t data[sizeof(uint32_t) + sizeof(float)*2];

	uint32_t *sysTick = (uint32_t *)data;
	*sysTick = Bsp_GetTick();

	float *actual = (float *)(data+sizeof(uint32_t));
	*actual = pidTuner.getActualFunc();

	float *power = (float *)(data+sizeof(uint32_t)+sizeof(float));
	*power = pidTuner.getPowerFunc();

	SerialDAQ_Transmit(serialDaq, data, sizeof(data));
}

static void TransmitPID(SerialDAQ_t *serialDaq) {
	float pidValues[3];
	pidValues[0] = PID_GetKP(pidTuner.pidVar);
	pidValues[1] = PID_GetKI(pidTuner.pidVar);
	pidValues[2] = PID_GetKD(pidTuner.pidVar);
	SerialDAQ_Transmit(serialDaq, (uint8_t *)pidValues, sizeof(pidValues));
}

static float ReadNextFloat(const uint8_t *buffer, size_t *index) {
	float data = *(float *)(buffer + *index);
	*index += sizeof(float);
	return data;
}
