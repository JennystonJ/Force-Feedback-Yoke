/*
 * as5600_interface.h
 *
 *  Created on: Jul 13, 2024
 *      Author: Jennyston
 */

#ifndef INC_DEVICES_AS5600_INTERFACE_H_
#define INC_DEVICES_AS5600_INTERFACE_H_

#include "as5600.h"
#include "encoder.h"

void AS5600InterfaceInit(EncoderInterface_t *interface, AS5600_t *hwEncoder);

#endif /* INC_DEVICES_AS5600_INTERFACE_H_ */
