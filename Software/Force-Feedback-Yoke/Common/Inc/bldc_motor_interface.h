/*
 * bldc_motor_interface.h
 *
 *  Created on: Jul 10, 2025
 *      Author: Jennyston
 */

#ifndef INC_BLDC_MOTOR_INTERFACE_H_
#define INC_BLDC_MOTOR_INTERFACE_H_

#include "bldc_motor.h"
#include "motor.h"

void BLDCMotorInterface_Init(MotorInterface_t *interface, BLDCMotor_t *motor);

#endif /* INC_BLDC_MOTOR_INTERFACE_H_ */
