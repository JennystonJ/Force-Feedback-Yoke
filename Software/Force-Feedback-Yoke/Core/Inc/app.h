/*
 * app.h
 *
 *  Created on: Jul 13, 2024
 *      Author: Jennyston
 */

#ifndef INC_APP_H_
#define INC_APP_H_

//TODO: Move to config
#define PULLEY_AILERON_ENCODER_STEP_PER_DEGREE (12.0f)
#define PULLEY_ELEVATOR_ENCODER_STEP_PER_MM ((4096*3)/(3.14159f*19.10f))

void ApplicationInit(void);
void ApplicationRun(void);
void ApplicationUpdate(int deltaTimeUs);
void ApplicationFFBUpdate(int deltaTimeUs);

#endif /* INC_APP_H_ */
