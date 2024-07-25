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

/*
 * Parameters used to apply a spring force.
 * parameter strength: spring force strength (-1.0 to 1.0).
 * parameter offset: desired position from center.
 */
typedef struct FFBSpringParam {
	float strength;
	float offset;
	float minimumSpringForce;
} FFBSpringParam_t;



typedef struct FFBController {
	float motorKtConstant;
	float gain;
	float constantGain;
	float periodicGain;
	float springGain;
	float damperGain;
	float lockAngle;

	struct {
		float constantStrength;
		FFBPeriodicParam_t periodic;
		FFBSpringParam_t spring;
		float damperStrength;
	} param;

} FFBController_t;

/*
 * Initializes force feedback controller structure.
 * parameter ffb: pointer to force feedback controller structure to be
 * initialized.
 */
void FFBInit(FFBController_t *ffb);

/*
 * Assigns strength of constant force.
 * parameter ffb: pointer to force feedback controller structure.
 * parameter constantStrength: strength of constant force
 */
void FFBSetConstantStrength(FFBController_t *ffb, float constantStrength);

/*
 * Assigns periodic force parameters.
 * parameter ffb: pointer to force feedback controller structure.
 * parameter periodic: structure containing periodic force parameters.
 */
void FFBSetPeriodicParams(FFBController_t *ffb, FFBPeriodicParam_t periodic);

/*
 * Assigns spring force parameters.
 * parameter ffb: pointer to force feedback controller structure.
 * parameter spring: structure containing spring force parameters.
 */
void FFBSetSpringParams(FFBController_t *ffb, FFBSpringParam_t spring);

/*
 * Assigns damper force strength.
 * parameter ffb: pointer to force feedback controller structure.
 * parameter damperStrength: strength of damper force.
 */
void FFBSetDamper(FFBController_t *ffb, float damperStrength);


/*
 * Calculates output force from given parameters.
 * parameter ffb: pointer to force feedback controller structure.
 * parameter measuredPosition: position measured from center.
 * parameter deltaTime: change in time between calls
 * returns: calculated force.
 */
float FFBCalcForces(FFBController_t *ffb, float measuredPosition,
		int deltaTime);

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
float FFBCalcConstantForce(float gain, float amount);

/**
 * Calculates periodic force.
 * parameter ffb: pointer to force feedback controller structure.
 * parameter periodic: pointer to force feedback periodic structure. Contains
 * periodic force parameters.
 * parameter deltaTime: change in time from last call to current call.
 */
float FFBCalcPeriodicForce(float gain, FFBPeriodicParam_t *periodic,
		float deltaTime);

/*
 * Calculates spring force from angular position.
 * parameter ffb: pointer to force feedback controller structure.
 * parameter measuredPosition: position measured from center.
 * parameter setPointAngle: desired angular position from center.
 * parameter strength: spring force strength (-1.0 to 1.0).
 * returns: spring force.
 */
float FFBCalcSpringForce(float gain, float measuredPosition,
		FFBSpringParam_t *springParam);

/*
 * Calculates damper force from magnitude (usually speed or torque).
 * parameter ffb: pointer to force feedback controller structure.
 * parameter magnitude: magnitude (usually speed or torque).
 * returns: damper force
 */
float FFBCalcDamperForce(float gain, float magnitude);

//float FFBCalcAllForces(FFBController_t *ffb, float measuredTorque,
//		float measuredPosition);

#ifdef __cplusplus
}
#endif

#endif /* FORCE_FEEDBACK_CONTROLLER_H_ */
