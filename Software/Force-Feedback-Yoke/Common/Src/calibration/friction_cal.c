/*
 * friction_cal.c
 *
 *  Created on: Jun 5, 2026
 *      Author: Jennyston
 */

#include "calibration/friction_cal.h"
#include <arm_math.h>
#include "utilities/utilities.h"
#include "log.h"

static MotionControlCommand_t FrictionCal_CalcSweep(FrictionCal_t *cal,
		const AxisKinematics_t *kinematics, const AxisLimits_t *limits,
		float velocity, bool *endReached);
static MotionControlCommand_t FrictionCal_ProcessRun(FrictionCal_t *cal,
		const AxisKinematics_t *kinematics, const AxisLimits_t *limits,
		bool *endReached);

static bool FrictionCal_ProcessVelocityStable(FrictionCal_t *cal,
		const AxisKinematics_t *kinematics, float velocity);
static void FrictionCal_CollectData(FrictionCal_t *cal,
		const AxisKinematics_t *kinematics, float velocity);

static void FrictionCal_UpdateFrictionCoeff(FrictionCal_t *cal);

void FrictionCal_Init(FrictionCal_t *cal,
		const FrictionCalConfig_t *config) {
	cal->config = config;

	cal->velocitySum = 0;
	cal->torqueSum = 0;
	cal->dataCount = 0;
	cal->testIndex = 0;

	cal->state = FRICTION_CAL_STATE_IDLE;
	cal->direction = FRICTION_CAL_DIRECTION_FORWARD;

	cal->coulombTorque = 0;
	cal->viscousTorqueCoeff = 0;
}

void FrictionCal_Start(FrictionCal_t *cal) {
	cal->velocitySum = 0;
	cal->torqueSum = 0;
	cal->dataCount = 0;
	cal->testIndex = 0;

	cal->coulombTorque = 0;
	cal->viscousTorqueCoeff = 0;

	cal->direction = FRICTION_CAL_DIRECTION_FORWARD;
	cal->state = FRICTION_CAL_STATE_PREPARING;

	Log_Print(LOG_LEVEL_INFO, __FILE__, __LINE__,
			"Starting friction calibration...");
}

MotionControlCommand_t FrictionCal_CalcMotion(FrictionCal_t *cal,
		const AxisKinematics_t *kinematics, const AxisLimits_t *limits) {

	// Default safe values (motor off)
	MotionControlCommand_t command = {
			.type = MOTION_CONTROL_TYPE_TORQUE,
			.data.torqueCommand = {
					.torqueLimit = 0,
					.torqueTarget = 0,
			}
	};
	bool endReached = false;

	switch(cal->state) {
		case FRICTION_CAL_STATE_IDLE:
			// Do nothing
			break;
		case FRICTION_CAL_STATE_PREPARING:
			float prepareVelocity =
					cal->direction == FRICTION_CAL_DIRECTION_FORWARD ?
							-6.28 : 6.28;
			command = FrictionCal_CalcSweep(cal, kinematics, limits, prepareVelocity,
					&endReached);
			if(endReached) {
				// Go to next state
				cal->state = FRICTION_CAL_STATE_RUNNING_FORWARD;
			}
			break;
		case FRICTION_CAL_STATE_RUNNING_FORWARD:
			command = FrictionCal_ProcessRun(cal, kinematics, limits, &endReached);
			if(endReached) {
				cal->direction = FRICTION_CAL_DIRECTION_REVERSE;
				cal->state = FRICTION_CAL_STATE_RUNNING_REVERSE;
			}
			break;
		case FRICTION_CAL_STATE_RUNNING_REVERSE:

			command = FrictionCal_ProcessRun(cal, kinematics, limits, &endReached);
			if(endReached) {

				// Calculate gravity torque
				cal->gravityTorque[cal->testIndex] =
						(cal->torqueVelDataForward[cal->testIndex][1] +
						cal->torqueVelDataReverse[cal->testIndex][1])/2;

				cal->testIndex++;
				if(cal->testIndex < sizeof(cal->config->sweepVelocities)/
						sizeof(cal->config->sweepVelocities[0])) {
					cal->direction = FRICTION_CAL_DIRECTION_FORWARD;
					cal->state = FRICTION_CAL_STATE_RUNNING_FORWARD;
				}
				else {
					FrictionCal_UpdateFrictionCoeff(cal);

					Log_Print(LOG_LEVEL_INFO, __FILE__, __LINE__,
							"Friction Calibration complete: Coloumb " \
							"Torque: %.4f, Viscous Torque Coeff: %.4f",
							cal->coulombTorque, cal->viscousTorqueCoeff);

					cal->state = FRICTION_CAL_STATE_IDLE;
				}
			}
		default:
			// Invalid state, do nothing
			break;
	}

	return command;
}

