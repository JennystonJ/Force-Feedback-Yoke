/*
 * anti_cog.h
 *
 *  Created on: May 25, 2023
 *      Author: Jennyston
 */

#ifndef INC_ANTI_COG_H_
#define INC_ANTI_COG_H_

#include <stdint.h>
#include "pid.h"
#include "motor_controller.h"

#define ENCODER_COUNT_PER_REV 800

typedef struct AntiCog {
	MotorController_t *controller;
	PID_t *pid;
	int32_t calForward[ENCODER_COUNT_PER_REV];
} AntiCog_t;

void AntiCogInit(AntiCog_t *antiCog, MotorController_t *controller, PID_t *pid);
void AntiCogRun(AntiCog_t *antiCog);
void AntiCogTest(AntiCog_t *antiCog);
uint32_t AntiCogGetCalAt(AntiCog_t *antiCog, uint32_t index);

#endif /* INC_ANTI_COG_H_ */
