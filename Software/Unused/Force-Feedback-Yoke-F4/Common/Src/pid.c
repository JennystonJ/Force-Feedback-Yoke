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

void PIDInit(PID_t *pid) {

	pid->kP = 200;
	pid->kI = 400;
	pid->kD = 0.8f;
	pid->integralLimit = PID_I_MAX;
	pid->integralLeakRate = 0;
	pid->integralEpsilon = PID_EPSILON;
	pid->integral = 0;
	pid->preError = 0;
	pid->preRawError = 0;
	pid->intergralSlowThreshold = 0;
	pid->integralSlowWeight = 0;

	pid->lpfError = NULL;
	pid->lpfDerivative = NULL;

	pid->pidP = 0;
	pid->pidI = 0;
	pid->pidD = 0;
}

void PIDSetGains(PID_t *pid, float kP, float kI, float kD) {
	pid->kP = kP;
	pid->kI = kI;
	pid->kD = kD;
}

void PIDSetKP(PID_t *pid, float kP) {
	pid->kP = kP;
}

void PIDSetKI(PID_t *pid, float kI) {
	pid->kI = kI;
}

void PIDSetKD(PID_t *pid, float kD) {
	pid->kD = kD;
}

float PIDGetError(PID_t *pid) {
	return pid->preError;
}

void PIDSetIntegralLimit(PID_t *pid, float limit) {
	pid->integralLimit = limit;
}

void PIDReset(PID_t *pid) {
	pid->integral = 0.0f;
	pid->preError = 0;
	pid->preRawError = 0;
	if(pid->lpfError != NULL) {
		LowPassFilterReset(pid->lpfError);
	}
	if(pid->lpfDerivative != NULL) {
		LowPassFilterReset(pid->lpfDerivative);
	}
}

float CalcPID(PID_t *pid, float setPoint, float actual, float dt) {
	float error = 0;
	if(pid->lpfError == NULL) {
		error = setPoint - actual;
	}
	else {
		error = LowPassFilterUpdate(pid->lpfError, setPoint - actual);
	}

	//integrate only if error is large enough
	if(fabsf(error) > pid->integralEpsilon) {
		float integralWeight;
		if(fabsf(error) > pid->intergralSlowThreshold)
		{
			integralWeight = 1.0f;
		}
		else {
			integralWeight = pid->integralSlowWeight;
		}
		pid->integral =
				(1.0f - pid->integralLeakRate) * pid->integral +
				integralWeight*error*dt;
	}

	//constrain integral
	pid->integral = ConstrainFloat(pid->integral, -pid->integralLimit,
			pid->integralLimit);

	float rawError = setPoint - actual;
	float derivative = (rawError - pid->preRawError)/dt;
	if(pid->lpfDerivative != NULL) {
		derivative = LowPassFilterUpdate(pid->lpfDerivative, derivative);
	}

	pid->pidP = pid->kP*error;
	pid->pidI = pid->kI*pid->integral;
	pid->pidD = pid->kD*derivative;
	float output =  pid->pidP + pid->pidI + pid->pidD;

	//constrain PID output
	output = ConstrainFloat(output, PID_MIN, PID_MAX);

	pid->preError = error;

	//update previous error for derivative calculation
	pid->preRawError = rawError;

	return output;
}

void PIDSetErrorLowPass(PID_t *pid, LowPass_t *lpfError) {
	pid->lpfError = lpfError;
}

void PIDSetDerivativeLowPass(PID_t *pid, LowPass_t *lpfDerivative) {
	pid->lpfDerivative = lpfDerivative;
}
