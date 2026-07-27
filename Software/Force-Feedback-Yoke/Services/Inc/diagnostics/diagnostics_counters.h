/*
 * diagnostics_counters.h
 *
 *  Created on: Jul 17, 2026
 *      Author: Jennyston
 */

#ifndef INC_DIAGNOSTICS_DIAGNOSTICS_COUNTERS_H_
#define INC_DIAGNOSTICS_DIAGNOSTICS_COUNTERS_H_

typedef struct MotorCounters {
	uint32_t overCurrentTrips;
	uint32_t maxCurrent;
} MotorCounters_t;

typedef struct EncoderCounters {
	uint32_t spiErrorCount;
	uint32_t crcErrorCount;
} EncoderCounters_t;




#endif /* INC_DIAGNOSTICS_DIAGNOSTICS_COUNTERS_H_ */
