/*
 * bldc.c
 *
 *  Created on: Jul 9, 2025
 *      Author: Jennyston
 */

#include "bldc_motor.h"
#include <stddef.h>
#include <math.h>
#include "bldc_foc_math.h"
#include "utilities/utilities.h"
#include "delay.h"
#include "diagnostics/diagnostics.h"
#include <string.h>

static int CalcElectricalAngleRawCount(BLDCMotor_t *motor);
static int CalcElectricalAngleCount(BLDCMotor_t *motor);
static float CalcElectricalAngle(BLDCMotor_t *motor);
static inline void UpdateCurrentSenseReadings(BLDCMotor_t *motor, float deltaTimeMs);

void BLDCMotor_Init(BLDCMotor_t *motor, BLDCDriver_t *driver,
		Encoder_t *encoder, int polePairs) {
	motor->driver = driver;
	motor->encoder = encoder;
	motor->electricalAngleOffsetCount = 0;
	motor->electricalAngleCount = 0;
	motor->electricalAngle = 0.0f;

	motor->currentSensingEnabled = false;
	motor->currentA = NULL;
	motor->currentB = NULL;
	motor->currentC = NULL;
	motor->currentSenseCalSampleTarget = 10;

	motor->kt = 0.0f;
	motor->qCurrentLimit = 0.5f;
	motor->polePairs = polePairs;
	motor->mode = BLDC_MOTOR_MODE_VOLTAGE;

	motor->eStop = false;
	motor->voltage = 0.0f;

	FOC_Init(&motor->foc, BLDCDriver_GetBusVoltage(driver));

	motor->diagInit = false;

	memset(&motor->diagConfig, 0, sizeof(motor->diagConfig));
}

void BLDCMotor_SetDiagnostics(BLDCMotor_t *motor,
		MotorDiagnosticsConfig_t config) {
	motor->diagConfig = config;
	motor->diagInit = true;
}

void BLDCMotor_SetCurrentSensors(BLDCMotor_t *motor, CurrentSensor_t *currentA,
		CurrentSensor_t *currentB, CurrentSensor_t *currentC) {
	motor->currentA = currentA;
	motor->currentB = currentB;
	motor->currentC = currentC;
	motor->currentSensingEnabled = !(motor->currentA == NULL ||
			motor->currentB == NULL ||
			motor->currentC == NULL);
}

void BLDCMotor_SetEnable(BLDCMotor_t *motor, bool enabled) {
	BLDCDriver_SetEnable(motor->driver, enabled & !motor->eStop);
}

void BLDCMotor_SetEStop(BLDCMotor_t *motor, bool eStop) {
	motor->eStop = eStop;

	BLDCDriver_SetEnable(motor->driver, eStop);
	BLDCMotor_SetVoltage(motor, 0.0f);

}

void BLDCMotor_SetTorqueConstant(BLDCMotor_t *motor, float kt) {
	motor->kt = kt;
}

void BLDCMotor_SetElectricalAngleOffsetCount(BLDCMotor_t *motor, int offset) {
	motor->electricalAngleOffsetCount = offset;
}

int BLDCMotor_GetElectricalAngleOffsetCount(BLDCMotor_t *motor) {
	return motor->electricalAngleOffsetCount;
}

float BLDCMotor_GetBusVoltage(BLDCMotor_t *motor) {
	return BLDCDriver_GetBusVoltage(motor->driver);
}

void BLDCMotor_SetVoltage(BLDCMotor_t *motor, float voltage) {
	motor->mode = BLDC_MOTOR_MODE_VOLTAGE;
	motor->voltage = voltage;
}

float BLDCMotor_GetVoltage(BLDCMotor_t *motor) {
	return motor->voltage;
}

void BLDCMotor_SetDCurrent(BLDCMotor_t *motor, float current) {
	motor->mode = BLDC_MOTOR_MODE_CURRENT;
	FOC_SetIDSetPoint(&motor->foc, current);
}

float BLDCMotor_GetDCurrent(BLDCMotor_t *motor) {
	return FOC_GetIDSetPoint(&motor->foc);
}

void BLDCMotor_SetQCurrentLimit(BLDCMotor_t *motor, float currentLimit) {
	motor->qCurrentLimit = currentLimit;
}

float BLDCMotor_GetQCurrentLimit(BLDCMotor_t *motor) {
	return motor->qCurrentLimit;
}

