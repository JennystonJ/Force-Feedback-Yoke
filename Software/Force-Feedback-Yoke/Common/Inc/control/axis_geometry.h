/*
 * axis_geometry.h
 *
 *  Created on: Apr 27, 2026
 *      Author: Jennyston
 */

#ifndef INC_CONTROL_AXIS_GEOMETRY_H_
#define INC_CONTROL_AXIS_GEOMETRY_H_

typedef struct AxisGeometry {
	float yokeEffortToMotorTorque;
	float posToRad;
} AxisGeometry_t;

static inline AxisGeometry_t AxisGeometry_Default(void) {
	return (AxisGeometry_t) {
		.yokeEffortToMotorTorque = 1.0f,
		.posToRad = 1.0f,
	};
}

static inline float AxisGeometry_YokeEffortToMotorTorque(const AxisGeometry_t *axis,
		float effort) {
	return axis->yokeEffortToMotorTorque * effort;
}

static inline float AxisGeometry_MotorTorqueToYokeEffort(const AxisGeometry_t *axis,
		float torque) {
	return torque / axis->yokeEffortToMotorTorque;
}

static inline float AxisGeometry_PosToRad(const AxisGeometry_t *axis, int position) {
	return position * axis->posToRad;
}

static inline float AxisGeometry_RadToPos(const AxisGeometry_t *axis, int rad) {
	return rad / axis->posToRad;
}


#endif /* INC_CONTROL_AXIS_GEOMETRY_H_ */
