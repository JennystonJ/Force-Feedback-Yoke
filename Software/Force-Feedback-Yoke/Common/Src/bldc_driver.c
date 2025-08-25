/*
 * bldc_driver.c
 *
 *  Created on: Jun 20, 2025
 *      Author: Jennyston
 */

#include "bldc_driver.h"
#include <stdint.h>
#include "utilities/utilities.h"

void BLDCDriver_Init(BLDCDriver_t *driver, BLDCDriverInterface_t interface) {
	driver->interface = interface;
	BLDCDriver_SetDutyCycles(driver, 0.5f, 0.5f, 0.5f);
}

void BLDCDriver_SetEnable(BLDCDriver_t *driver, bool enabled) {
	driver->interface.SetDriverEnable(&driver->interface, enabled);
}

void BLDCDriver_SetDutyCycles(BLDCDriver_t *driver, float a, float b,
		float c) {
	driver->interface.SetPhaseDutyCycles(&driver->interface, a, b, c);
}

void BLDCDriver_SetVoltages(BLDCDriver_t *driver, float a, float b, float c) {
	driver->interface.SetPhaseVoltages(&driver->interface, a, b, c);
}

float BLDCDriver_GetBusVoltage(BLDCDriver_t *driver) {
	return driver->interface.GetBusVoltage(&driver->interface);
}
