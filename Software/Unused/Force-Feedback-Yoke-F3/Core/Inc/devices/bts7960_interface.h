/*
 * bts7960_interface.h
 *
 *  Created on: Jul 13, 2024
 *      Author: Jennyston
 */

#ifndef INC_DEVICES_BTS7960_INTERFACE_H_
#define INC_DEVICES_BTS7960_INTERFACE_H_

#include "devices/bts7960.h"
#include "motor.h"

void BTS7960InterfaceInit(MotorInterface_t *interface, BTS7960_t *driver);

#endif /* INC_DEVICES_BTS7960_INTERFACE_H_ */
