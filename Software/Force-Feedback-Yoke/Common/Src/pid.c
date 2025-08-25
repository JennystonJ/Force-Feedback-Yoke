/*
 * pid.c
 *
 *  Created on: Feb 21, 2023
 *      Author: Jennyston
 */

#include "pid.h"
#include "utilities/utilities.h"
#include <stddef.h>
#include <math.h>

void PID_Init(PID_t *pid) {

	pid->kP = 0;
	pid->kI = 0;
	pid->kD = 0;
	pid->integralLimit = PID_I_MAX;
	pid->integralEpsilon = PID_EPSILON;
	pid->integral = 0;
	pid->prevError = 0;
}

void PID_SetGains(PID_t *pid, float kP, float kI, float kD) {
	pid->kP = kP;
	pid->kI = kI;
	pid->kD = kD;
}

void PID_SetKP(PID_t *pid, float kP) {
	pid->kP = kP;
}

void PID_SetKI(PID_t *pid, float kI) {
	pid->kI = kI;
}

void PID_SetKD(PID_t *pid, float kD) {
	pid->kD = kD;
}

float PID_GetError(PID_t *pid) {
	return pid->prevError;
}

float PID_GetKP(PID_t *pid) {
	return pid->kP;
}

float PID_GetKI(PID_t *pid) {
	return pid->kI;
}

float PID_GetKD(PID_t *pid) {
	return pid->kD;
}

void PID_SetIntegralLimit(PID_t *pid, float limit) {
	pid->integralLimit = limit;
}

void PID_SetIntegralEpsilon(PID_t *pid, float epsilon) {
	pid->integralEpsilon = epsilon;
}

void PID_Reset(PID_t *pid) {
	pid->integral = 0;
	pid->prevError = 0;
}

float PID_Calc(PID_t *pid, float setPoint, float actual, float dt) {
	float error = setPoint - actual;

	// Only integrate if error is large enough
	if(fabsf(error) > pid->integralEpsilon) {
		pid->integral += error*dt;
		pid->integral = ConstrainFloat(pid->integral, -pid->integralLimit,
				pid->integralLimit);
	}

	// Calculate derivative
	float derivative = (error - pid->prevError) / dt;

	float result = pid->kP * error +
			pid->kI * pid->integral +
			pid->kD * derivative;

	// Update previous error
	pid->prevError = error;

	return result;
}
