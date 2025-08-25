/*
 * bldc_motor_interface.c
 *
 *  Created on: Jul 10, 2025
 *      Author: Jennyston
 */

#include "bldc_motor_interface.h"

static void MotorSetEnable(MotorInterface_t *interface, bool enabled);
static float MotorGetBusVoltage(MotorInterface_t *interface);
static float MotorGetVoltage(MotorInterface_t *interface);
static void MotorSetVoltage(MotorInterface_t *interface, float voltage);
static float MotorGetCurrentLimit(MotorInterface_t *interface);
static void MotorSetCurrentLimit(MotorInterface_t *interface,
		float currentLimit);
static float MotorGetCurrent(MotorInterface_t *interface);
static void MotorSetCurrent(MotorInterface_t *interface, float current);
static float MotorGetTorque(MotorInterface_t *interface);
static void MotorSetTorque(MotorInterface_t *interface, float torque);
static float MotorGetTorqueLimit(MotorInterface_t *interface);
static void MotorSetTorqueLimit(MotorInterface_t *interface, float torque);
static int MotorGetNumCurrentSensors(MotorInterface_t *interface);
static float MotorGetCurrentReading(MotorInterface_t *interface,
		int sensorIndex);
static float MotorGetTorqueReading(MotorInterface_t *interface);
static float MotorGetTotalCurrentReading(MotorInterface_t * interface);
static void MotorUpdate(MotorInterface_t *interface, float deltaTimeMs);


void BLDCMotorInterface_Init(MotorInterface_t *interface, BLDCMotor_t *motor) {
	interface->hardwareMotor = motor;

	interface->MotorSetEnable = &MotorSetEnable;
	interface->MotorGetBusVoltage = &MotorGetBusVoltage;
	interface->MotorGetVoltage = &MotorGetVoltage;
	interface->MotorSetVoltage = &MotorSetVoltage;
	interface->MotorGetCurrentLimit = &MotorGetCurrentLimit;
	interface->MotorSetCurrentLimit = &MotorSetCurrentLimit;
	interface->MotorGetCurrent = &MotorGetCurrent;
	interface->MotorSetCurrent = &MotorSetCurrent;
	interface->MotorGetTorque = &MotorGetTorque;
	interface->MotorSetTorque = &MotorSetTorque;
	interface->MotorGetTorqueLimit = &MotorGetTorqueLimit;
	interface->MotorSetTorqueLimit = &MotorSetTorqueLimit;
	interface->MotorGetNumCurrentSensors = &MotorGetNumCurrentSensors;
	interface->MotorGetCurrentReading = &MotorGetCurrentReading;
	interface->MotorGetTorqueReading = &MotorGetTorqueReading;
	interface->MotorGetTotalCurrentReading = &MotorGetTotalCurrentReading;
	interface->MotorUpdate = &MotorUpdate;
}

static void MotorSetEnable(MotorInterface_t *interface, bool enabled) {
	BLDCMotor_SetEnable((BLDCMotor_t *)interface->hardwareMotor, enabled);
}

static float MotorGetBusVoltage(MotorInterface_t *interface) {
	return BLDCMotor_GetBusVoltage((BLDCMotor_t *)interface->hardwareMotor);
}

static float MotorGetVoltage(MotorInterface_t *interface) {
	return BLDCMotor_GetVoltage((BLDCMotor_t *)interface->hardwareMotor);
}

static void MotorSetVoltage(MotorInterface_t *interface, float voltage) {
	BLDCMotor_SetVoltage((BLDCMotor_t *)interface->hardwareMotor, voltage);
}

static float MotorGetCurrentLimit(MotorInterface_t *interface) {
	return BLDCMotor_GetQCurrentLimit((BLDCMotor_t *)interface->hardwareMotor);
}

static void MotorSetCurrentLimit(MotorInterface_t *interface,
		float currentLimit) {
	BLDCMotor_SetQCurrentLimit((BLDCMotor_t *)interface->hardwareMotor,
			currentLimit);
}

static float MotorGetCurrent(MotorInterface_t *interface) {
	return BLDCMotor_GetQCurrent((BLDCMotor_t *)interface->hardwareMotor);
}

static void MotorSetCurrent(MotorInterface_t *interface, float current) {
	BLDCMotor_SetQCurrent((BLDCMotor_t *)interface->hardwareMotor, current);
}

static float MotorGetTorque(MotorInterface_t *interface) {
	return BLDCMotor_GetTorque((BLDCMotor_t *)interface->hardwareMotor);
}

static void MotorSetTorque(MotorInterface_t *interface, float torque) {
	BLDCMotor_SetTorque((BLDCMotor_t *)interface->hardwareMotor, torque);
}

static float MotorGetTorqueLimit(MotorInterface_t *interface) {
	return BLDCMotor_GetTorqueLimit((BLDCMotor_t *)interface->hardwareMotor);
}

static void MotorSetTorqueLimit(MotorInterface_t *interface, float torque) {
	BLDCMotor_SetTorqueLimit((BLDCMotor_t *)interface->hardwareMotor, torque);
}

static int MotorGetNumCurrentSensors(MotorInterface_t *interface) {
	return BLDCMotor_GetNumCurrentSensors(
			(BLDCMotor_t *)interface->hardwareMotor);
}

static float MotorGetCurrentReading(MotorInterface_t *interface,
		int sensorIndex) {
	switch(sensorIndex) {
		case 0:
			return BLDCMotor_GetDCurrentReading(
					(BLDCMotor_t *)interface->hardwareMotor);
			break;
		case 1:
			return BLDCMotor_GetQCurrentReading(
					(BLDCMotor_t *)interface->hardwareMotor);
		default:
			// Invalid index
			return 0.0f;
			break;
	}
}

static float MotorGetTorqueReading(MotorInterface_t *interface) {
	return BLDCMotor_GetTorqueReading(interface->hardwareMotor);
}

static float MotorGetTotalCurrentReading(MotorInterface_t * interface) {
	return BLDCMotor_GetTotalCurrentReading(
			(BLDCMotor_t *)interface->hardwareMotor);
}

static void MotorUpdate(MotorInterface_t *interface, float deltaTimeMs) {
	BLDCMotor_Update((BLDCMotor_t *)interface->hardwareMotor, deltaTimeMs);
}
