/*
 * diagnostics_fault_types.h
 *
 *  Created on: Jul 17, 2026
 *      Author: Jennyston
 */

#ifndef INC_DIAGNOSTICS_DIAGNOSTICS_FAULT_TYPES_H_
#define INC_DIAGNOSTICS_DIAGNOSTICS_FAULT_TYPES_H_

typedef enum MotorFaultFlags {
	FAULT_MOTOR_NONE			= 0,
	FAULT_MOTOR_OVERCURRENT		= (1 << 0),
	FAULT_MOTOR_DRIVER_FAULT  	= (1 << 1),
} MotorFaultFlags_e;

typedef enum EncoderFaultFlags {
	FAULT_ENCODER_NONE				= 0,
	FAULT_ENCODER_SPI				= (1 << 0),
	FAULT_ENCODER_CRC				= (1 << 1),
} EncoderFaultFlags_e;

typedef enum UsbFaultFlags {
	FAULT_USB_NONE					= 0,
} UsbFaultFlags_e;

#endif /* INC_DIAGNOSTICS_DIAGNOSTICS_FAULT_TYPES_H_ */
