/*
 * ina219_reg.h
 *
 *  Created on: May 24, 2023
 *      Author: Jennyston
 */

#ifndef INC_DEVICES_INA219_REG_H_
#define INC_DEVICES_INA219_REG_H_

typedef enum {
	INA219_CONFIG = 0x00,
	INA219_SHUNT_V = 0x01,
	INA219_BUS_V = 0x02,
	INA219_POWER = 0x03,
	INA219_CURRENT = 0x04,
	INA219_CALIBRATION = 0x05,
} Ina219Reg;

#endif /* INC_DEVICES_INA219_REG_H_ */
