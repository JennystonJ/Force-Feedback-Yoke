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

void MotorInit(Motor_t *motor, MotorInterface_t interface) {
	motor->interface = interface;
	motor->currentSensor = NULL;
	motor->antiCog = NULL;
	motor->mode = MOTOR_CONTROL_POWER;

	motor->currentLimit = 150;
	motor->currentLimitTripCount = 0;
	PIDInit(&motor->pidCurrent);
	PIDSetKP(&motor->pidCurrent, 140);
	PIDSetKI(&motor->pidCurrent, 15);
	PIDSetKD(&motor->pidCurrent, 0);
	PIDSetIntegralLimit(&motor->pidCurrent, 100);

	motor->preCalPower = 0;
}

void MotorSetCurrentSensor(Motor_t *motor, CurrentSensor_t *currentSensor) {
	motor->currentSensor = currentSensor;
}

void MotorSetAntiCog(Motor_t *motor, AntiCog_t *antiCog) {
	motor->antiCog = antiCog;
}

int MotorGetPower(Motor_t *motor) {
	return motor->interface.MotorGetPower(&motor->interface);
}

void MotorSetPower(Motor_t *motor, int power) {
	motor->mode = MOTOR_CONTROL_POWER;
	motor->interface.MotorSetPower(&motor->interface, power/2);
}

float MotorGetCurrent(Motor_t *motor) {
	return motor->setPointCurrent;
}

float MotorGetMeasuredCurrent(Motor_t *motor) {
	return CurrentSensorGetValue(motor->currentSensor);
}

void MotorSetCurrent(Motor_t *motor, float current) {
	motor->mode = MOTOR_CONTROL_CURRENT;
	motor->currentLimiting = fabsf(current) > motor->currentLimit;
	motor->setPointCurrent = ConstrainFloat(current,
			-motor->currentLimit, motor->currentLimit);
}

void MotorCurrentUpdate(Motor_t *motor, int deltaTimeUs) {

	if(motor->currentSensor == NULL) {
		// Current sensor has not been set
		return;
	}

	if(motor->mode == MOTOR_CONTROL_POWER ||
			motor->mode == MOTOR_CONTROL_CURRENT_CAL) {
		// Wrong mode
		return;
	}

	if(MotorGetMeasuredCurrent(motor) > motor->currentLimit * 1.5f) {
		motor->currentLimitTripCount++;
	}

	motor->compensatedSetPointCurrent = motor->setPointCurrent +
			(motor->antiCog == NULL) ? 0.0f : AntiCogCalc(motor->antiCog);

	float output = CalcPID(&motor->pidCurrent,
			motor->compensatedSetPointCurrent,
			MotorGetMeasuredCurrent(motor), deltaTimeUs/1000.0f);
	int motorPower = Constrain((int32_t)output, -MOTOR_POWER_MAX/2,
			MOTOR_POWER_MAX/2);
	motor->interface.MotorSetPower(&motor->interface, motorPower);
}

PID_t *MotorGetPIDCurrent(Motor_t *motor) {
	return &motor->pidCurrent;
}

void MotorCurrentCalibrate(Motor_t *motor) {
	motor->preCalPower = motor->interface.MotorGetPower(&motor->interface);
	motor->interface.MotorSetPower(&motor->interface, 0);
	motor->mode = MOTOR_CONTROL_CURRENT_CAL;
	CurrentSensorStartCalibration(motor->currentSensor);
}

void MotorCurrentCalibrationUpdate(Motor_t *motor) {
	if(motor->mode == MOTOR_CONTROL_CURRENT_CAL &&
			!CurrentSensorIsCalibrating(motor->currentSensor)) {
		motor->mode = MOTOR_CONTROL_CURRENT;
		motor->interface.MotorSetPower(&motor->interface, motor->preCalPower);
	}
}
