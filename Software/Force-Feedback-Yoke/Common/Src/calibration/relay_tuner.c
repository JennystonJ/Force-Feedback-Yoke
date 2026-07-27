/*
 * relay_tuner.c
 *
 *  Created on: Jun 24, 2026
 *      Author: Jennyston
 */

#include "calibration/relay_tuner.h"
#include <math.h>

void RelayTuner_Init(RelayTuner_t *tuner, const RelayTunerConfig_t *config) {
	tuner->state = RELAY_TUNER_IDLE;
	tuner->config = config;

	tuner->timeElapsed = 0.0f;
	tuner->lastPos = 0.0f;
	tuner->lastCrossingTime = 0.0f;
	tuner->currentPeakAmplitude = 0.0f;
	tuner->crossingCount = 0;
	tuner->amplitudeSum = 0.0f;
	tuner->periodSum = 0.0f;
	tuner->positionZero = 0.0f;

	tuner->kU = 0.0f;
	tuner->tU = 0.0f;
}

void RelayTuner_Start(RelayTuner_t *tuner) {
	tuner->timeElapsed = 0.0f;
	tuner->lastPos = 0.0f;
	tuner->lastCrossingTime = 0.0f;
	tuner->currentPeakAmplitude = 0.0f;
	tuner->crossingCount = 0;
	tuner->amplitudeSum = 0.0f;
	tuner->periodSum = 0.0f;
	tuner->positionZero = 0.0f;

	tuner->state = RELAY_TUNER_CENTERING;
}

MotionControlCommand_t RelayTuner_CalcMotion(RelayTuner_t *tuner,
		const AxisKinematics_t *kinematics, float deltaTime) {
	if(tuner->state == RELAY_TUNER_CENTERING)
	{
		// Check if center reached
		if(fabsf(kinematics->position) < 2.0f) {
			tuner->positionZero = kinematics->position;
			tuner->state = RELAY_TUNER_ACTIVE;
			return zeroTorqueCommand;
		}
		else {
			return (MotionControlCommand_t) {
				.type = MOTION_CONTROL_TYPE_POSITION,
						.data.positionCommand = {
							.position = 0.0f,
							.velocityLimit = M_PI * 2,
							.torqueLimit = 0.5f,
							.accelerationLimit = 12,
						},
			};
		}
	}
	else if(tuner->state != RELAY_TUNER_ACTIVE) {
		return zeroTorqueCommand;
	}

	// Update time elapsed
	tuner->timeElapsed += deltaTime;

	float zeroedPosition = kinematics->position - tuner->positionZero;

	// Safety position bounds check
	if(fabsf(zeroedPosition) > tuner->config->safeLimitPos) {
		tuner->state = RELAY_TUNER_FAILED_OUT_OF_BOUNDS;
		return zeroTorqueCommand;
	}

	// Keep track of peak amplitude
	if(fabsf(zeroedPosition) > tuner->currentPeakAmplitude) {
		tuner->currentPeakAmplitude = fabsf(zeroedPosition);
	}

	// Detect zero-crossing
	bool crossedNegative = zeroedPosition < 0.0f && tuner->lastPos >= 0.0f;
	bool crossedPositive = zeroedPosition > 0.0f && tuner->lastPos <= 0.0f;

	if(crossedNegative || crossedPositive) {
		// Calculate time it took to complete half-cycle
		float halfPeriod = tuner->timeElapsed - tuner->lastCrossingTime;
		tuner->lastCrossingTime = tuner->timeElapsed;

		if(tuner->crossingCount >0) {
			// Multiply by 2 for full period
			tuner->periodSum += (halfPeriod * 2.0f);
			tuner->amplitudeSum += tuner->currentPeakAmplitude;
		}

		tuner->crossingCount++;
		// Reset for next oscillation
		tuner->currentPeakAmplitude = 0.0f;

		// Flip relay
		tuner->relaySign = (zeroedPosition > 0.0f) ? -1.0f : 1.0f;
	}

	MotionControlCommand_t command;
	command.type = MOTION_CONTROL_TYPE_TORQUE;
	command.data.torqueCommand.torqueLimit = 1.0f;
	command.data.torqueCommand.torqueTarget = tuner->config->relayAmplitiude *
			tuner->relaySign;

	// Check if data collection is complete
	if(tuner->crossingCount > tuner->config->maxCrossings) {
		// Calculate averages
		float avgAmplitude = tuner->amplitudeSum / tuner->config->maxCrossings;
		float avgPeriod = tuner->periodSum / tuner->config->maxCrossings;

		// Calculate ultimate gain (kU) and ultimate period (tU)
		tuner->kU = (4.0f * tuner->config->relayAmplitiude) / (M_PI * avgAmplitude);
		tuner->tU = avgPeriod;

		tuner->state = RELAY_TUNER_COMPLETE;
		command.data.torqueCommand.torqueTarget = 0.0f;
	}

	// Update last position for next iteration
	tuner->lastPos = zeroedPosition;

	return command;
}

bool RelayTuner_IsCalDone(RelayTuner_t *tuner) {
	return tuner->state == RELAY_TUNER_COMPLETE;
}
