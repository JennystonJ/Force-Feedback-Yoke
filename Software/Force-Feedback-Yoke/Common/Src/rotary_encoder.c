/*
 * rotary_encoder.c
 *
 *  Created on: May 1, 2023
 *      Author: Jennyston
 */

#include "rotary_encoder.h"
#include "utilities.h"

static float RotaryEncCalcSpeed(RotaryEncoder_t *encoder, float deltaTimeMs);

void RotaryEncInit(RotaryEncoder_t *encoder) {
	encoder->prevHardCount = 0;
	encoder->count32 = 0;
	encoder->speed = 0;
	encoder->prevSpeedCount = 0;
	encoder->dtCounter = 0;
	encoder->prevDt = 0;
}

void RotaryEncSetCount(RotaryEncoder_t *encoder, int32_t count) {
	encoder->count32 = count;
}

int32_t RotaryEncGetCount(RotaryEncoder_t *encoder) {
	return encoder->count32;
}

float RotaryEncGetSpeed(RotaryEncoder_t *encoder) {
	return encoder->speed;
}


void RotaryEncUpdate(RotaryEncoder_t *encoder, uint16_t newCount,
		float deltaTimeMs) {

	//for speed calculation
	int32_t prevCount32 = encoder->count32;

	//find change in count
	int32_t deltaCount = (int32_t)newCount - encoder->prevHardCount;

	//newCount did not wrap around
	if(Abs(deltaCount) < ENC_COUNT_WRAP_THRESHOLD) {
		encoder->count32 += deltaCount;
	}
	//newCount wrapped around
	else {
		//newCount underflow
		if(encoder->prevHardCount < newCount){
			encoder->count32 -= (int32_t)0xFFFF + encoder->prevHardCount -
					newCount + 1;
		}
		//newCount overflow
		else {
			encoder->count32 += (int32_t)0xFFFF - encoder->prevHardCount + 1 +
					newCount;
		}
	}

	//TODO: switch to UnwrapAtThreshold16 function
//	encoder->count32 += UnwrapAtThreshold16(newCount, encoder->prevHardCount,
//			ENC_COUNT_WRAP_THRESHOLD);

	int32_t speedDeltaCount = encoder->count32 - encoder->prevSpeedCount;
	encoder->dtCounter += ENC_UPDATE_TIME_STEP;
	if(Abs(speedDeltaCount) >= ENC_UPDATE_SPEED_MIN_COUNT_DELTA &&
			encoder->dtCounter >=
			ENC_UPDATE_TIME_STEP*ENC_UPDATE_SPEED_SAMPLES) {

		//calculate and update speed
		encoder->speed = speedDeltaCount /
				(encoder->dtCounter * ENC_UPDATE_MS_SCALE);
		encoder->prevDt = encoder->dtCounter;
		encoder->dtCounter = 0;
		encoder->prevSpeedCount = encoder->count32;
	}
	else if(encoder->dtCounter >= 500) {
		encoder->speed = 0;
		encoder->prevSpeedCount = encoder->count32;
		encoder->dtCounter = 0;
	}
//	else {
//		encoder->speed = 0;
//	}



	//update previous hardware count
	encoder->prevHardCount = newCount;
}

