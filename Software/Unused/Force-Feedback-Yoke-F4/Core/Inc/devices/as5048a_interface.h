/*
 * as5048a_interface.h
 *
 *  Created on: Apr 21, 2025
 *      Author: Jennyston
 */

#ifndef INC_DEVICES_AS5048A_INTERFACE_H_
#define INC_DEVICES_AS5048A_INTERFACE_H_

#include "as5048a.h"
#include "encoder.h"

void AS5048AInterfaceInit(EncoderInterface_t *interface, AS5048A_t *hwEncoder);


#endif /* INC_DEVICES_AS5048A_INTERFACE_H_ */
