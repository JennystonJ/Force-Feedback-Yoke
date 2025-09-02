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
#include "force_feedback_assist.h"
#include "force_feedback_force.h"

#include "motor.h"
#include "encoder.h"
#include "load_cell.h"
#include "utilities/filters.h"

#define FFB_CONTROL_NUM_FORCES 32

// Current to overcome stiction
#define FFB_CONTROL_HOME_CURRENT_START (0.35f)
#define FFB_CONTROL_HOME_CURRENT (0.10f)
#define FFB_CONTROL_HOME_POWER (1.0f)

// TODO: Change to variables
#define FFB_CONTROL_HOME_VELOCITY 50.0f
#define FFB_CONTROL_HOME_CURRENT_LIMIT 1.1f

#define FFB_AVG_SPEED_DT 5000

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


typedef struct FFBController {
	Motor_t *motor;
	float motorKtConstant;

	bool axisReverse;

	Encoder_t *encoder;
	LoadCell_t *loadCell;

	FFBControllerState_e state;
	FFBHomingState_e homingState;

	FFBAssist_t ffbAssist;
	bool assistEnable;

	float gain;
	float constantGain;
	float periodicGain;
	float springGain;
	float damperGain;

	float forceOut;

	int prevEncoderCountAvg;
	int speedDt;
	int prevEncoderCount;
	float speed;
	LowPass_t lpfSpeed;
	float acceleration;
	LowPass_t lpfAccel;

	float assistMin;
	float assistGain;

	int minLock;
	int maxLock;
	int travelRange;
	int lockPower;
	float lockKp;
	float lockKd;
	bool minLockReached;
	bool maxLockReached;

	int lockHysterisis;

	float unitPerRev;
	float unitPerNm;

	struct {
		float constantStrength;
		FFBPeriodicForce_t periodic;
//		FFBSpringForce_t spring;
		float damperStrength;
	} param;

	FFBForces_t forces;
	FFBForces_t homeCenterForce;

} FFBController_t;

/*
 * Initializes force feedback controller structure.
 * parameter ffb: pointer to force feedback controller structure to be
 * initialized.
 */
void FFBInit(FFBController_t *ffb, Motor_t *motor, Encoder_t *encoder);

void FFB_SetAxisReverse(FFBController_t *ffb, bool reverse);

void FFB_SetAxisCount(FFBController_t *ffb, int count);

int FFB_GetRawAxisCount(FFBController_t *ffb);

void FFBSetAssistEnable(FFBController_t *ffb, bool enabled);

void FFBSetLoadCell(FFBController_t *ffb, LoadCell_t *loadCell);

void FFB_SetLockGains(FFBController_t *ffb, float lockKp, float lockKd);

FFBAssist_t *FFB_GetFFBAssist(FFBController_t *ffb);

/*
 * Assigns strength of constant force.
 * parameter ffb: pointer to force feedback controller structure.
 * parameter force: strength of constant force
 */
void FFBSetConstant(FFBController_t *ffb, float force);

/*
 * Assigns periodic force parameters.
 * parameter ffb: pointer to force feedback controller structure.
 * parameter periodic: structure containing periodic force parameters.
 */
void FFBSetPeriodicParams(FFBController_t *ffb, FFBPeriodicForce_t periodic);

/*
 * Assigns spring force parameters.
 * parameter ffb: pointer to force feedback controller structure.
 * parameter strength: strength of spring force.
 */
void FFBSetSpring(FFBController_t *ffb, float strength);

/*
 * Assigns damper force strength.
 * parameter ffb: pointer to force feedback controller structure.
 * parameter damperStrength: strength of damper force.
 */
void FFBSetDamper(FFBController_t *ffb, float damperStrength);

/*
 * Assigns currently used forces for FFBForces structure.
 * parameter ffb: pointer to force feedback controller structure.
 * parameter forces: forces to be assigned.
 */
void FFBSetForces(FFBController_t *ffb, FFBForces_t forces);

/*
 * Assigns center forces used for homing.
 * parameter ffb: pointer to force feedback controller structure.
 * parameter homeCenterForces: forces to be assigned for centering during
 * homing.
 */
void FFB_SetHomeCenterForces(FFBController_t *ffb,
		FFBForces_t homeCenterForces);

/*
 * Calculates output force from given parameters.
 * parameter ffb: pointer to force feedback controller structure.
 * parameter measuredPosition: position measured from center.
 * parameter deltaTimeMs: change in time in milliseconds between calls
 * returns: calculated force.
 */
float FFBCalcForces(FFBController_t *ffb, float measuredPosition,
		float deltaTimeMs);

