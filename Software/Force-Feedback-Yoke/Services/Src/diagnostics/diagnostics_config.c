/*
 * diagnostics_config.c
 *
 *  Created on: Jul 15, 2026
 *      Author: Jennyston
 */

#include "diagnostics/diagnostics_config.h"

const DiagnosticsConfig_t diagConfig = {
		.motorId = {
				"PITCH",
				"ROLL"
		},
		.encoderId = {
				"PITCH",
				"ROLL"
		},
		.usbId = "1"
};

const MotorDiagnosticsConfig_t pitchMotorDiagConfig = {
		.id = 0,
		.overcurrentReportLimit = 3.0f,
};

const MotorDiagnosticsConfig_t rollMotorDiagConfig = {
		.id = 1,
		.overcurrentReportLimit = 3.0f,
};
