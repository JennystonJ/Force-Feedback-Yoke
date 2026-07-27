/*
 * diagnostics_config.h
 *
 *  Created on: Jul 15, 2026
 *      Author: Jennyston
 */

#ifndef INC_DIAGNOSTICS_CONFIG_H_
#define INC_DIAGNOSTICS_CONFIG_H_

#include <stdint.h>

typedef struct DiagnosticsConfig {
	const char *motorId[2];
	const char *encoderId[2];
	const char *usbId;
} DiagnosticsConfig_t;

typedef struct MotorDiagnosticsConfig {
	int8_t id;
	float overcurrentReportLimit;
} MotorDiagnosticsConfig_t;

extern const DiagnosticsConfig_t diagConfig;

extern const MotorDiagnosticsConfig_t pitchMotorDiagConfig;
extern const MotorDiagnosticsConfig_t rollMotorDiagConfig;

#endif /* INC_DIAGNOSTICS_CONFIG_H_ */
