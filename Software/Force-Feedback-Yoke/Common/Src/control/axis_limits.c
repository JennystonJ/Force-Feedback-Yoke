/*
 * axis_limits.c
 *
 *  Created on: Jun 1, 2026
 *      Author: Jennyston
 */

#include "control/axis_limits.h"
#include "utilities/utilities.h"
#include <math.h>

static float AxisLimits_ApplyStopper(AxisLimits_t *axisLimits,
		const AxisKinematics_t *kinematics, float desiredTorque);

void AxisLimits_Init(AxisLimits_t *axisLimits, AxisLimitSet_t safety,
		AxisLimitSet_t operating) {
	axisLimits->safety = safety;
	axisLimits->operating = operating;

	axisLimits->stopperEnable = true;
	axisLimits->stopperActive = false;
	axisLimits->stopperSpring = 0.0f;
	axisLimits->stopperDamper = 0.0f;
}

void AxisLimits_SetSafetyPositionRange(AxisLimits_t *axisLimits,
		AxisRange_t positionRange) {
	axisLimits->safety.positionRange = positionRange;

	// Update operating position limits if needed
	axisLimits->operating.positionRange.min =
			fmaxf(axisLimits->operating.positionRange.min,
			axisLimits->safety.positionRange.min);
	axisLimits->operating.positionRange.max =
			fminf(axisLimits->operating.positionRange.max,
			axisLimits->safety.positionRange.max);
}


AxisRange_t AxisLimits_GetSafetyPositionRange(const AxisLimits_t *axisLimits) {
	return axisLimits->safety.positionRange;
}

void AxisLimits_SetSafetyMaxTorque(AxisLimits_t *axisLimits, float maxTorque) {
	axisLimits->safety.maxTorque = maxTorque;

	// Update operating torque limit if needed
	axisLimits->operating.maxTorque = fminf(axisLimits->operating.maxTorque,
				axisLimits->safety.maxTorque);
}

float AxisLimits_GetSafetyMaxTorque(const AxisLimits_t *axisLimits) {
	return axisLimits->safety.maxTorque;
}

void AxisLimits_SetOperatingPositionRange(AxisLimits_t *axisLimits,
		AxisRange_t positionRange) {

	// Clamp and assign operating position range
	axisLimits->operating.positionRange.min =
			fmaxf(positionRange.min, axisLimits->safety.positionRange.min);
	axisLimits->operating.positionRange.max =
			fminf(positionRange.max, axisLimits->safety.positionRange.max);
}

AxisRange_t AxisLimits_GetOperatingPositionRange(const AxisLimits_t *axisLimits) {
	return axisLimits->operating.positionRange;
}

void AxisLimits_SetOperatingMaxTorque(AxisLimits_t *axisLimits, float maxTorque) {
	axisLimits->operating.maxTorque = fminf(maxTorque,
			axisLimits->safety.maxTorque);
}

float AxisLimits_GetOperatingMaxTorque(const AxisLimits_t *axisLimits) {
	return axisLimits->operating.maxTorque;
}

void AxisLimits_SetStopperEnable(AxisLimits_t *axisLimits, bool enabled) {
	axisLimits->stopperEnable = enabled;
}

void AxisLimits_SetStopperSpringGain(AxisLimits_t *axisLimits, float k) {
	axisLimits->stopperSpring = k;
}

void AxisLimits_SetStopperDamperGain(AxisLimits_t *axisLimits, float b) {
	axisLimits->stopperDamper = b;
}


bool AxisLimits_IsWithinSafetyRange(const AxisLimits_t *axisLimits,
		float position) {
	return axisLimits->safety.positionRange.min <= position &&
			position <= axisLimits->safety.positionRange.max;
}

bool AxisLimits_IsWithinOperatingRange(const AxisLimits_t *axisLimits,
		float position) {
	return axisLimits->operating.positionRange.min <= position &&
			position <= axisLimits->operating.positionRange.max;
}

AxisLimitStopperType_e AxisLimits_GetStopperType(const AxisLimits_t *axisLimits) {
	return axisLimits->stopperType;
}

float AxisLimits_LimitTorque(AxisLimits_t *axisLimits,
		const AxisKinematics_t *kinematics, float desiredTorque) {
	float clampedTorque = ConstrainFloat(desiredTorque,
			-axisLimits->operating.maxTorque,
			axisLimits->operating.maxTorque);
	// Only apply stopper if enabled
	float outputTorque = axisLimits->stopperEnable ?
			AxisLimits_ApplyStopper(axisLimits, kinematics,
			clampedTorque) : clampedTorque;

	return outputTorque;
}

static float AxisLimits_ApplyStopper(AxisLimits_t *axisLimits,
		const AxisKinematics_t *kinematics, float desiredTorque) {

	float positionLimit;
	if(kinematics->position < axisLimits->operating.positionRange.min) {
		positionLimit =	axisLimits->operating.positionRange.min;
		axisLimits->stopperType = AXIS_LIMIT_STOPPER_TYPE_OPERATING_MIN;
	}
	else if(kinematics->position > axisLimits->operating.positionRange.max) {
		positionLimit = axisLimits->operating.positionRange.max;
		axisLimits->stopperType = AXIS_LIMIT_STOPPER_TYPE_OPERATING_MAX;
	}
	else {
		// Within operating range
		axisLimits->stopperActive = false;
		axisLimits->stopperType = AXIS_LIMIT_STOPPER_TYPE_NONE;
		return desiredTorque;
	}

	float deltaPosition = kinematics->position - positionLimit;

	float stopperTorque = -axisLimits->stopperSpring * deltaPosition -
			axisLimits->stopperDamper * kinematics->velocity;

	float torque;
	if(fabsf(deltaPosition) < 1) {
		torque = desiredTorque + stopperTorque;
	}
	else {
		torque = stopperTorque;
	}

	return torque;
}