void BLDCMotor_SetQCurrent(BLDCMotor_t *motor, float current) {
	if(motor->currentSensingEnabled && !BLDCMotor_IsCurrentSensorCalibrating(motor)) {
		motor->mode = BLDC_MOTOR_MODE_CURRENT;

		FOC_SetIQSetPoint(&motor->foc,
				ConstrainFloat(current, -motor->qCurrentLimit,
						motor->qCurrentLimit));
	}
	else {
		// Current sensors have not been assigned or are calibrating,
		// set voltages to 0
		BLDCMotor_SetVoltage(motor, 0);
	}
}

float BLDCMotor_GetQCurrent(BLDCMotor_t *motor) {
	return FOC_GetIQSetPoint(&motor->foc);
}

int BLDCMotor_GetNumCurrentSensors(BLDCMotor_t *motor) {
	return motor->currentA == NULL ? 0 : 2;
}

void BLDCMotor_SetTorque(BLDCMotor_t *motor, float torque) {
	if(motor->kt > 0.0f) {
		BLDCMotor_SetQCurrent(motor, torque/motor->kt);
	}
	else {
		// Torque constant has not been set or is invalid
		BLDCMotor_SetQCurrent(motor, 0.0f);
	}
}

float BLDCMotor_GetTorque(BLDCMotor_t *motor) {
	return FOC_GetIQSetPoint(&motor->foc) * motor->kt;
}

float BLDCMotor_GetTorqueReading(BLDCMotor_t *motor) {
	return BLDCMotor_GetQCurrentReading(motor) * motor->kt;
}

void BLDCMotor_SetTorqueLimit(BLDCMotor_t *motor, float torqueLimit) {
	motor->qCurrentLimit = torqueLimit/motor->kt;
}

float BLDCMotor_GetTorqueLimit(BLDCMotor_t *motor) {
	return motor->qCurrentLimit/motor->kt;
}

float BLDCMotor_GetDCurrentReading(BLDCMotor_t *motor){
	return FOC_GetDQCurrent(&motor->foc).d;
}

float BLDCMotor_GetQCurrentReading(BLDCMotor_t *motor) {
	return FOC_GetDQCurrent(&motor->foc).q;
}

float BLDCMotor_GetTotalCurrentReading(BLDCMotor_t *motor) {
	float d_2 = BLDCMotor_GetDCurrentReading(motor) *
			BLDCMotor_GetDCurrentReading(motor);
	float q_2 = BLDCMotor_GetQCurrentReading(motor) *
			BLDCMotor_GetQCurrentReading(motor);
	return sqrtf(d_2 + q_2);
}

FOC_t *BLDCMotor_GetFOC(BLDCMotor_t *motor) {
	return &motor->foc;
}

void BLDCMotor_RunCurrentSensorCalibration(BLDCMotor_t *motor) {
	BLDCMotor_SetVoltage(motor, 0.0f);
	BLDCMotor_SetEnable(motor, true);

	delayMs(500);

	CurrentSensor_StartCalibration(motor->currentA,
			motor->currentSenseCalSampleTarget);
	CurrentSensor_StartCalibration(motor->currentB,
			motor->currentSenseCalSampleTarget);
	CurrentSensor_StartCalibration(motor->currentC,
			motor->currentSenseCalSampleTarget);
}

void BLDCMotor_SetCurrentSensorCalibrationSampleTarget(BLDCMotor_t *motor,
		unsigned int targetSamples) {
	motor->currentSenseCalSampleTarget = targetSamples;
}

void BLDCMotor_RunEncoderCalibration(BLDCMotor_t *motor,
		float phaseHoldCurrent) {
	motor->mode = BLDC_MOTOR_MODE_ENCODER_CAL;

//	PhaseVoltages_t phaseVoltages = {
//			.a = phaseHoldVoltage * cosf(0),
//			.b = phaseHoldVoltage * cosf(-2.0f*((float)M_PI)/3.0f),
//			.c = phaseHoldVoltage * cosf(2.0f*((float)M_PI)/3.0f)
//	};

	BLDCDriver_SetEnable(motor->driver, true);

	FOC_SetIQSetPoint(&motor->foc, 0.0f);
	FOC_SetIDSetPoint(&motor->foc, phaseHoldCurrent);

	delayMs(2500);
	motor->electricalAngleOffsetCount = -CalcElectricalAngleRawCount(motor);

	FOC_SetIDSetPoint(&motor->foc, 0.0f);
	BLDCDriver_SetVoltages(motor->driver, 0, 0, 0);
}

