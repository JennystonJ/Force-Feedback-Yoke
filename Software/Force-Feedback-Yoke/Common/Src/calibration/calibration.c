/*
 * calibration.c
 *
 *  Created on: Jun 8, 2026
 *      Author: Jennyston
 */

#include "calibration/calibration.h"
#include "pid.h"
#include "log.h"

static void Calibration_CalcPIGains(float ku, float tu, float *outKp, float *outKi);

void Calibration_Init(Calibration_t *cal, FFBAxis_t *axis,
		const CalibrationConfig_t *config) {
	cal->state = CALIBRATION_STATE_IDLE;
	cal->config = config;
	cal->axis = axis;

	StaticFrictionCal_Init(&cal->staticFrictionCal, &config->staticFriction);
	FrictionCal_Init(&cal->frictionCal, &config->friction);
	RelayTuner_Init(&cal->relayTuner, &config->relay);

}

void Calibration_Start(Calibration_t *cal) {

	VelocityControl_t *velControl = FFBAxis_GetVelocityControl(cal->axis);
	PID_t *velPid = VelocityControl_GetVelocityPID(velControl);
	PID_SetGains(velPid, cal->config->calVelocityKp, 0, 0);

	Log_Print(LOG_LEVEL_INFO, __FILE__, __LINE__, "Starting Calibration...");

	FrictionCal_Start(&cal->frictionCal);
	cal->state = CALIBRATION_STATE_FRICTION_CAL;

}

void Calibration_Update(Calibration_t *cal, float deltaTime) {

	switch(cal->state) {
		case CALIBRATION_STATE_IDLE:
			// Do nothing
			break;
		case CALIBRATION_STATE_FRICTION_CAL:
		{
			MotionControlCommand_t motion;
			motion = FrictionCal_CalcMotion(&cal->frictionCal,
					FFBAxis_GetAxisKinematics(cal->axis),
					FFBAxis_GetAxisLimits(cal->axis));
			FFBAxis_ApplyMotionCommand(cal->axis, &motion, deltaTime);
			if(FrictionCal_IsCalDone(&cal->frictionCal)) {
				// Assign new friction calibration values to motion control
//				MotionControlCal_t *motionCal = MotionControl_GetCalibration(
//						FFBAxis_GetMotionControl(cal->axis));
//				motionCal->fc = cal->frictionCal.coulombTorque;
//				motionCal->fv = cal->frictionCal.viscousTorqueCoeff;
//				motionCal->sigma = 10.0;

				StaticFrictionCal_Start(&cal->staticFrictionCal);
				cal->state = CALIBRATION_STATE_STATIC_FRICTION_CAL;
			}
		}
		break;
		case CALIBRATION_STATE_STATIC_FRICTION_CAL:
		{
			MotionControlCommand_t motion;
			motion = StaticFrictionCal_CalcMotion(&cal->staticFrictionCal,
					FFBAxis_GetAxisKinematics(cal->axis), deltaTime);
			FFBAxis_ApplyMotionCommand(cal->axis, &motion, deltaTime);

			if(StaticFrictionCal_IsDone(&cal->staticFrictionCal)) {

				// Assign new friction calibration values to motion control
				MotionControlCal_t *motionCal = MotionControl_GetCalibration(
						FFBAxis_GetMotionControl(cal->axis));
				motionCal->fs = cal->staticFrictionCal.breakawayTorque;
				motionCal->fc = cal->frictionCal.coulombTorque;
				motionCal->fv = cal->frictionCal.viscousTorqueCoeff;
				motionCal->sigma = 10000.0;
				motionCal->vs = 10.0;

				cal->state = CALIBRATION_STATE_IDLE;
				//				RelayTuner_Start(&cal->relayTuner);
				//				cal->state = CALIBRATION_STATE_VELOCITY_CAL;
			}
		}
		break;
		case CALIBRATION_STATE_VELOCITY_CAL:
		{
			MotionControlCommand_t motion;
			motion = RelayTuner_CalcMotion(&cal->relayTuner,
					FFBAxis_GetAxisKinematics(cal->axis),
					deltaTime);
			FFBAxis_ApplyMotionCommand(cal->axis, &motion, deltaTime);

			if(RelayTuner_IsCalDone(&cal->relayTuner)) {
				// Calculate and assign calibration values to velocity control
				VelocityControl_t *velControl =
						FFBAxis_GetVelocityControl(cal->axis);
				PID_t *pid = VelocityControl_GetVelocityPID(velControl);

				float kP, kI;
				Calibration_CalcPIGains(cal->relayTuner.kU, cal->relayTuner.tU,
						&kP, &kI);

				PID_SetGains(pid, kP, kI, 0);

				FrictionCal_Start(&cal->frictionCal);
				cal->state = CALIBRATION_STATE_FRICTION_CAL;
			}
		}
		break;
		default:
			// Invalid state, do nothing
	}
}

bool Calibration_IsRunning(Calibration_t *cal) {
	return cal->state != CALIBRATION_STATE_IDLE;
}

static void Calibration_CalcPIGains(float ku, float tu, float *outKp, float *outKi) {
	*outKp = ku / 3.2f;
	float ti = 2.2f * tu;

	*outKi = *outKp / ti;
}
