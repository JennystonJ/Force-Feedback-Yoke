/*
 * calibration.h
 *
 *  Created on: Jun 8, 2026
 *      Author: Jennyston
 */

#ifndef INC_CALIBRATION_CALIBRATION_H_
#define INC_CALIBRATION_CALIBRATION_H_

#include "control/axis_kinematics.h"
#include "control/velocity_control.h"
#include "config/calibration_config.h"
#include "control/ffb_axis.h"
#include "calibration/friction_cal.h"
#include "calibration/static_friction_cal.h"
#include "calibration/relay_tuner.h"
#include <stdbool.h>

typedef enum CalibrationState {
	CALIBRATION_STATE_IDLE,
	CALIBRATION_STATE_FRICTION_CAL,
	CALIBRATION_STATE_STATIC_FRICTION_CAL,
	CALIBRATION_STATE_VELOCITY_CAL
} CalibrationState_e;


typedef struct Calibration {
	CalibrationState_e state;
	const CalibrationConfig_t *config;
	FFBAxis_t *axis;

	FrictionCal_t frictionCal;
	StaticFrictionCal_t staticFrictionCal;
	RelayTuner_t relayTuner;

	float calKp;
} Calibration_t;

void Calibration_Init(Calibration_t *cal, FFBAxis_t *axis,
		const CalibrationConfig_t *config);
void Calibration_Start(Calibration_t *cal);
void Calibration_Update(Calibration_t *cal, float deltaTime);
bool Calibration_IsRunning(Calibration_t *cal);

#endif /* INC_CALIBRATION_CALIBRATION_H_ */
