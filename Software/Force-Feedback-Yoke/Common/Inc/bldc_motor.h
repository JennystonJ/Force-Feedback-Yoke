/*
 * bldc.h
 *
 *  Created on: Jul 9, 2025
 *      Author: Jennyston
 */

#ifndef INC_BLDC_MOTOR_H_
#define INC_BLDC_MOTOR_H_

#include "bldc_driver.h"
#include "bldc_foc.h"
#include "encoder.h"
#include "current_sensor.h"

#include <stdbool.h>

typedef enum {
	BLDC_MOTOR_MODE_VOLTAGE,
	BLDC_MOTOR_MODE_CURRENT,
	BLDC_MOTOR_MODE_ENCODER_CAL
} BLDCMotorControlMode_e;

typedef struct BLDCMotor {
	BLDCDriver_t *driver;

	BLDCMotorControlMode_e mode;

	Encoder_t *encoder;
	int electricalAngleOffsetCount;
	int electricalAngleCount;
	float electricalAngle;

	CurrentSensor_t *currentA;
	CurrentSensor_t *currentB;
	CurrentSensor_t *currentC;

	PhaseCurrents_t phaseCurrents;

	float kt;
	float qCurrentLimit;
	int polePairs;

	float voltage;

	bool eStop;

	FOC_t foc;
} BLDCMotor_t;

void BLDCMotor_Init(BLDCMotor_t *motor, BLDCDriver_t *driver,
		Encoder_t *encoder, int polePairs);
void BLDCMotor_SetCurrentSensors(BLDCMotor_t *motor, CurrentSensor_t *currentA,
		CurrentSensor_t *currentB, CurrentSensor_t *currentC);

void BLDCMotor_SetEnable(BLDCMotor_t *motor, bool enabled);
void BLDCMotor_SetEStop(BLDCMotor_t *motor, bool eStop);

void BLDCMotor_SetTorqueConstant(BLDCMotor_t *motor, float kt);

void BLDCMotor_SetElectricalAngleOffsetCount(BLDCMotor_t *motor, int offset);
int BLDCMotor_GetElectricalAngleOffsetCount(BLDCMotor_t *motor);

float BLDCMotor_GetBusVoltage(BLDCMotor_t *motor);
void BLDCMotor_SetVoltage(BLDCMotor_t *motor, float voltage);
float BLDCMotor_GetVoltage(BLDCMotor_t *motor);

void BLDCMotor_SetDCurrent(BLDCMotor_t *motor, float currentLimit);
float BLDCMotor_GetDCurrent(BLDCMotor_t *motor);

void BLDCMotor_SetQCurrentLimit(BLDCMotor_t *motor, float current);
float BLDCMotor_GetQCurrentLimit(BLDCMotor_t *motor);

void BLDCMotor_SetQCurrent(BLDCMotor_t *motor, float current);
float BLDCMotor_GetQCurrent(BLDCMotor_t *motor);

void BLDCMotor_SetTorque(BLDCMotor_t *motor, float torque);
float BLDCMotor_GetTorque(BLDCMotor_t *motor);

void BLDCMotor_SetTorqueLimit(BLDCMotor_t *motor, float torqueLimit);
float BLDCMotor_GetTorqueLimit(BLDCMotor_t *motor);

float BLDCMotor_GetTorqueReading(BLDCMotor_t *motor);
float BLDCMotor_GetDCurrentReading(BLDCMotor_t *motor);
float BLDCMotor_GetQCurrentReading(BLDCMotor_t *motor);

int BLDCMotor_GetNumCurrentSensors(BLDCMotor_t *motor);
float BLDCMotor_GetTotalCurrentReading(BLDCMotor_t *motor);

FOC_t *BLDCMotor_GetFOC(BLDCMotor_t *motor);

void BLDCMotor_RunEncoderCalibration(BLDCMotor_t *motor,
		float phaseHoldCurrrent);
void BLDCMotor_RunCurrentSensorCalibration(BLDCMotor_t *motor,
		unsigned int numSamples);

void BLDCMotor_Update(BLDCMotor_t *motor, float deltaTimeMs);

#endif /* INC_BLDC_MOTOR_H_ */
