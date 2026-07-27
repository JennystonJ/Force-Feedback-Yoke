/*
 * ffb_axis_config.c
 *
 *  Created on: Apr 27, 2026
 *      Author: Jennyston
 */

#include <config/ffb_axis_config.h>
#include "config/force_feedback_config.h"
#include "config/config.h"
#include "bsp.h"
#include <stddef.h>

const FFBAxisConfig_t pitchConfig = {
		.hardware = {
				.motor = &pitchMotor,
				.encoder = &pitchEncoder,
				.loadCell = &pitchLoadCell,
		},
		.loadCell = {
				.lpfAlpha = LOAD_CELL_LPF_ALPHA,
				.conversionConstant = LOAD_CELL_PITCH_CONVERSION_CONSTANT,
		},
		.vel = {
				.kp = VELOCITY_CONTROL_PITCH_KP,
				.ki = VELOCITY_CONTROL_PITCH_KI,
				.kd = VELOCITY_CONTROL_PITCH_KD,
				.integralLimit = VELOCITY_CONTROL_PITCH_INTEGRAL_LIMIT,
				.epsilon = VELOCITY_CONTROL_PITCH_EPSILON,
				.lpfAlpha = MOTOR_PITCH_VELOCITY_LPF_ALPHA,
				.loopDivider = MOTOR_PITCH_VELOCITY_LOOP_FREQ_DIV,
				.lpfAccelAlpha = 0.0f,
		},
		.pos = {
				.kp = POSITION_CONTROL_PITCH_KP,
				.ki = POSITION_CONTROL_PITCH_KI,
				.kd = POSITION_CONTROL_PITCH_KD,
				.integralLimit = POSITION_CONTROL_PITCH_INTEGRAL_LIMIT,
				.epsilon = POSITION_CONTROL_PITCH_EPSILON,
		},
		.ve = {
			.kP = VE_KP_PITCH,
			.kI = VE_KI_PITCH,
		},
		.assist = {
				.assistGain = FFB_ASSIST_GAIN,
				.accelGain = FFB_ASSIST_ACCEL_GAIN,
				.velGain = FFB_ASSIST_VELOCITY_GAIN,
				.velSmallComp = FFB_ASSIST_VELOCITY_SMALL_COMP,
		},
		.ffb = {
				.lockKp = FFB_PITCH_LOCK_KP,
				.lockKd = FFB_PITCH_LOCK_KD,
		},
		.geom = {
				.yokeEffortToMotorTorque = EFFORT_TO_TORQUE_PITCH,
				.posToRad = POS_TO_RAD_PITCH,
		},
		.safeLimits = {
				.positionRange = {
						.min = PITCH_UNHOMED_SAFE_LIMIT_MIN_RAD,
						.max = PITCH_UNHOMED_SAFE_LIMIT_MAX_RAD
				},
				.maxTorque = PITCH_MOTOR_TORQUE_LIMIT,
		},
		.stopper = {
			.springGain = AXIS_PITCH_STOPPER_SPRING_GAIN,
			.damperGain = AXIS_PITCH_STOPPER_DAMPER_GAIN,
		},
		.home = {
				.searchVelocity = AXIS_PITCH_HOME_SEARCH_VELOCITY,
				.searchMotorTorque = AXIS_PITCH_HOME_SEARCH_TORQUE,
				.searchAcceleration = AXIS_PITCH_HOME_SEARCH_ACCELERATION,
		},
		.reverse = AXIS_REVERSE_PITCH,
};

const FFBAxisConfig_t rollConfig = {
		.hardware = {
				.motor = &rollMotor,
				.encoder = &rollEncoder,
				.loadCell = NULL,
		},
		.loadCell = {
				.lpfAlpha = 0,
				.conversionConstant = 0,
		},
		.vel = {
				.kp = VELOCITY_CONTROL_ROLL_KP,
				.ki = VELOCITY_CONTROL_ROLL_KI,
				.kd = VELOCITY_CONTROL_ROLL_KD,
				.integralLimit = VELOCITY_CONTROL_ROLL_INTEGRAL_LIMIT,
				.epsilon = VELOCITY_CONTROL_ROLL_EPSILON,
				.lpfAlpha = MOTOR_ROLL_VELOCITY_LPF_ALPHA,
				.loopDivider = MOTOR_ROLL_VELOCITY_LOOP_FREQ_DIV,
				.lpfAccelAlpha = 0.0f,
		},
		.pos = {
				.kp = POSITION_CONTROL_ROLL_KP,
				.ki = POSITION_CONTROL_ROLL_KI,
				.kd = POSITION_CONTROL_ROLL_KD,
				.integralLimit = POSITION_CONTROL_ROLL_INTEGRAL_LIMIT,
				.epsilon = POSITION_CONTROL_ROLL_EPSILON,
		},
		.ve = {
			.kP = VE_KP_ROLL,
			.kI = VE_KI_ROLL,
		},
		.assist = {
				.assistGain = 0,
				.accelGain = 0,
				.velGain = 0,
				.velSmallComp = 0,
		},
		.ffb = {
				.lockKp = FFB_ROLL_LOCK_KP,
				.lockKd = FFB_ROLL_LOCK_KD,
		},
		.geom = {
				.yokeEffortToMotorTorque = EFFORT_TO_TORQUE_ROLL,
				.posToRad = POS_TO_RAD_ROLL,
		},
		.safeLimits = {
				.positionRange = {
						.min = ROLL_UNHOMED_SAFE_LIMIT_MIN_RAD,
						.max = ROLL_UNHOMED_SAFE_LIMIT_MAX_RAD
				},
				.maxTorque = ROLL_MOTOR_TORQUE_LIMIT,
		},
		.stopper = {
			.springGain = AXIS_ROLL_STOPPER_SPRING_GAIN,
			.damperGain = AXIS_ROLL_STOPPER_DAMPER_GAIN,
		},
		.home = {
				.searchVelocity = AXIS_ROLL_HOME_SEARCH_VELOCITY,
				.searchMotorTorque = AXIS_ROLL_HOME_SEARCH_TORQUE,
				.searchAcceleration = AXIS_ROLL_HOME_SEARCH_ACCELERATION,
		},
		.reverse = AXIS_REVERSE_ROLL,
};
