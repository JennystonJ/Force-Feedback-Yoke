/*
 * diagnostics_faults.c
 *
 *  Created on: Jul 17, 2026
 *      Author: Jennyston
 */

#include "diagnostics/diagnostics_faults.h"
#include "diagnostics/diagnostics_fault_types.h"
#include "log.h"


typedef enum FaultSource {
	FAULT_SOURCE_MOTOR,
	FAULT_SOURCE_ENCODER,
	FAULT_SOURCE_USB,
	FAULT_SOURCE_SIZE
} FaultSource_t;

typedef struct FaultData {
	FaultSource_t src;
	int8_t subSrc;

	uint32_t active;
	uint32_t changed;
	int8_t index;
} FaultData_t;

static const char *faultMsgs[FAULT_SOURCE_SIZE][5] = {
		{
				"Motor %d overcurrent",
				"Motor %d driver fault",
		},
		{
				"Encoder %d SPI error",
				"Encoder %d CRC error",
		},
		{
				"USB %d fault",
		}

};



static void Diagnostics_HandleFaults(FaultData_t *data);
static void Diagnostics_FaultDataInit(FaultData_t *data, FaultSource_t src,
		int8_t subSrc, uint32_t activeFlags, uint32_t changedFlags);
static int8_t Diagnostics_GetNextFault(FaultData_t *data);
static void Diagnostics_FaultDataInit(FaultData_t *data, FaultSource_t src,
		int8_t subSrc, uint32_t activeFlags, uint32_t changedFlags);

void Diagnostics_ProcessMotorFaults(uint8_t source,
		FaultState_t *motorFaultState) {

	MotorFaultFlags_e active = motorFaultState->active;
	MotorFaultFlags_e changed = active ^ motorFaultState->previous;
	motorFaultState->previous = active;

	if(changed != FAULT_MOTOR_NONE) {
		// Fault change occurred, handle faults
		FaultData_t faultData;
		Diagnostics_FaultDataInit(&faultData, FAULT_SOURCE_MOTOR, source,
				active, changed);
		Diagnostics_HandleFaults(&faultData);
	}
}

void Diagnostics_ProcessEncoderFaults(uint8_t source,
		FaultState_t *encoderFaultState) {

	EncoderFaultFlags_e active = encoderFaultState->active;
	EncoderFaultFlags_e changed = active ^ encoderFaultState->previous;
	encoderFaultState->previous = active;

	if(changed != FAULT_ENCODER_NONE) {
		// Fault change occurred, handle faults
		FaultData_t faultData;
		Diagnostics_FaultDataInit(&faultData, FAULT_SOURCE_ENCODER, source,
				active, changed);
		Diagnostics_HandleFaults(&faultData);
	}

}

void Diagnostics_ProcessUsbFaults(uint8_t source,
		FaultState_t *usbFaultState) {

	UsbFaultFlags_e active = usbFaultState->active;
	UsbFaultFlags_e changed = active ^ usbFaultState->previous;
	usbFaultState->previous = active;

	if(changed != FAULT_USB_NONE) {
		// Fault change occurred, handle faults
		FaultData_t faultData;
		Diagnostics_FaultDataInit(&faultData, FAULT_SOURCE_USB, source,
				active, changed);
		Diagnostics_HandleFaults(&faultData);
	}
}

static void Diagnostics_HandleFaults(FaultData_t *data) {

	int8_t faultType = Diagnostics_GetNextFault(data);
	// Handle faults until no faults remaining
	while(faultType >= 0) {
		Log_Print(LOG_LEVEL_WARN, __FILE__, __LINE__,
				faultMsgs[data->src][faultType],
				data->subSrc);
		faultType = Diagnostics_GetNextFault(data);
	}
}

static void Diagnostics_FaultDataInit(FaultData_t *data, FaultSource_t src,
		int8_t subSrc, uint32_t activeFlags, uint32_t changedFlags) {
	data->src = src;
	data->subSrc = subSrc;
	data->active = activeFlags;
	data->changed = changedFlags;
	data->index = 0;
}

static int8_t Diagnostics_GetNextFault(FaultData_t *data) {
	int8_t foundIndex = -1;
	int bitsRemaining = sizeof(uint32_t)*8 - data->index;
	for(int i = 0; foundIndex < 0 && i < bitsRemaining; i++) {
		// Identify if flag changed and transitioned from reset to set
		if(((data->changed & 0x01) != 0) && ((data->active & 0x01) != 0)) {
			foundIndex = data->index;
		}

		data->active >>= 1;
		data->changed >>= 1;
		data->index++;
	}

	return foundIndex;
}
