/*
 * axis_kinematics.h
 *
 *  Created on: May 18, 2026
 *      Author: Jennyston
 */

#ifndef INC_CONTROL_AXIS_KINEMATICS_H_
#define INC_CONTROL_AXIS_KINEMATICS_H_

typedef struct AxisKinematics {
	float position;
	float motorTorque;
	float loadCellTorque;
	float velocity;
	float acceleration;
} AxisKinematics_t;

#endif /* INC_CONTROL_AXIS_KINEMATICS_H_ */
