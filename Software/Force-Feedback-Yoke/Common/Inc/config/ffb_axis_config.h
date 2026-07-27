/*
 * ffb_axis_config.h
 *
 *  Created on: Apr 27, 2026
 *      Author: Jennyston
 */

#ifndef INC_CONFIG_FFB_AXIS_CONFIG_H_
#define INC_CONFIG_FFB_AXIS_CONFIG_H_

#include <stdbool.h>
#include "motor.h"
#include "encoder.h"
#include "load_cell.h"
#include "force_feedback/force_feedback_controller.h"
#include "control/axis_range.h"
#include "control/velocity_control.h"

typedef struct AxisHardware {
	Motor_t *motor;
	Encoder_t *encoder;
	LoadCell_t *loadCell;
} AxisHardware_t;

typedef struct LoadCellConfig {
	float lpfAlpha;
	float conversionConstant;
} LoadCellConfig_t;

typedef struct VelocityConfig {
	float kp;
	float ki;
	float kd;
	float integralLimit;
	float epsilon;
	float lpfAlpha;
	int loopDivider;
	float lpfAccelAlpha;
} VelocityConfig_t;

typedef struct PositionConfig {
	float kp;
	float ki;
	float kd;
	float integralLimit;
	float epsilon;
} PositionConfig_t;

typedef struct VelocityEstimatorConfig {
	float kP;
	float kI;
} VelocityEstimatorConfig_t;

typedef struct AssistConfig {
	float assistGain;
	float accelGain;
	float velGain;
	float velSmallComp;
} AssistConfig_t;

typedef struct FFBControllerConfig {
	float lockKp;
	float lockKd;
} FFBControllerConfig_t;

typedef struct AxisGeometryConfig {
	float yokeEffortToMotorTorque;
	float posToRad;
} AxisGeometryConfig_t;

typedef struct AxisSafeLimitsConfig {
	AxisRange_t positionRange;
	float maxTorque;
} AxisSafeLimitsConfig_t;

typedef struct AxisLimitsStopperConfig {
	float springGain;
	float damperGain;
} AxisLimitsStopperConfig_t;

typedef struct FFBHomeConfig {
	float searchVelocity;
	float searchMotorTorque;
	float searchAcceleration;
} FFBHomeConfig_t;

typedef struct FFBAxisConfig {
	AxisHardware_t hardware;
	LoadCellConfig_t loadCell;
	VelocityConfig_t vel;
	PositionConfig_t pos;
	VelocityEstimatorConfig_t ve;
	AssistConfig_t assist;
	FFBControllerConfig_t ffb;
	AxisGeometryConfig_t geom;
	AxisSafeLimitsConfig_t safeLimits;
	AxisLimitsStopperConfig_t stopper;
	FFBHomeConfig_t home;
	bool reverse;
} FFBAxisConfig_t;

extern const FFBAxisConfig_t pitchConfig;
extern const FFBAxisConfig_t rollConfig;

#endif /* INC_CONFIG_FFB_AXIS_CONFIG_H_ */
