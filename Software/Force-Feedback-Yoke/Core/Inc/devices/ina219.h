/*
 * ina219.h
 *
 *  Created on: May 24, 2023
 *      Author: Jennyston
 */

#ifndef INC_DEVICES_INA219_H_
#define INC_DEVICES_INA219_H_

#include "stm32f3xx.h"

#define INA219_ADDR (0x40<<1)

typedef struct Ina219 {

	I2C_HandleTypeDef *hi2c;

} Ina219_t;

void CurrentSenseInit(Ina219_t *cSense, I2C_HandleTypeDef *hi2c);
float CurrentSenseGetCurrent(Ina219_t *cSense);

#endif /* INC_DEVICES_INA219_H_ */
