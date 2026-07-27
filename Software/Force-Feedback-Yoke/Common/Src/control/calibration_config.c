/*
 * calibration_config.c
 *
 *  Created on: Jun 9, 2026
 *      Author: Jennyston
 */

#include "config/calibration_config.h"
#include <math.h>

const CalibrationConfig_t pitchCalConfig = {
		.friction = {
				.sweepVelocities = {5, 8, 16, 32, 48, 64},
				.sweepAcceleration = 80,
				.numDataPoints = 500,

		},
		.staticFriction = {
			.torqueStepRate = 0.005f,
			.maxTests = 10,
			.maxSettleTime = 0.5f,
		},
		.relay = {
			.relayAmplitiude = 0.04f,
			.safeLimitPos = (M_PI/180.0f * 360.0f),
			.maxCrossings = 25,
		},
		.calVelocityKp = 0.075,
};
