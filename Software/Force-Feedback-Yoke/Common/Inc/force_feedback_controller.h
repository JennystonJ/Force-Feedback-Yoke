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

#include "force_feedback_periodic.h"

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
float FFBCalcMotorTorque(FFBController_t *ffb, float motorCurrent);

/**
 * Calculates constant force from amount.
 * parameter ffb: pointer to force feedback controller structure.
 * parameter amount: amount of force.
 * returns: force.
 */
float FFBCalcConstantForce(FFBController_t *ffb, float amount);

/**
 * Calculates periodic force.
 * parameter ffb: pointer to force feedback controller structure.
 * parameter periodic: pointer to force feedback periodic structure. Contains
 * periodic force parameters.
 * parameter deltaTime: change in time from last call to current call.
 */
float FFBCalcPeriodicForce(FFBController_t *ffb, FFBPeriodic_t *periodic,
		float deltaTime);

/*
 * Calculates spring force from angular position.
 * parameter ffb: pointer to force feedback controller structure.
 * parameter measuredAngle: angular position measured from center.
 * parameter setPointAngle: desired angular position from center.
 * parameter strength: spring force strength (-1.0 to 1.0).
 * returns: spring force.
 */
float FFBCalcSpringForce(FFBController_t *ffb, float measuredAngle,
		float setPointAngle, float strength);
/*
 * Calculates damper force from magnitude (usually speed or torque).
 * parameter ffb: pointer to force feedback controller structure.
 * parameter magnitude: magnitude (usually speed or torque).
 * returns: damper force
 */
float FFBCalcDamperForce(FFBController_t *ffb, float magnitude);

float FFBCalcAllForces(FFBController_t * ffb, float measuredTorque,
		float measuredAngle);

#ifdef __cplusplus
}
#endif

#endif /* FORCE_FEEDBACK_CONTROLLER_H_ */
