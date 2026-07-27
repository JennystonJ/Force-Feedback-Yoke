/*
 * diagnostics.h
 *
 *  Created on: Jul 13, 2026
 *      Author: Jennyston
 */

#ifndef INC_DIAGNOSTICS_H_
#define INC_DIAGNOSTICS_H_

#include <stdbool.h>
#include <stdint.h>
#include "diagnostics_config.h"
#include "diagnostics_types.h"

typedef struct LoopDiagnostics {
	uint32_t executionTimeCycles;
	uint32_t maxExecutionTimeCycles;
	uint32_t missedDeadlines;
} LoopDiagnostics_t;



typedef struct MotorCurrentStatistics {
	uint32_t maxCurrent;
	uint32_t tripCount;
} MotorCurrentStatistics_t;



typedef struct MotorStatistics {
	MotorCurrentStatistics_t currentStatistics;
	LoopDiagnostics_t focTiming;
} MotorStatistics_t;


typedef struct SystemDiagnostics {
	uint32_t uptime;
	uint32_t loopTiming;
} SystemDiagnostics_t;

#define DIAGNOSTICS_EVENT_QUEUE_SIZE 32









void Diagnostics_Init(const DiagnosticsConfig_t *config);
void Diagnostics_Process(void);
void Diagnostics_SetMotorFault(MotorFaultFlags_e fault, int index);
void Diagnostics_ResetMotorFault(MotorFaultFlags_e fault, int index);
void Diagnostics_SetEncoderFault(EncoderFaultFlags_e fault, int index);
void Diagnostics_ResetEncoderFault(EncoderFaultFlags_e fault, int index);
void Diagnostics_SetUsbFault(UsbFaultFlags_e fault);
void Diagnostics_ResetUsbFault(UsbFaultFlags_e fault);

void Diagnostics_IncrementMotorCounter(uint8_t motorId,
		DiagnosticsMotorCounter_e counter);
void Diagnostics_IncrementEncoderCounter(uint8_t encoderId,
		DiagnosticsEncoderCounter_e counter);

void Diagnostics_PostEvent(DiagnosticsEvent_e event, uint8_t source);

#endif /* INC_DIAGNOSTICS_H_ */
