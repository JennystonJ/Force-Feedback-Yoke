/*
 * calibration_config.h
 *
 *  Created on: Jun 9, 2026
 *      Author: Jennyston
 */

#ifndef INC_CONFIG_CALIBRATION_CONFIG_H_
#define INC_CONFIG_CALIBRATION_CONFIG_H_

typedef struct FrictionCalConfig {
	float sweepVelocities[6];
	float sweepAcceleration;
	int numDataPoints;
} FrictionCalConfig_t;

typedef struct StaticFrictionCalConfig {
	float torqueStepRate;
	float maxTests;
	float maxSettleTime;
} StaticFrictionCalConfig_t;

typedef struct RelayTunerConfig {
	float relayAmplitiude;
	float safeLimitPos;
	int maxCrossings;
} RelayTunerConfig_t;

typedef struct CalibrationConfig {
	FrictionCalConfig_t friction;
	StaticFrictionCalConfig_t staticFriction;
	RelayTunerConfig_t relay;
	float calVelocityKp;
} CalibrationConfig_t;

extern const CalibrationConfig_t pitchCalConfig;

#endif /* INC_CONFIG_CALIBRATION_CONFIG_H_ */
