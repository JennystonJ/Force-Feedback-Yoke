/*
 * rotary_encoder.h
 *
 *  Created on: May 1, 2023
 *      Author: Jennyston
 */

#ifndef INC_ROTARY_ENCODER_H_
#define INC_ROTARY_ENCODER_H_

#ifdef __cplusplus
extern "C" {
#endif


#define ENC_COUNT_WRAP_THRESHOLD 0x7FFF
#define ENC_UPDATE_TIME_STEP 5
#define ENC_UPDATE_MS_SCALE (0.1f)
#define ENC_UPDATE_SPEED_SAMPLES 25
#define ENC_UPDATE_SPEED_MIN_COUNT_DELTA 3

#include <stdint.h>

typedef struct RotaryEncoder {
	int32_t count32;
	uint16_t prevHardCount;
	int32_t prevSpeedCount;
	float speed;
	uint32_t dtCounter;
	uint32_t prevDt;
} RotaryEncoder_t;

/*
 * Initializes encoder structure.
 * parameter encoder: pointer to encoder structure to initialize.
 */
void RotaryEncInit(RotaryEncoder_t *encoder);

/*
 * Obtains encoder count.
 * parameter encoder: pointer to encoder structure.
 * returns: encoder count.
 */
int32_t RotaryEncGetCount(RotaryEncoder_t *encoder);

/*
 * Assigns encoder count.
 * parameter encoder: pointer to encoder structure.
 * parameter count: count to be set to encoder.
 */
void RotaryEncSetCount(RotaryEncoder_t *encoder, int32_t count);

/*
 * Obtains encoder speed in counts per millisecond.
 * parameter encoder: pointer to encoder structure.
 * returns: speed in counts per millisecond.
 */
float RotaryEncGetSpeed(RotaryEncoder_t *encoder);

/*
 * Updates count and computes speed in encoder structure.
 * parameter encoder: pointer to encoder structure.
 * parameter newCount: new encoder count.
 * parameter deltaTimeMs: change in time from current and previous call in
 * milliseconds.
 */
void RotaryEncUpdate(RotaryEncoder_t *encoder, uint16_t newCount,
		float deltaTimeMs);

#ifdef __cplusplus
}
#endif

#endif /* INC_ROTARY_ENCODER_H_ */
;
