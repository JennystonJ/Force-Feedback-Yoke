/*
 * pid.c
 *
 *  Created on: Feb 21, 2023
 *      Author: Jennyston
 */

#include "pid.h"
#include "utilities/utilities.h"

void PIDInit(PID_t *pid) {

	pid->kP = 200;
	pid->kI = 400;
	pid->kD = 0.8;

	pid->integral = 0;
	pid->preError = 0;
}

float CalcPID(PID_t *pid, float setPoint, float actual) {
	float error = setPoint - actual;

	//integrate only if error is large enough
	if(AbsFloat(error) > PID_EPSILON) {
		pid->integral += error*PID_DT;
	}

	//constrain integral
	pid->integral = ConstrainFloat(pid->integral, PID_I_MIN, PID_I_MAX);

	float derivative = (error - pid->preError)/PID_DT;

	float output = pid->kP*error + pid->kI*pid->integral + pid->kD*derivative;

	//constrain PID output
	output = ConstrainFloat(output, PID_MIN, PID_MAX);

	//update previous error for derivative calculation
	pid->preError = error;

	return output;
}
