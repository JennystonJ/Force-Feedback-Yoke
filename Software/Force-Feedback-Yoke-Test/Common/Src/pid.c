/*
 * pid.c
 *
 *  Created on: Feb 21, 2023
 *      Author: Jennyston
 */

#include "pid.h"

static float Abs(float x);

void PIDInit(PID_t *pid) {
	pid->kP = 20;
	pid->kI = 0;
	pid->kD = 0;
	pid->integral = 0;
	pid->preError = 0;
}

float ComputePID(PID_t *pid, float setPoint, float actual) {
	float error = actual - setPoint;

	//integrate only if error is large enough
	if(Abs(error) > PID_EPSILON) {
		pid->integral += error*PID_DT;
	}
	//constrain integral
	if(pid->integral > PID_I_MAX) {
		pid->integral = PID_I_MAX;
	}
	else if(pid->integral < PID_I_MIN) {
		pid->integral = PID_I_MIN;
	}

	float derivative = (error - pid->preError)/PID_DT;

	float output = pid->kP*error + pid->kI*pid->integral + pid->kD*derivative;
	//constrain PID output
	if(output > PID_MAX) {
		output = PID_MAX;
	}
	else if(output < PID_MIN) {
		output = PID_MIN;
	}

	//update previous error for derivative calculation
	pid->preError = error;

	return output;
}

static float Abs(float x) {
	if(x < 0) {
		return -x;
	}
	else{
		return x;
	}
}
