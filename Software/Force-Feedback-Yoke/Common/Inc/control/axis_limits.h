/*
 * axis_limits.h
 *
 *  Created on: Jun 1, 2026
 *      Author: Jennyston
 */

#ifndef INC_CONTROL_AXIS_LIMITS_H_
#define INC_CONTROL_AXIS_LIMITS_H_

#include <stdbool.h>
#include "axis_range.h"
#include "control/axis_kinematics.h"

typedef enum AxisLimitStopperType {
	AXIS_LIMIT_STOPPER_TYPE_NONE,
	AXIS_LIMIT_STOPPER_TYPE_OPERATING_MIN,
	AXIS_LIMIT_STOPPER_TYPE_OPERATING_MAX,
	AXIS_LIMIT_STOPPER_TYPE_SAFETY_MIN,
	AXIS_LIMIT_STOPPER_TYPE_SAFETY_MAX,
} AxisLimitStopperType_e;

typedef struct AxisLimitSet_t {
	AxisRange_t positionRange;
	float maxTorque;
} AxisLimitSet_t;

typedef struct AxisLimits {
	AxisLimitSet_t safety;
	AxisLimitSet_t operating;
	AxisLimitStopperType_e stopperType;

	bool stopperEnable;
	bool stopperActive;
	float stopperSpring;
	float stopperDamper;
} AxisLimits_t;


void AxisLimits_Init(AxisLimits_t *axisLimits, AxisLimitSet_t safety,
		AxisLimitSet_t operating);

void AxisLimits_SetSafetyPositionRange(AxisLimits_t *axisLimits,
		AxisRange_t positionRange);
AxisRange_t AxisLimits_GetSafetyPositionRange(const AxisLimits_t *axisLimits);
void AxisLimits_SetSafetyMaxTorque(AxisLimits_t *axisLimits, float maxTorque);
float AxisLimits_GetSafetyMaxTorque(const AxisLimits_t *axisLimits);

void AxisLimits_SetOperatingPositionRange(AxisLimits_t *axisLimits,
		AxisRange_t positionRange);
AxisRange_t AxisLimits_GetOperatingPositionRange(const AxisLimits_t *axisLimits);
void AxisLimits_SetOperatingMaxTorque(AxisLimits_t *axisLimits, float maxTorque);
float AxisLimits_GetOperatingMaxTorque(const AxisLimits_t *axisLimits);

void AxisLimits_SetStopperEnable(AxisLimits_t *axisLimits, bool enabled);
void AxisLimits_SetStopperSpringGain(AxisLimits_t *axisLimits, float k);
void AxisLimits_SetStopperDamperGain(AxisLimits_t *axisLimits, float b);

bool AxisLimits_IsWithinSafetyRange(const AxisLimits_t *axisLimits,
		float position);
bool AxisLimits_IsWithinOperatingRange(const AxisLimits_t *axisLimits,
		float position);
AxisLimitStopperType_e AxisLimits_GetStopperType(const AxisLimits_t *axisLimits);
float AxisLimits_LimitTorque(AxisLimits_t *axisLimits,
		const AxisKinematics_t *kinematics, float desiredTorque);

#endif /* INC_CONTROL_AXIS_LIMITS_H_ */