static void FrictionCal_UpdateFrictionCoeff(FrictionCal_t *cal) {

	// 1. Setup Data Arrays

	// Corrected torque data
	float32_t correctedTorque[14];
	// Forward sweep
	for(int i = 0; i < 7; i++) {
		correctedTorque[i] = cal->torqueVelDataForward[i][1] - cal->gravityTorque[i];
	}
	// Reverse sweep
	for(int i = 7; i < 14; i++) {
		correctedTorque[i] = cal->torqueVelDataReverse[i-7][1] -
				cal->gravityTorque[i-7];
	}

	// Velocity data
	float32_t velocityData[14*2];
	// Forward sweep
	for(int i = 0; i < 7; i++) {
		velocityData[i*2] = signf(cal->torqueVelDataForward[i][0]);
		velocityData[i*2 + 1] = cal->torqueVelDataForward[i][0];
	}
	// Reverse sweep
	for(int i = 7; i < 14; i++) {
		velocityData[i*2] = signf(cal->torqueVelDataReverse[i-7][0]);
		velocityData[i*2 + 1] = cal->torqueVelDataReverse[i-7][0];
	}


	// 2. Initialize Matrices
	arm_matrix_instance_f32 x, xT, xTx, xTxInv, xTxInvxT, y, beta;
	float32_t xTData[2*14];
	float32_t xTxData[2*2];
	float32_t xTxInvData[2*2];
	float32_t xTxInvxTData[2*14];
	float32_t betaData[2];

	arm_mat_init_f32(&x, 14, 2, velocityData);
	arm_mat_init_f32(&xT, 2, 14, xTData);
	arm_mat_init_f32(&xTx, 2, 2, xTxData);
	arm_mat_init_f32(&xTxInv, 2, 2, xTxInvData);
	arm_mat_init_f32(&xTxInvxT, 2, 14, xTxInvxTData);
	arm_mat_init_f32(&y, 14, 1, correctedTorque);
	arm_mat_init_f32(&beta, 2, 1, betaData);




	arm_mat_trans_f32(&x, &xT);
	arm_mat_mult_f32(&xT, &x, &xTx);
	arm_status status = arm_mat_inverse_f32(&xTx, &xTxInv);

	if(status == ARM_MATH_SUCCESS) {
		arm_mat_mult_f32(&xTxInv, &xT, &xTxInvxT);
		arm_mat_mult_f32(&xTxInvxT, &y, &beta);

		cal->coulombTorque = betaData[0];
		cal->viscousTorqueCoeff = betaData[1];
	}
	else {
		cal->coulombTorque = 0.0f;
		cal->viscousTorqueCoeff = 0.0f;
	}
}

static bool FrictionCal_ProcessVelocityStable(FrictionCal_t *cal,
		const AxisKinematics_t *kinematics, float velocity) {

	bool stable = false;
	// Check if velocity is within acceptable range
	if(fabsf(velocity - kinematics->velocity) < fabsf(velocity) * 0.20) {
		// Wait until velocity is stable
		if(cal->velocityHoldCount < 10) {
			cal->velocityHoldCount++;
		}
		else {
			stable = true;
		}
	}
	else {
		// Reset hold count (velocity is unstable)
		cal->velocityHoldCount = 0;
	}

	return stable;
}

static void FrictionCal_CollectData(FrictionCal_t *cal,
		const AxisKinematics_t *kinematics, float velocity) {
	cal->velocitySum += kinematics->velocity;
	cal->torqueSum += kinematics->motorTorque;
	cal->dataCount++;
}

static MotionControlCommand_t FrictionCal_CalcSweep(FrictionCal_t *cal,
		const AxisKinematics_t *kinematics, const AxisLimits_t *limits,
		float velocity, bool *endReached) {
	MotionControlCommand_t command = {
			.type = MOTION_CONTROL_TYPE_VELOCITY,
			.data.velocityCommand = {
					.accelerationLimit = 0,
					.velocityTarget = 0,
					.torqueLimit = 0,
			}
	};

	// Check if end reached
	AxisRange_t posRange = AxisLimits_GetOperatingPositionRange(limits);
	if((velocity < 0 &&
			fabsf(kinematics->position - posRange.min) < 3.0f) ||
			(velocity > 0 &&
					fabsf(kinematics->position - posRange.max) < 3.0f)) {
		*endReached = true;
	}
	else {
		// Calculate velocity command
		command.type = MOTION_CONTROL_TYPE_VELOCITY;
		VelocityControlCommand_t *velCommand = &command.data.velocityCommand;
		velCommand->accelerationLimit = cal->config->sweepAcceleration;
		velCommand->velocityTarget = velocity;
		velCommand->torqueLimit = 0.2f;

		*endReached = false;
	}

	return command;
}

static MotionControlCommand_t FrictionCal_ProcessRun(FrictionCal_t *cal,
		const AxisKinematics_t *kinematics, const AxisLimits_t *limits,
		bool *endReached) {

	// Default safe values (motor off)
	MotionControlCommand_t command = {
			.type = MOTION_CONTROL_TYPE_TORQUE,
			.data.torqueCommand = {
					.torqueLimit = 0,
					.torqueTarget = 0,
			}
	};

	float velocity = cal->direction == FRICTION_CAL_DIRECTION_FORWARD ?
			cal->config->sweepVelocities[cal->testIndex] :
			-cal->config->sweepVelocities[cal->testIndex];
	command = FrictionCal_CalcSweep(cal, kinematics, limits, velocity,
			endReached);

	if(*endReached) {
		float (*torqueVelData)[2] = cal->direction ==
				FRICTION_CAL_DIRECTION_FORWARD ?
						cal->torqueVelDataForward :
						cal->torqueVelDataReverse;

		// Calculate and store average of data points
		torqueVelData[cal->testIndex][0] =
				cal->velocitySum/cal->dataCount;
		torqueVelData[cal->testIndex][1] =
				cal->torqueSum/cal->dataCount;

		cal->velocityHoldCount = 0;
		cal->velocitySum = 0;
		cal->torqueSum = 0;
		cal->dataCount = 0;
	}
	else if(FrictionCal_ProcessVelocityStable(cal, kinematics, velocity)) {
		FrictionCal_CollectData(cal, kinematics, velocity);
	}

	return command;
}

bool FrictionCal_IsCalDone(FrictionCal_t *cal) {
	return cal->state == FRICTION_CAL_STATE_IDLE;
}
