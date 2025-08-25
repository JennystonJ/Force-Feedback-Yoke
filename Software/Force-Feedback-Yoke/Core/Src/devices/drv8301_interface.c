/*
 * DRV8301_interface.c
 *
 *  Created on: Jun 20, 2025
 *      Author: Jennyston
 */

#include <devices/drv8301_interface.h>
#include <stdbool.h>

// Private function prototypes
void BLDCI_SetDriverEnable(BLDCDriverInterface_t *interface, bool enable);
void BLDCI_SetPhaseVoltages(BLDCDriverInterface_t *interface, float u, float v,
		float w);
void BLDCI_SetPhaseDutyCycles(BLDCDriverInterface_t *interface, float u,
		float v, float w);
float BLDCI_GetBusVoltage(BLDCDriverInterface_t *interface);

void DRV8301Interface_Init(BLDCDriverInterface_t *interface,
		DRV8301_t *driver) {
	interface->hardwareDriver = driver;
	interface->SetDriverEnable = &BLDCI_SetDriverEnable;
	interface->SetPhaseVoltages = &BLDCI_SetPhaseVoltages;
	interface->SetPhaseDutyCycles = &BLDCI_SetPhaseDutyCycles;
	interface->GetBusVoltage = &BLDCI_GetBusVoltage;
}

//Private functions

void BLDCI_SetDriverEnable(BLDCDriverInterface_t *interface, bool enable) {
	DRV8301_SetDriverEnable((DRV8301_t *)interface->hardwareDriver, enable);
}

void BLDCI_SetPhaseVoltages(BLDCDriverInterface_t *interface, float u, float v,
		float w) {
	DRV8301_SetPhaseVoltages((DRV8301_t *)interface->hardwareDriver, u, v, w);
}

void BLDCI_SetPhaseDutyCycles(BLDCDriverInterface_t *interface, float u,
		float v, float w) {
	DRV8301_SetPhaseDutyCycles((DRV8301_t *)interface->hardwareDriver, u, v, w);
}

float BLDCI_GetBusVoltage(BLDCDriverInterface_t *interface) {
	return DRV8301_GetBusVoltage((DRV8301_t *)interface->hardwareDriver);
}
