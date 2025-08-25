/*
 * anti_cog.c
 *
 *  Created on: May 30, 2025
 *      Author: Jennyston
 */

#include "anti_cog.h"
#include <stddef.h>
#include <math.h>
#include <string.h>

#include "bsp.h"

// For tuning use
float prevSetPoint = 0;

void AntiCogInit(AntiCog_t *antiCog, Encoder_t *encoder,
		const float *cogMap, int cogMapLength) {

	antiCog->hardware.encoder = encoder;
//	antiCog->hardware.motor = NULL;

	antiCog->cogMap = cogMap;
	antiCog->cogMapLength = cogMapLength;

	antiCog->gain = 1;

	antiCog->calibration.calibrationBuffer.batch = 0;

	LowPassFilter_Init(&antiCog->calibration.lpfError, 0.1f);
	LowPassFilter_Init(&antiCog->calibration.lpfDerivative, 0.1);

	PID_t *pid = &antiCog->calibration.pidPosition;
	PID_Init(pid);
	PID_SetGains(pid, 0.06050f, 0.00002f, 0.00028f);
	PID_SetIntegralLimit(pid, 4000000);
	PIDSetErrorLowPass(pid, &antiCog->calibration.lpfError);
	PIDSetDerivativeLowPass(pid, &antiCog->calibration.lpfDerivative);

	PID_t *pidSpeed = &antiCog->calibration.pidSpeed;
	PID_Init(pidSpeed);
	PID_SetGains(pidSpeed, 10.0f, 0.022000f, 0);
	PID_SetIntegralLimit(pidSpeed, 5000);
	pidSpeed->integralEpsilon = 0.5f;



	LowPassFilter_Init(&antiCog->calibration.lpfOutput, 0.1f);

	antiCog->calibration.velocityDampingCo = 0.1f;
	LowPassFilter_Init(&antiCog->calibration.lpfSpeed, 0.005f);

	antiCog->calibration.calibrating = false;

	// Find the number of cog map steps per one encoder count
	antiCog->cogMapStepsPerCount =
			(float)antiCog->cogMapLength /
			Encoder_GetCountPerRev(antiCog->hardware.encoder);
}

float AntiCogCalc(AntiCog_t *antiCog) {

	// Approximate anti-cog value linearly

	float encoderCount = Encoder_GetHardCount(antiCog->hardware.encoder);

	// Position to calculate anti-cog for
	float x = antiCog->cogMapStepsPerCount * encoderCount;
	// Truncate
	int x1 = (int)x;
	// x2 is the next whole integer, since x1 is a truncated value.
	// Wrap around if necessary
	int x2 = (x1 + 1) % antiCog->cogMapLength;

	// Division (x2 - x1) is omitted since value is 1 (ignoring wrap around)
	float slope = (antiCog->cogMap[x2] - antiCog->cogMap[x1]);

	float yInt = antiCog->cogMap[x1] - slope*x1;

	return (slope*x + yInt) * antiCog->gain;
}

static void LoadPositions(AntiCog_t *antiCog, int16_t startPosition) {

}

//void AntiCogStartCalibration(AntiCog_t *antiCog, Motor_t *motor, bool reverse,
//		float *cogMap, int cogMapLength) {
//	antiCog->hardware.motor = motor;
//	antiCog->calibration.currentCogMapIndex = 0;
//	antiCog->calibration.timeHeld = 0;
//
//	// Make encoder count match hardware count
//	EncoderSetCount(antiCog->hardware.encoder,
//			EncoderGetHardCount(antiCog->hardware.encoder));
//
//	AntiCogCalibrationBuffer_t *calBuffer =
//			&antiCog->calibration.calibrationBuffer;
//	calBuffer->cogMap = cogMap;
//	calBuffer->cogMapLength = cogMapLength;
//
//	// Set up bin size
//	int countsPerRev = EncoderGetCountPerRev(antiCog->hardware.encoder);
//	calBuffer->binSize = countsPerRev /
//			antiCog->cogMapLength;
//
//	memset(calBuffer->cogMap, 0, calBuffer->cogMapLength*sizeof(float));
//	memset(calBuffer->counts, 0, sizeof(calBuffer->counts));
//
//	antiCog->calibration.speed = reverse ? -ANTI_COG_CALIBRATION_SPEED :
//			ANTI_COG_CALIBRATION_SPEED;
//	antiCog->calibration.speedLocked = false;
//	antiCog->calibration.calibrating = true;
//}

