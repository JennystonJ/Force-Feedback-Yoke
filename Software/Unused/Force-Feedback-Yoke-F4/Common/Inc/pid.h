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
	float integralLeakRate;
	float integralEpsilon;
	float intergralSlowThreshold;
	float integralSlowWeight;
	float integral;
	float preError;
	float preRawError;
	LowPass_t *lpfError;
	LowPass_t *lpfDerivative;

	float pidP;
	float pidI;
	float pidD;
} PID_t;

void PIDInit(PID_t *pid);
void PIDSetGains(PID_t *pid, float kP, float kI, float kD);
void PIDSetKP(PID_t *pid, float kP);
void PIDSetKI(PID_t *pid, float kI);
void PIDSetKD(PID_t *pid, float kD);
void PIDSetIntegralLimit(PID_t *pid, float limit);
void PIDReset(PID_t *pid);
float PIDGetError(PID_t *pid);
float CalcPID(PID_t *pid, float setPoint, float actual, float dt);
void PIDSetErrorLowPass(PID_t *pid, LowPass_t *lpfError);
void PIDSetDerivativeLowPass(PID_t *pid, LowPass_t *lpfDerivative);

#ifdef __cplusplus
}
#endif


#endif /* INC_PID_H_ */
