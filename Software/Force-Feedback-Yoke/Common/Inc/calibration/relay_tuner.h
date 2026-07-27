/*
 * relay_tuner.h
 *
 *  Created on: Jun 24, 2026
 *      Author: Jennyston
 */

#ifndef INC_CALIBRATION_RELAY_TUNER_H_
#define INC_CALIBRATION_RELAY_TUNER_H_

#include "control/motion_command.h"
#include "control/axis_kinematics.h"
#include "config/calibration_config.h"
#include <stdbool.h>

typedef enum RelayTunerState {
	RELAY_TUNER_IDLE,
	RELAY_TUNER_CENTERING,
	RELAY_TUNER_ACTIVE,
	RELAY_TUNER_COMPLETE,
	RELAY_TUNER_FAILED_OUT_OF_BOUNDS
} RelayTunerState_e;

typedef struct RelayTuner {
	const RelayTunerConfig_t *config;

	RelayTunerState_e state;

	float timeElapsed;
	float lastPos;
	float lastCrossingTime;
	float currentPeakAmplitude;
	float relaySign;
	int crossingCount;
	float positionZero;

	float amplitudeSum;
	float periodSum;

	float kU;
	float tU;
} RelayTuner_t;

void RelayTuner_Init(RelayTuner_t *tuner, const RelayTunerConfig_t *config);
void RelayTuner_Start(RelayTuner_t *tuner);
MotionControlCommand_t RelayTuner_CalcMotion(RelayTuner_t *tuner,
		const AxisKinematics_t *kinematics, float deltaTime);
bool RelayTuner_IsCalDone(RelayTuner_t *tuner);

#endif /* INC_CALIBRATION_RELAY_TUNER_H_ */
