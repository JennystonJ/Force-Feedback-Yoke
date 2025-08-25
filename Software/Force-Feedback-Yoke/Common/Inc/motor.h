/*
 * motor.h
 *
 *  Created on: Mar 18, 2024
 *      Author: Jennyston
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "pid.h"
#include <stdint.h>
#include <stdbool.h>
#include "anti_cog.h"
#include "encoder.h"
#include "velocity_control.h"

typedef enum {
	MOTOR_CONTROL_VOLTAGE,
	MOTOR_CONTROL_CURRENT,
	MOTOR_CONTROL_VELOCITY,
	MOTOR_CONTROL_CURRENT_CAL
} MotorControlMode_e;

typedef struct MotorInterface MotorInterface_t;

struct MotorInterface {
	void *hardwareMotor;
	void (*MotorSetEnable)(MotorInterface_t *interface, bool enabled);
	float (*MotorGetBusVoltage)(MotorInterface_t *interface);
	float (*MotorGetVoltage)(MotorInterface_t *interface);
	void (*MotorSetVoltage)(MotorInterface_t *interface, float voltage);
	float (*MotorGetCurrentLimit)(MotorInterface_t *interface);
	void (*MotorSetCurrentLimit)(MotorInterface_t *interface,
			float currentLimit);
	float (*MotorGetCurrent)(MotorInterface_t *interface);
	void (*MotorSetCurrent)(MotorInterface_t *interface, float current);
	float (*MotorGetTorqueLimit)(MotorInterface_t *interface);
	void (*MotorSetTorqueLimit)(MotorInterface_t *interface, float torqueLimit);
	float (*MotorGetTorque)(MotorInterface_t *interface);
	void (*MotorSetTorque)(MotorInterface_t *interface, float torque);
	float (*MotorGetTorqueReading)(MotorInterface_t *interface);
	int (*MotorGetNumCurrentSensors)(MotorInterface_t *interface);
	float (*MotorGetCurrentReading)(MotorInterface_t *interface,
			int sensorIndex);
	float (*MotorGetTotalCurrentReading)(MotorInterface_t * interface);
	void (*MotorUpdate)(MotorInterface_t *interface, float deltaTimeMs);
};

typedef struct Motor {
	MotorInterface_t interface;
	Encoder_t *encoder;

	VelocityControl_t velControl;
	float velocityRpm;
	int velocityLoopFreqDivider;
	int velocityLoopCount;

	bool currentLimitTripped;
	int currentLimitTripCount;

	MotorControlMode_e mode;
} Motor_t;

void Motor_Init(Motor_t *motor, MotorInterface_t interface);

void Motor_SetEnable(Motor_t *motor, bool enabled);

float Motor_GetBusVoltage(Motor_t *motor);
float Motor_GetVoltage(Motor_t *motor);
void Motor_SetVoltage(Motor_t *motor, float voltage);

float Motor_GetCurrent(Motor_t *motor);
int Motor_GetNumCurrentSensors(Motor_t *motor);
float Motor_GetMeasuredCurrent(Motor_t *motor, int index);
float Motor_GetMeasuredTotalCurrent(Motor_t *motor);
void Motor_SetCurrent(Motor_t *motor, float current);

float Motor_GetCurrentLimit(Motor_t *motor);
void Motor_SetCurrentLimit(Motor_t *motor, float currentLimit);

float Motor_GetTorqueLimit(Motor_t *motor);
void Motor_SetTorqueLimit(Motor_t *motor, float torqueLimit);

float Motor_GetTorque(Motor_t *motor);
float Motor_GetMeasuredTorque(Motor_t *motor);
void Motor_SetTorque(Motor_t *motor, float torque);

void Motor_InitVelocityEncoder(Motor_t *motor, Encoder_t *encoder);
void Motor_SetVelocityLoopFreqDivider(Motor_t *motor, int freqDivider);
void Motor_SetVelocityFilterAlpha(Motor_t *motor, float alpha);
void Motor_SetVelocity(Motor_t *motor, float velocity);
float Motor_GetVelocity(Motor_t *motor);
PID_t *Motor_GetVelocityPID(Motor_t *motor);

void Motor_Update(Motor_t *motor, float deltaTimeMs);


#ifdef __cplusplus
}
#endif

#endif /* INC_MOTOR_H_ */
