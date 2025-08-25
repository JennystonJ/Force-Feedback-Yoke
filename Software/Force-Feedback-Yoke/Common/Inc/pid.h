/*
 * pid.h
 *
 *  Created on: Feb 21, 2023
 *      Author: Jennyston
 */

#ifndef INC_PID_H_
#define INC_PID_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "utilities/filters.h"

#define PID_DT 0.001f
#define PID_EPSILON 0.05f
//#define PID_EPSILON 0.6f

#define PID_MAX (2400-1)
#define PID_MIN (-PID_MAX)

#define PID_I_MAX 10
#define PID_I_MIN (-PID_I_MAX)

typedef struct PID {
	float kP;
	float kI;
	float kD;
	float integralLimit;
	float integralEpsilon;
	float integral;
	float prevError;
} PID_t;

void PID_Init(PID_t *pid);
void PID_SetGains(PID_t *pid, float kP, float kI, float kD);
void PID_SetKP(PID_t *pid, float kP);
void PID_SetKI(PID_t *pid, float kI);
void PID_SetKD(PID_t *pid, float kD);
float PID_GetKP(PID_t *pid);
float PID_GetKI(PID_t *pid);
float PID_GetKD(PID_t *pid);
void PID_SetIntegralLimit(PID_t *pid, float limit);
void PID_SetIntegralEpsilon(PID_t *pid, float epsilon);
void PID_Reset(PID_t *pid);
float PID_GetError(PID_t *pid);
float PID_Calc(PID_t *pid, float setPoint, float actual, float dt);

#ifdef __cplusplus
}
#endif


#endif /* INC_PID_H_ */
