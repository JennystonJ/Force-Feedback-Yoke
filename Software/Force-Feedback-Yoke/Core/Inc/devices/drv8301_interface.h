/*
 * DRV8301_interface.h
 *
 *  Created on: Jun 20, 2025
 *      Author: Jennyston
 */

#ifndef INC_DEVICES_DRV8301_INTERFACE_H_
#define INC_DEVICES_DRV8301_INTERFACE_H_

#include "devices/drv8301.h"
#include "bldc_driver.h"

void DRV8301Interface_Init(BLDCDriverInterface_t *interface, DRV8301_t *driver);

#endif /* INC_DEVICES_DRV8301_INTERFACE_H_ */
