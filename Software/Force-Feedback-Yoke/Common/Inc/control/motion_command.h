/*
 * ,otion_command.h
 *
 *  Created on: Jun 5, 2026
 *      Author: Jennyston
 */

#ifndef INC_CONTROL_MOTION_COMMAND_H_
#define INC_CONTROL_MOTION_COMMAND_H_

typedef enum MotionControlType {
	MOTION_CONTROL_TYPE_TORQUE,
	MOTION_CONTROL_TYPE_VELOCITY,
	MOTION_CONTROL_TYPE_POSITION,
} MotionControlType_e;

typedef struct TorqueControlCommand {
	float torqueTarget;
	float torqueLimit;
} TorqueControlCommand_t;

typedef struct VelocityControlCommand {
	float velocityTarget;
	float torqueLimit;
	float accelerationLimit;
} VelocityControlCommand_t;

typedef struct PositionControlCommand {
	float position;
	float velocityLimit;
	float torqueLimit;
	float accelerationLimit;
} PositionControlCommand_t;

typedef struct MotionControlCommand {
	MotionControlType_e type;

	union {
		TorqueControlCommand_t torqueCommand;
		VelocityControlCommand_t velocityCommand;
		PositionControlCommand_t positionCommand;
	} data;

} MotionControlCommand_t;

static const MotionControlCommand_t zeroTorqueCommand = {
		.type = MOTION_CONTROL_TYPE_TORQUE,
		.data.torqueCommand = {
			.torqueTarget = 0.0f,
			.torqueLimit = 0.0f
		},
};

#endif /* INC_CONTROL_MOTION_COMMAND_H_ */
