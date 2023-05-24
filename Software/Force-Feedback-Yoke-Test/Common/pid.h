/*
 * pid.h
 *
 *  Created on: Feb 21, 2023
 *      Author: Jennyston
 */

#ifndef INC_PID_H_
#define INC_PID_H_

#define PID_DT 0.010f
#define PID_EPSILON 0.6f

#define PID_MAX (2400-1)
#define PID_MIN (-PID_MAX)

#define PID_I_MAX 4
#define PID_I_MIN (-PID_I_MAX)

typedef struct PID {
	float kP;
	float kI;
	float kD;
	float integral;
	float preError;
} PID_t;

void PIDInit(PID_t *pid);
float ComputePID(PID_t *pid, float setPoint, float actual);

#endif /* INC_PID_H_ */
