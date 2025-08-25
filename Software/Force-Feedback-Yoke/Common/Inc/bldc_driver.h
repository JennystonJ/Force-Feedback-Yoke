/*
 * bldc_driver.h
 *
 *  Created on: Jun 20, 2025
 *      Author: Jennyston
 */

#ifndef INC_BLDC_DRIVER_H_
#define INC_BLDC_DRIVER_H_

#include "peripherals/gpio.h"
#include <stdbool.h>

typedef struct BLDCDriverInterface BLDCDriverInterface_t;

struct BLDCDriverInterface {
	void *hardwareDriver;
	void (*SetDriverEnable)(BLDCDriverInterface_t *interface, bool enable);
	void (*SetPhaseVoltages)(BLDCDriverInterface_t *interface,
			float a, float b, float c);
	void (*SetPhaseDutyCycles)(BLDCDriverInterface_t *interface, float a,
			float b, float c);
	float (*GetBusVoltage)(BLDCDriverInterface_t *inteface);
};

typedef struct BLDCDriver {
	BLDCDriverInterface_t interface;
} BLDCDriver_t;

void BLDCDriver_Init(BLDCDriver_t *driver, BLDCDriverInterface_t interface);
void BLDCDriver_SetEnable(BLDCDriver_t *driver, bool enabled);
void BLDCDriver_SetDutyCycles(BLDCDriver_t *driver, float a, float b, float c);
void BLDCDriver_SetVoltages(BLDCDriver_t *driver, float a, float b, float c);
float BLDCDriver_GetBusVoltage(BLDCDriver_t *driver);

#endif /* INC_BLDC_DRIVER_H_ */
