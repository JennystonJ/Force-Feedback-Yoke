/*
 * mt6835_interface.h
 *
 *  Created on: Jul 6, 2025
 *      Author: Jennyston
 */

#ifndef INC_DEVICES_MT6835_INTERFACE_H_
#define INC_DEVICES_MT6835_INTERFACE_H_

#include "devices/mt6835.h"
#include "encoder.h"

void MT6835Interface_Init(EncoderInterface_t *interface, MT6835_t *hwEncoder);

#endif /* INC_DEVICES_MT6835_INTERFACE_H_ */
