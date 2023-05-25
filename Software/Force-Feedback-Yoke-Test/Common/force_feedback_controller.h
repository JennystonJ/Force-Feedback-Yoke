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
	float motorKtConstant;
	float gain;
	float constantGain;
	float periodicGain;
	float springGain;
	float damperGain;
	float minimumSpringForce;
	float lockAngle;
} FFBController_t;

/*
 * Initializes force feedback controller structure.
 * parameter ffb: pointer to force feedback controller structure to be
 * initialized.
 */
void FFBInit(FFBController_t *ffb);

/*
 * Calculates motor torque from current.
 * parameter ffb: pointer to force feedback controller structure.
 * parameter motorCurrent: measured motor current.
 * returns: motor torque.
 */
float FFBComputeMotorTorque(FFBController_t *ffb, float motorCurrent);

/*
 * Calculates spring force from angular position.
 * parameter ffb: pointer to force feedback controller structure.
 * parameter measuredAngle: angular position from center.
 */
float FFBComputeSpringForce(FFBController_t *ffb, float measuredAngle);

/*
 * Calculates damper force from magnitude (usually speed or torque).
 * parameter ffb: pointer to force feedback controller structure.
 * parameter magnitude: magnitude (usually speed or torque).
 */
float FFBComputeDamperForce(FFBController_t *ffb, float magnitude);

float FFBComputerAllForces(FFBController_t * ffb, float measuredTorque,
		float measuredAngle);

#ifdef __cplusplus
}
#endif

#endif /* FORCE_FEEDBACK_CONTROLLER_H_ */
