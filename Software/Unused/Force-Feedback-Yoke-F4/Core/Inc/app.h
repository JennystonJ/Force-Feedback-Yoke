/*
 * app.h
 *
 *  Created on: Jul 13, 2024
 *      Author: Jennyston
 */

#ifndef INC_APP_H_
#define INC_APP_H_

//TODO: Move to config
#define PULLEY_AILERON_ENCODER_STEP_PER_DEGREE (4096*12)/(360.0f)
#define PULLEY_ELEVATOR_ENCODER_STEP_PER_MM ((16384*3)/(3.14159f*19.10f))

void ApplicationInit(void);
void ApplicationRun(void);
void ApplicationProcessWatchDog(void);
void ApplicationHighPriorityUpdate(int deltaTimeUs);
void ApplicationSetFastUpdateFlag(int deltaTimeUs);
void ApplicationFastUpdate(int deltaTimeUs);
void ApplicationSetUpdateFlag(int deltaTimeUs);
void ApplicationUpdate(int deltaTimeUs);
void ApplicationFFBUpdate(int deltaTimeUs);

#endif /* INC_APP_H_ */
