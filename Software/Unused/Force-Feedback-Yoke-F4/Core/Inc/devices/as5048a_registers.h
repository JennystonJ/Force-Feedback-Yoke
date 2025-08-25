/*
 * as5048a_registers.h
 *
 *  Created on: Apr 21, 2025
 *      Author: Jennyston
 */

#ifndef INC_DEVICES_AS5048A_REGISTERS_H_
#define INC_DEVICES_AS5048A_REGISTERS_H_

typedef enum {
	// Control and Error Registers
	AS5048A_NOP = 0x0000,
	AS5048A_CLR_ERR_FLAG = 0x0001,
	AS5048A_PROG_CTRL = 0x0003,

	// Readout Registers
	AS5048A_DIAG_AGC = 0x3FFD,
	AS5048A_MAGNITUDE = 0x3FFE,
	AS5048A_ANGLE = 0x3FFF
} AS5048AReg;

#endif /* INC_DEVICES_AS5048A_REGISTERS_H_ */
