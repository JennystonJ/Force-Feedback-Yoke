/*
 * diagnostics_counter_types.h
 *
 *  Created on: Jul 17, 2026
 *      Author: Jennyston
 */

#ifndef INC_DIAGNOSTICS_DIAGNOSTICS_COUNTER_TYPES_H_
#define INC_DIAGNOSTICS_DIAGNOSTICS_COUNTER_TYPES_H_

typedef enum DiagnosticsSystemCounter {
	DIAG_COUNTER_SYSTEM_UPTIME,
} DiagnosticsSystemCounter_e;

typedef enum DiagnosticsMotorCounter {
	DIAG_COUNTER_MOTOR_OVERCURRENT,
	DIAG_COUTNER_MOTOR_FAULT,
} DiagnosticsMotorCounter_e;

typedef enum DiagnosticsEncoderCounter {
	DIAG_COUNTER_ENCODER_SPI_ERROR,
	DIAG_COUNTER_ENCODER_CRC_ERROR,
} DiagnosticsEncoderCounter_e;

typedef enum DiagnosticsUsbCounter {
	DIAG_COUNTER_USB_ERROR,
} DiagnosticsUsbCounter_e;

#endif /* INC_DIAGNOSTICS_DIAGNOSTICS_COUNTER_TYPES_H_ */
