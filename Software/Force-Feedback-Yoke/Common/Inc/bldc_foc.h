/*
 * bldc_foc.h
 *
 *  Created on: Jun 22, 2025
 *      Author: Jennyston
 */

#ifndef INC_BLDC_FOC_H_
#define INC_BLDC_FOC_H_

#include "bldc_foc_types.h"
#include "pid.h"

typedef struct FOC {
	PhaseVoltages_t phaseVoltages;
	DQCurrent_t dqCurrent;

	float idSetPoint;
	float iqSetPoint;
	PID_t idPID;
	PID_t iqPID;

	float busVoltage;
} FOC_t;

void FOC_Init(FOC_t *foc, float busVoltage);

float FOC_GetIDSetPoint(FOC_t *foc);
void FOC_SetIDSetPoint(FOC_t *foc, float current);

float FOC_GetIQSetPoint(FOC_t *foc);
void FOC_SetIQSetPoint(FOC_t *foc, float current);

PhaseVoltages_t FOC_Calc(FOC_t *foc, PhaseCurrents_t phaseCurrents,
		float angleElec, float deltaTimeMs);

DQCurrent_t FOC_GetDQCurrent(FOC_t *foc);

PID_t *FOC_GetIdPID(FOC_t *foc);
PID_t *FOC_GetIqPID(FOC_t *foc);

void FOC_ResetPID(FOC_t *foc);

#endif /* INC_BLDC_FOC_H_ */
