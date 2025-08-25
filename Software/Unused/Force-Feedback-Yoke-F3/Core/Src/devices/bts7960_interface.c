/*
 * bts7960_interface.c
 *
 *  Created on: Jul 13, 2024
 *      Author: Jennyston
 */

#include "devices/bts7960_interface.h"

// Private function prototypes
int MotorIGetPower(MotorInterface_t *interface);
void MotorISetPower(MotorInterface_t *interface, int power);

void BTS7960InterfaceInit(MotorInterface_t *interface, BTS7960_t *driver) {
	interface->hardwareMotor = driver;
	interface->MotorGetPower = &MotorIGetPower;
	interface->MotorSetPower = &MotorISetPower;
}

int MotorIGetPower(MotorInterface_t *interface) {
	return BTS7960GetPower((BTS7960_t *)interface->hardwareMotor);
}

void MotorISetPower(MotorInterface_t *interface, int power) {
	BTS7960SetPower((BTS7960_t *)interface->hardwareMotor, power);
}
