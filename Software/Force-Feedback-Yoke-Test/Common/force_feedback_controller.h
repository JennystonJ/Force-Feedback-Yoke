/*
 * force_feedback_controller.h
 *
 *  Created on: May 24, 2023
 *      Author: Jennyston
 */

#ifndef FORCE_FEEDBACK_CONTROLLER_H_
#define FORCE_FEEDBACK_CONTROLLER_H_

#ifdef __cplusplus
extern "C" {
#endif


typedef struct FFBController {
	float motorKiConstant;
	float gain;
	float constantGain;
	float periodicGain;
	float springGain;
	float damperGain;
	float minimumForce;
	float lockAngle;
} FFBController_t;

/*
 * Initializes force feedback structure.
 * parameter ffb: Force feedback structure to be initialized
 */
void FFBInit(FFBController_t *ffb);

#ifdef __cplusplus
}
#endif

#endif /* FORCE_FEEDBACK_CONTROLLER_H_ */
