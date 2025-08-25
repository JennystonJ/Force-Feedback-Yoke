/*
 * pid_tuner.h
 *
 *  Created on: Jul 15, 2025
 *      Author: Jennyston
 */

#ifndef INC_PID_TUNER_H_
#define INC_PID_TUNER_H_

#include "devices/serial_daq.h"
#include "pid.h"

void PIDTuner_Init(SerialDAQ_t *serialDaq, PID_t *pidVar,
		void (*setSetPointFunc)(float setPoint),
		float (*getActualFunc)(void),
		float (*getPowerFunc)(void));
void PIDTuner_Start(SerialDAQ_t *serialDaq);
void PIDTuner_Stop(void);

#endif /* INC_PID_TUNER_H_ */
