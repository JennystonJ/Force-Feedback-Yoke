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
#include "current_sensor.h"
#include <stdint.h>
#include <stdbool.h>
#include "anti_cog.h"

#define MOTOR_POWER_MAX (4800-1)

typedef enum {
	MOTOR_CONTROL_POWER,
	MOTOR_CONTROL_CURRENT,
	MOTOR_CONTROL_CURRENT_CAL
} MotorControlMode_e;

typedef struct MotorInterface MotorInterface_t;

struct MotorInterface {
	void *hardwareMotor;
	int (*MotorGetPower)(MotorInterface_t *motor);
	void (*MotorSetPower)(MotorInterface_t *motor, int power);
};

typedef struct Motor {
	MotorInterface_t interface;
	CurrentSensor_t *currentSensor;
	AntiCog_t *antiCog;
	MotorControlMode_e mode;

	float currentLimit;
	bool currentLimiting;
	int currentLimitTripCount;

	float setPointCurrent;
	float compensatedSetPointCurrent;
	PID_t pidCurrent;

	int preCalPower;
} Motor_t;

void MotorInit(Motor_t *motor, MotorInterface_t interface);
void MotorSetCurrentSensor(Motor_t *motor, CurrentSensor_t *currentSensor);
void MotorSetAntiCog(Motor_t *motor, AntiCog_t *antiCog);
int MotorGetPower(Motor_t *motor);
void MotorSetPower(Motor_t *motor, int power);

float MotorGetCurrent(Motor_t *motor);
float MotorGetMeasuredCurrent(Motor_t *motor);
void MotorSetCurrent(Motor_t *motor, float current);
void MotorCurrentUpdate(Motor_t *motor, int dt);
PID_t *MotorGetPIDCurrent(Motor_t *motor);

void MotorCurrentCalibrate(Motor_t *motor);
void MotorCurrentCalibrationUpdate(Motor_t *motor);

#ifdef __cplusplus
}
#endif

#endif /* INC_MOTOR_H_ */
