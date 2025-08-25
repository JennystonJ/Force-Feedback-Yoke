/*
 * AS5600_Registers.h
 *
 *  Created on: Mar 13, 2024
 *      Author: Jennyston
 */

#ifndef INC_AS5600_REGISTERS_H_
#define INC_AS5600_REGISTERS_H_

typedef enum {
	// Configuration Registers
	AS5600_ZMCO = 0x00,
	AS5600_ZPOS_1 = 0x01,
	AS5600_ZPOS_2 = 0x02,
	AS5600_MPOS_1 = 0x03,
	AS5600_MPOS_2 = 0x04,
	AS5600_MANG_1 = 0x05,
	AS5600_MANG_2 = 0x06,
	AS5600_CONF_1 = 0x07,
	AS5600_CONF_2 = 0x08,

	// Output Registers
	AS5600_RAW_ANGLE_1 = 0x0C,
	AS5600_RAW_ANGLE_2 = 0x0D,
	AS5600_ANGLE_1 = 0x0E,
	AS5600_ANGLE_2 = 0x0F,

	// Status Registers
	AS5600_STATUS = 0x0B,
	AS5600_AGC = 0x1A,
	AS5600_MAGNITUDE_1 = 0x1B,
	AS5600_MAGNITUDE_2 = 0x1C

} AS5600Reg;

#endif /* INC_AS5600_REGISTERS_H_ */
