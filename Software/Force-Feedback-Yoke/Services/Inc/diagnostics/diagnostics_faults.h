/*
 * diagnostics_faults.h
 *
 *  Created on: Jul 17, 2026
 *      Author: Jennyston
 */

#ifndef INC_DIAGNOSTICS_DIAGNOSTICS_FAULTS_H_
#define INC_DIAGNOSTICS_DIAGNOSTICS_FAULTS_H_

#include <stdint.h>

typedef struct FaultState {
	uint32_t active;
	uint32_t previous;
	uint32_t latched;
} FaultState_t;

void Diagnostics_ProcessMotorFaults(uint8_t source,
		FaultState_t *motorFaultState);
void Diagnostics_ProcessEncoderFaults(uint8_t source,
		FaultState_t *encoderFaultState);
void Diagnostics_ProcessUsbFaults(uint8_t source,
		FaultState_t *usbFaultState);

#endif /* INC_DIAGNOSTICS_DIAGNOSTICS_FAULTS_H_ */