/*
 * Updates force feedback motor power based on force feedback parameters.
 * parameter ffb: pointer to force feedback controller structure.
 * parameter deltaTimeMs: change in time between calls in milliseconds.
 */
void FFBUpdate(FFBController_t *ffb, float deltaTimeMs);

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
 * parameter ffb: pointer to force feedback controller structure.
 * returns state.
 */
FFBControllerState_e FFBGetState(FFBController_t *ffb);

/*
 * Sets the lock range of the force feedback controller (in encoder counts).
 * parameter ffb: pointer to force feedback controller structure.
 * parameter min: min range of control movement (in encoder counts).
 * parameter max: max range of control movement (in encoder counts).
 */
void FFBSetControlRange(FFBController_t *ffb, int min, int max);

/*
 * Obtains minimum FFB encoder value.
 * parameter ffb: pointer to force feedback controller structure.
 * returns minimum FFB encoder value.
 */
int FFBGetMinControlRange(FFBController_t *ffb);

/*
 * Obtains travel range, which is initialized after
 * homing.
 * parameter ffb: pointer to force feedback controller structure.
 * returns travel range in encoder counts
 */
int FFBGetTravelRange(FFBController_t *ffb);

/*
 * Obtains travel range, which is initialized after homing,
 * in units based on unitPerRev.
 * parameeter ffb: pointer to force feedback controller structure.
 * returns travel range in unit
 */
float FFBGetTravelRangeInUnit(FFBController_t *ffb);

/*
 * Obtains maximum FFB encoder value.
 * parameter ffb: pointer to force feedback controller structure.
 * returns maximum FFB encoder value.
 */
int FFBGetMaxControlRange(FFBController_t *ffb);

void FFBHome(FFBController_t *ffb);

/**
 * Calculates constant force from amount.
 * parameter gain: multiplication factor of force.
 * parameter amount: amount of force.
 * returns: force.
 */
float FFBCalcConstantForce(float gain, float amount);

/**
 * Calculates periodic force.
 * parameter gain: multiplication factor of force.
 * parameter periodic: pointer to force feedback periodic structure. Contains
 * periodic force parameters.
 * parameter deltaTime: change in time from last call to current call.
 */
float FFBCalcPeriodicForce(float gain, FFBPeriodicForce_t *periodic,
		float deltaTime);

/*
 * Calculates spring force from angular position.
 * parameter gain: multiplication factor of force.
 * parameter springParam: pointer to springParam structure.
 * returns: spring force.
 */
float FFBCalcSpringForce(float gain, float measuredPosition,
		float springStrength);

/*
 * Calculates damper force from magnitude (usually speed or torque).
 * parameter gain: multiplication factor of force.
 * parameter magnitude: magnitude (usually speed or torque).
 * returns: damper force
 */
float FFBCalcDamperForce(float gain, float magnitude, float velocity);

/*
 * Calculates assist force from speed
 * parameter gain: multiplication factor of force.
 * parameter min: minimum force when speed is not zero.
 * parameter speed: rate of change of position.
 */
float FFBCalcAssist(float gain, float min, float speed);

float FFB_GetOutputForce(FFBController_t *ffb);

/*
 * Sets the units per motor revolution constant used of calculations such as
 * speed.
 * parameter ffb: pointer to force feedback controller structure.
 * parameter unitPerRev: Unit per motor revolution constant.
 */
void FFB_SetUnitPerRevConstant(FFBController_t *ffb, float unitPerRev);

/*
 * Sets the units per Nm constant used for torque/force calculations.
 * parameter ffb: pointer to force feedback controller structure.
 * parameter unitPerNm: Unit per newton-meter.
 */
void FFB_SetUnitPerNmConstant(FFBController_t *ffb, float unitPerNm);

/*
 * Resets all forces to cleared state.
 * parameter ffb: pointer to force feedback controller structure.
 */
void FFB_ResetForces(FFBController_t *ffb);

//float FFBCalcAllForces(FFBController_t *ffb, float measuredTorque,
//		float measuredPosition);

/*
 * Returns measure motor torque in force feed back units
 * parameter ffb: pointer to force feedback controller structure.
 */
float FFB_GetFeedback(FFBController_t *ffb);

float FFB_ConvertMotorTorqueToFFBUnits(FFBController_t *ffb,
		float motorTorque);
float FFB_ConvertFFBToMotorTorque(FFBController_t *ffb,
		float ffbUnit);

#ifdef __cplusplus
}
#endif

#endif /* FORCE_FEEDBACK_CONTROLLER_H_ */
