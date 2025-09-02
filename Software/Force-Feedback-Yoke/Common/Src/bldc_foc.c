/*
 * bldc_foc.c
 *
 *  Created on: Jun 22, 2025
 *      Author: Jennyston
 */

#include "bldc_foc.h"
#include "bldc_foc_math.h"
#include <math.h>

void FOC_Init(FOC_t *foc, float busVoltage) {
	foc->phaseVoltages.a = 0;
	foc->phaseVoltages.b = 0;
	foc->phaseVoltages.c = 0;

	foc->idSetPoint = 0;
	foc->iqSetPoint = 0;

	PID_Init(&foc->idPID);
	// TODO: Configure PID parameters
	PID_SetGains(&foc->idPID, 0, 0, 0);
	PID_SetIntegralLimit(&foc->idPID, 100);
	PID_SetIntegralEpsilon(&foc->idPID, 0);

	PID_Init(&foc->iqPID);
	// TODO: Configure PID parameters
	PID_SetGains(&foc->iqPID, 0, 0, 0);
	PID_SetIntegralLimit(&foc->iqPID, 100);
	PID_SetIntegralEpsilon(&foc->iqPID, 0);

	busVoltage = 12.0f;
}

float FOC_GetIDSetPoint(FOC_t *foc) {
	return foc->idSetPoint;
}

void FOC_SetIDSetPoint(FOC_t *foc, float current) {
	foc->idSetPoint = current;
}

float FOC_GetIQSetPoint(FOC_t *foc) {
	return foc->iqSetPoint;
}

void FOC_SetIQSetPoint(FOC_t *foc, float current) {
	foc->iqSetPoint = current;
}

PhaseVoltages_t FOC_Calc(FOC_t *foc, PhaseCurrents_t phaseCurrents,
		float angleElec, float deltaTimeMs) {
	ABCurrent_t abCurrent = FOCMath_CalcABCurrent(phaseCurrents);
	foc->dqCurrent = FOCMath_CalcDQCurrent(abCurrent, angleElec);

	float dVoltage = PID_Calc(&foc->idPID, foc->idSetPoint, foc->dqCurrent.d,
			deltaTimeMs);
	float qVoltage = PID_Calc(&foc->iqPID, foc->iqSetPoint, foc->dqCurrent.q,
			deltaTimeMs);

	foc->phaseVoltages = FOCMath_CalcPhaseVoltages(dVoltage, qVoltage,
			angleElec);

	return foc->phaseVoltages;
}

PID_t *FOC_GetIdPID(FOC_t *foc) {
	return &foc->idPID;
}

PID_t *FOC_GetIqPID(FOC_t *foc) {
	return &foc->iqPID;
}

DQCurrent_t FOC_GetDQCurrent(FOC_t *foc) {
	return foc->dqCurrent;
}

void FOC_ResetPID(FOC_t *foc) {
	PID_Reset(&foc->idPID);
	PID_Reset(&foc->iqPID);
}
