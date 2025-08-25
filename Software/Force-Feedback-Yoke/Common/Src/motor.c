/*
 * motor.c
 *
 *  Created on: Mar 18, 2024
 *      Author: Jennyston
 */

#include "motor.h"
#include "utilities/utilities.h"
#include <stdbool.h>
#include <stddef.h>
#include <math.h>

static float EncoderCountToRad(Encoder_t *encoder);
static float RadPerSecToRPM(float radPerSec);
static float RPMToRadPerSec(float rpm);

void Motor_Init(Motor_t *motor, MotorInterface_t interface) {
	motor->interface = interface;
	motor->encoder = NULL;
	motor->currentLimitTripCount = 0;

	motor->velocityRpm = 0.0f;
	motor->velocityLoopFreqDivider = 100;
	motor->velocityLoopCount = 0;

	motor->mode = MOTOR_CONTROL_VOLTAGE;
}

void Motor_SetEnable(Motor_t *motor, bool enabled) {
	motor->interface.MotorSetEnable(&motor->interface, enabled);
}

float Motor_GetBusVoltage(Motor_t *motor) {
	return motor->interface.MotorGetBusVoltage(&motor->interface);
}

float Motor_GetVoltage(Motor_t *motor) {
	return motor->interface.MotorGetVoltage(&motor->interface);
}

void Motor_SetVoltage(Motor_t *motor, float voltage) {
	motor->mode = MOTOR_CONTROL_VOLTAGE;
	return motor->interface.MotorSetVoltage(&motor->interface,
			voltage);
}

float Motor_GetCurrent(Motor_t *motor) {
	return motor->interface.MotorGetCurrent(&motor->interface);
}

int Motor_GetNumCurrentSensors(Motor_t *motor) {
	return motor->interface.MotorGetNumCurrentSensors(&motor->interface);
}

float Motor_GetMeasuredCurrent(Motor_t *motor, int index) {
	return motor->interface.MotorGetCurrentReading(&motor->interface, index);
}

float Motor_GetMeasuredTotalCurrent(Motor_t *motor) {
	return motor->interface.MotorGetTotalCurrentReading(&motor->interface);
}

void Motor_SetCurrent(Motor_t *motor, float current) {
	motor->mode = MOTOR_CONTROL_CURRENT;
	motor->interface.MotorSetCurrent(&motor->interface, current);
}

float Motor_GetCurrentLimit(Motor_t *motor) {
	return motor->interface.MotorGetCurrentLimit(&motor->interface);
}

void Motor_SetCurrentLimit(Motor_t *motor, float currentLimit) {
	motor->interface.MotorSetCurrentLimit(&motor->interface, currentLimit);
}

float Motor_GetTorque(Motor_t *motor) {
	return motor->interface.MotorGetTorque(&motor->interface);
}

float Motor_GetTorqueLimit(Motor_t *motor) {
	return motor->interface.MotorGetTorqueLimit(&motor->interface);
}

void Motor_SetTorqueLimit(Motor_t *motor, float torqueLimit) {
	motor->interface.MotorSetTorqueLimit(&motor->interface, torqueLimit);
}

float Motor_GetMeasuredTorque(Motor_t *motor) {
	return motor->interface.MotorGetTorqueReading(&motor->interface);
}

void Motor_SetTorque(Motor_t *motor, float torque) {
	motor->mode = MOTOR_CONTROL_CURRENT;
	motor->interface.MotorSetTorque(&motor->interface, torque);
}

void Motor_InitVelocityEncoder(Motor_t *motor, Encoder_t *encoder) {
	motor->encoder = encoder;
	VelocityControl_Init(&motor->velControl, EncoderCountToRad(encoder),
			0);
}

void Motor_SetVelocityFilterAlpha(Motor_t *motor, float alpha) {
	VelocityControl_SetFilterAlpha(&motor->velControl, alpha);
}

void Motor_SetVelocityLoopFreqDivider(Motor_t *motor, int freqDivider) {
	motor->velocityLoopFreqDivider = freqDivider;
}

void Motor_SetVelocity(Motor_t *motor, float velocity) {
	if(motor->encoder != NULL) {
		if(motor->mode != MOTOR_CONTROL_VELOCITY) {
			// Reset velocity PID only if current control mode is not velocity
			PID_Reset(VelocityControl_GetVelocityPID(&motor->velControl));
			motor->mode = MOTOR_CONTROL_VELOCITY;
		}

		VelocityControl_SetVelocityTarget(&motor->velControl,
				RPMToRadPerSec(velocity));
	}
	else {
		// Encoder has not been set, turn motor off
		Motor_SetVoltage(motor, 0.0f);
	}
}

float Motor_GetVelocity(Motor_t *motor) {
	return motor->velocityRpm;
}

PID_t *Motor_GetVelocityPID(Motor_t *motor) {
	return VelocityControl_GetVelocityPID(&motor->velControl);
}

void Motor_Update(Motor_t *motor, float deltaTimeMs) {

	if(motor->encoder != NULL) {
		motor->velocityLoopCount++;
		if(motor->velocityLoopCount >= motor->velocityLoopFreqDivider) {

			// Convert from milliseconds to seconds and scale based on frequency
			// divider
			float velocityDeltaTime = (deltaTimeMs/1000.0f) *
					motor->velocityLoopFreqDivider;

			VelocityControl_UpdateVelocity(&motor->velControl,
					EncoderCountToRad(motor->encoder),
					velocityDeltaTime);
			motor->velocityRpm =
					RadPerSecToRPM(VelocityControl_GetVelocity(
							&motor->velControl));

			if(motor->mode == MOTOR_CONTROL_VELOCITY) {
				float torque = VelocityControl_CalcTorque(&motor->velControl,
						velocityDeltaTime);
				motor->interface.MotorSetTorque(&motor->interface, torque);
			}

			motor->velocityLoopCount = 0;
		}
	}


	motor->interface.MotorUpdate(&motor->interface, deltaTimeMs);

	// Check if the motor has a current sensor
//	if(Motor_GetNumCurrentSensors(motor) > 0) {
//		if(Motor_GetMeasuredTotalCurrent(motor) > Motor_GetCurrentLimit(motor)
//				&& !motor->currentLimitTripped) {
//			motor->currentLimitTripped = true;
//			motor->currentLimitTripCount++;
//			// TODO: Add current limit tripped callback
//		}
//	}
}

static float EncoderCountToRad(Encoder_t *encoder) {
	return (Encoder_GetCount(encoder) * 2.0f * ((float)M_PI)) /
			Encoder_GetCountPerRev(encoder);
}

static float RadPerSecToRPM(float radPerSec) {
	return (radPerSec/(2.0f * ((float)M_PI))) * 60.0f;
}

static float RPMToRadPerSec(float rpm) {
	return (rpm/60.0f) * (2.0f * ((float)M_PI));
}
