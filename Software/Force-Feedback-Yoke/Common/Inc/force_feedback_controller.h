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

#include "motor.h"
#include "encoder.h"

#define FFB_CONTROL_HOME_POWER (MOTOR_POWER_MAX/4)

/*
 * Parameters used to apply a spring force.
 * parameter strength: spring force strength (-1.0 to 1.0).
 * parameter offset: desired position from center.
 */

typedef enum {
	FFB_STOPPED,
	FFB_RUNNING,
	FFB_IDLE,
} FFBControllerState_e;

typedef enum {
	FFB_UNHOMED,
	FFB_HOME_FIND_START,
	FFB_HOME_FIND_END,
	FFB_HOME_CENTER,
	FFB_HOME_DONE
} FFBHomingState_e;

typedef struct FFBSpringParam {
	float strength;
	float offset;
	float minimumSpringForce;
} FFBSpringParam_t;



typedef struct FFBController {
	Motor_t *motor;
	float motorKtConstant;

	Encoder_t *encoder;

	FFBControllerState_e state;
	FFBHomingState_e homingState;

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
void FFBInit(FFBController_t *ffb, Motor_t *motor, Encoder_t *encoder);

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
		int deltaTimeUs);

/*
 * Updates force feedback motor power based on force feedback parameters.
 * parameter ffb: pointer to force feedback controller structure.
 * parameter deltaTimeUs: change in time between calls in microseconds.
 */
void FFBUpdate(FFBController_t *ffb, int deltaTimeUs);

/*
 * Stops (disables) force feedback controller. Turns off motor.
 * parameter ffb: pointer to force feedback controller structure.
 */
void FFBStop(FFBController_t *ffb);

/*
 * Starts (enables) force feedback controller.
 * parameter ffb: pointer to force feedback controller structure.
 */
void FFBStart(FFBController_t *ffb);

/*
 * Obtains current force feedback controller state.
 * parameter ffb: point to force feedback controller structure.
 * returns state.
 */
FFBControllerState_e FFBGetState(FFBController_t *ffb);

void FFBHome(FFBController_t *ffb);

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