void BLDCMotor_Update(BLDCMotor_t *motor, float deltaTimeMs) {

	// Check if current sensors have been assigned
	if(motor->currentSensingEnabled) {
		UpdateCurrentSenseReadings(motor, deltaTimeMs);
	}

	motor->electricalAngleCount = CalcElectricalAngleCount(motor);
	motor->electricalAngle = CalcElectricalAngle(motor);

	switch(motor->mode) {
		case BLDC_MOTOR_MODE_CURRENT:
		{
			PhaseVoltages_t phaseVoltages =
					FOC_Calc(&motor->foc, motor->phaseCurrents,
								motor->electricalAngle,
								deltaTimeMs);
			BLDCDriver_SetVoltages(motor->driver, phaseVoltages.a, phaseVoltages.b,
					phaseVoltages.c);
			break;
		}
		case BLDC_MOTOR_MODE_VOLTAGE:
		{
			// Calculate phase voltages
			PhaseVoltages_t phaseVoltages = FOCMath_CalcPhaseVoltages(0.0f,
					motor->voltage/2.0f,
					motor->electricalAngle);

			// Assign phase voltages
			BLDCDriver_SetVoltages(motor->driver, phaseVoltages.a,
						phaseVoltages.b, phaseVoltages.c);
			break;
		}
		case BLDC_MOTOR_MODE_ENCODER_CAL:
		{
			PhaseVoltages_t phaseVoltages =
					FOC_Calc(&motor->foc, motor->phaseCurrents,
							0.0f,
							deltaTimeMs);
			BLDCDriver_SetVoltages(motor->driver, phaseVoltages.a, phaseVoltages.b,
					phaseVoltages.c);
			break;
		}
		default:
			FOC_ResetPID(&motor->foc);
			// Do Nothing
			break;
	}
}


bool BLDCMotor_IsCurrentSensorCalibrating(BLDCMotor_t *motor) {
	return !(CurrentSensor_IsCalibrationDone(motor->currentA) &&
			CurrentSensor_IsCalibrationDone(motor->currentB) &&
			CurrentSensor_IsCalibrationDone(motor->currentC));
}

static int CalcElectricalAngleRawCount(BLDCMotor_t *motor) {
	int countsPerElecRev = Encoder_GetCountPerRev(motor->encoder) /
			motor->polePairs;

	int raw = Encoder_GetHardCount(motor->encoder);
	int elecCount = ((raw % countsPerElecRev) + countsPerElecRev) %
			countsPerElecRev;

	return elecCount;
}

static int CalcElectricalAngleCount(BLDCMotor_t *motor) {
	int countsPerElecRev = Encoder_GetCountPerRev(motor->encoder) /
			motor->polePairs;

	int raw = Encoder_GetHardCount(motor->encoder) +
			motor->electricalAngleOffsetCount;
	int elecCount = ((raw % countsPerElecRev) + countsPerElecRev) %
			countsPerElecRev;

	return elecCount;
}

static float CalcElectricalAngle(BLDCMotor_t *motor) {
	int countsPerElecRev = Encoder_GetCountPerRev(motor->encoder) /
			motor->polePairs;
	float elecAngle = (2.0f*(float)M_PI) *
					(CalcElectricalAngleCount(motor) / (float)countsPerElecRev);
	return elecAngle;
}


static inline void UpdateCurrentSenseReadings(BLDCMotor_t *motor, float deltaTimeMs) {
	// Update sensors
	CurrentSensor_Update(motor->currentA, deltaTimeMs);
	CurrentSensor_Update(motor->currentB, deltaTimeMs);
	CurrentSensor_Update(motor->currentC, deltaTimeMs);

	// Get phase currents
	motor->phaseCurrents.a = CurrentSensor_GetValue(motor->currentA);
	motor->phaseCurrents.b = CurrentSensor_GetValue(motor->currentB);
	motor->phaseCurrents.c = CurrentSensor_GetValue(motor->currentC);

	if(motor->diagInit) {
		PhaseCurrents_t *phaseCurrents = &motor->phaseCurrents;
		float overcurrentReportLimit = motor->diagConfig.overcurrentReportLimit;
		if(fabsf(phaseCurrents->a) > overcurrentReportLimit ||
				fabsf(phaseCurrents->b) > overcurrentReportLimit ||
				fabsf(phaseCurrents->c > overcurrentReportLimit)) {
			Diagnostics_SetMotorFault(FAULT_MOTOR_OVERCURRENT,
					motor->diagConfig.id);
		}
		else {
			Diagnostics_ResetMotorFault(FAULT_MOTOR_OVERCURRENT,
					motor->diagConfig.id);
		}
	}
}
