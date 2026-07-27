/*
 * diagnostics_events.h
 *
 *  Created on: Jul 17, 2026
 *      Author: Jennyston
 */

#ifndef INC_DIAGNOSTICS_DIAGNOSTICS_EVENTS_H_
#define INC_DIAGNOSTICS_DIAGNOSTICS_EVENTS_H_

#include "diagnostics_event_types.h"

typedef struct DiagnosticsEvent {
	DiagnosticsEvent_e event;
	uint8_t source;
	uint32_t timestamp;
} DiagnosticsEvent_t;

#endif /* INC_DIAGNOSTICS_DIAGNOSTICS_EVENTS_H_ */
