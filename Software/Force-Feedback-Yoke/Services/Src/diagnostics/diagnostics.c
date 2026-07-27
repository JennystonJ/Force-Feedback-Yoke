/*
 * diagnostics.c
 *
 *  Created on: Jul 13, 2026
 *      Author: Jennyston
 */

#include "diagnostics/diagnostics.h"
#include "diagnostics/diagnostics_private.h"

#include <string.h>
#include "log.h"


typedef struct Diagnostics {
	SystemDiagnostics_t system;

	FaultState_t motorFaults[2];
	FaultState_t encoderFaults[2];
	FaultState_t usbFaults;

	MotorStatistics_t motor[2];
} Diagnostics_t;

Diagnostics_t diag;





#define DIAG_SET_FAULT(x, f) {(x)->active |= (f); (x)->latched |= (f);}
#define DIAG_RESET_FAULT(x, f) {(x)->active &= ~(fault);}


void Diagnostics_Init(const DiagnosticsConfig_t *config) {
	// Clear diagnostics
	memset(&diag, 0, sizeof(diag));
}

void Diagnostics_Process(void) {
	Diagnostics_ProcessMotorFaults(0, &diag.motorFaults[0]);
	Diagnostics_ProcessMotorFaults(1, &diag.motorFaults[1]);

	Diagnostics_ProcessEncoderFaults(0, &diag.encoderFaults[0]);
	Diagnostics_ProcessEncoderFaults(1, &diag.encoderFaults[1]);

	Diagnostics_ProcessUsbFaults(0, &diag.usbFaults);
}

void Diagnostics_SetMotorFault(MotorFaultFlags_e fault, int index) {
	DIAG_SET_FAULT(&diag.motorFaults[index], fault);
}

void Diagnostics_ResetMotorFault(MotorFaultFlags_e fault, int index) {
	DIAG_RESET_FAULT(&diag.motorFaults[index], fault);
}

void Diagnostics_SetEncoderFault(EncoderFaultFlags_e fault, int index) {
	DIAG_SET_FAULT(&diag.encoderFaults[index], fault);
}

void Diagnostics_ResetEncoderFault(EncoderFaultFlags_e fault, int index) {
	DIAG_RESET_FAULT(&diag.encoderFaults[index], fault);
}

void Diagnostics_SetUsbFault(UsbFaultFlags_e fault) {
	DIAG_SET_FAULT(&diag.usbFaults, fault);
}

void Diagnostics_ResetUsbFault(UsbFaultFlags_e fault) {
	DIAG_RESET_FAULT(&diag.usbFaults, fault);
}