//void AntiCogCalibrationUpdate2(AntiCog_t *antiCog, int deltaTimeUs) {
//	if(!antiCog->calibration.calibrating) {
//		// Calibration has not started
//		return;
//	}
//
//	float setPoint = antiCog->calibration.speed;
//	if(setPoint != prevSetPoint) {
//		// Reset integral
//		PIDReset(&antiCog->calibration.pidPosition);
//	}
//
//	float actualSpeed = LowPassFilterUpdate(&antiCog->calibration.lpfSpeed, EncoderGetSpeed(antiCog->hardware.encoder));
//	float motorSetPoint = CalcPID(&antiCog->calibration.pidSpeed, setPoint,
//			actualSpeed,
//			deltaTimeUs/1000.0f);
//	MotorSetCurrent(antiCog->hardware.motor, motorSetPoint);
//
//	int encoderHardCount = EncoderGetHardCount(antiCog->hardware.encoder);
//	// Only collect data if speed is within threshold
//	if(fabsf(PIDGetError(&antiCog->calibration.pidSpeed)) < 1.0f) {
//		// Speed error is within tolerance. Increment hold counter
//		antiCog->calibration.timeHeld += deltaTimeUs;
//
//		if(antiCog->calibration.timeHeld >= ANTI_COG_CAL_POS_HOLD_TIME) {
//			antiCog->calibration.speedLocked = true;
//
//			//Collect data
//
//			AntiCogCalibrationBuffer_t *calBuffer =
//					&antiCog->calibration.calibrationBuffer;
//			// Determine bin
//			uint16_t bin =
//					(uint16_t)(encoderHardCount / calBuffer->binSize);
//			if(bin >= 512) {
//				__BKPT(255);
//			}
//			if(calBuffer->counts[bin] < 0xFFFF) {
//				calBuffer->counts[bin]++;
//				calBuffer->cogMap[bin] += (
//						MotorGetMeasuredCurrent(antiCog->hardware.motor) -
//						calBuffer->cogMap[bin]) / calBuffer->counts[bin];
//			}
//		}
//	}
//	else {
//		// Error is too large, reset time
//		antiCog->calibration.timeHeld = 0;
//		antiCog->calibration.speedLocked = false;
//	}
//
//	prevSetPoint = setPoint;
//}

//void AntiCogCalibrationUpdate(AntiCog_t *antiCog, int deltaTimeUs) {
//	if(!antiCog->calibration.calibrating) {
//		// Calibration has not started
//		return;
//	}
//
//	int encoderCount = EncoderGetCount(antiCog->hardware.encoder);
//
//	float setPoint = antiCog->calibration.currentCogMapIndex /
//			antiCog->cogMapStepsPerCount;
////	float setPoint = pidTunerSetPoint;
//	if(setPoint != prevSetPoint) {
//		// Reset integral
//		PIDReset(&antiCog->calibration.pidPosition);
//	}
//
//	//TODO: Add a variable to encoder for reversing
//	float motorSetPoint = CalcPID(&antiCog->calibration.pidPosition, setPoint,
//			encoderCount, deltaTimeUs/1000.0f) - antiCog->calibration.velocityDampingCo *
//					LowPassFilterUpdate(&antiCog->calibration.lpfSpeed, EncoderGetSpeed(antiCog->hardware.encoder));
//	motorSetPoint = LowPassFilterUpdate(&antiCog->calibration.lpfOutput,
//			motorSetPoint);
//
//	MotorSetCurrent(antiCog->hardware.motor, motorSetPoint);
//
//	if(fabsf(PIDGetError(&antiCog->calibration.pidPosition)) <=
//			ANTI_COG_CAL_POS_COUNT_TOLERANCE) {
//		// Position error is within tolerance. Increment hold counter
//		antiCog->calibration.timeHeld += deltaTimeUs;
//		if(antiCog->calibration.timeHeld >= ANTI_COG_CAL_POS_HOLD_TIME) {
//			// Store motor set point in anti-cog map
//			antiCog->cogMap[antiCog->calibration.currentCogMapIndex] =
//					motorSetPoint;
//
//			//Proceed to next position
//			antiCog->calibration.currentCogMapIndex++;
//			if(antiCog->calibration.currentCogMapIndex >=
//					antiCog->cogMapLength) {
//				// Calibration complete, turn motor off
//				MotorSetPower(antiCog->hardware.motor, 0);
//				antiCog->calibration.calibrating = false;
//			}
//		}
//	}
//	else {
//		// Error is too large, reset time
//		antiCog->calibration.timeHeld = 0;
//	}
//
//	prevSetPoint = setPoint;
//}

bool AntiCogIsCalibrating(AntiCog_t *antiCog) {
	return antiCog->calibration.calibrating;
}
