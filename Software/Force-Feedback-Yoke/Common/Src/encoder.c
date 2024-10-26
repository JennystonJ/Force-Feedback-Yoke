/*
 * encoder.c
 *
 *  Created on: Mar 17, 2024
 *      Author: Jennyston
 */

#include "encoder.h"

void EncoderInit(Encoder_t *encoder, EncoderInterface_t interface) {
	encoder->interface = interface;

	encoder->countPerRev = ENCODER_DEFAULT_COUNT_PER_REV;
	encoder->totalCount = interface.GetEncoderSensorCount(&interface);
	encoder->prevHardCount = encoder->totalCount;
	encoder->speed = 0;
}

int EncoderGetCount(Encoder_t *encoder) {
	return encoder->totalCount;
}

void EncoderSetCount(Encoder_t *encoder, int count) {
	encoder->totalCount = count;
}

void EncoderResetCount(Encoder_t *encoder) {
	encoder->totalCount = 0;
}

float EncoderGetSpeed(Encoder_t *encoder) {
	return encoder->speed;
}

int EncoderGetCountPerRev(Encoder_t *encoder) {
	return encoder->countPerRev;
}

void EncoderUpdate(Encoder_t *encoder, float deltaTimeMs) {

	int deltaCount;
	int currentHardCount =
			encoder->interface.GetEncoderSensorCount(&encoder->interface);
	int countPerRevHalf = encoder->countPerRev/2;

	// Calculate deltaCount based on current and previous counts
	if(currentHardCount + countPerRevHalf < encoder->prevHardCount) {
		// Handle overflow
		deltaCount = (encoder->countPerRev - encoder->prevHardCount) +
				currentHardCount;
	}
	else if(currentHardCount > encoder->prevHardCount + countPerRevHalf) {
		// Handle underflow
		deltaCount = -((encoder->countPerRev - currentHardCount) +
				encoder->prevHardCount);
	}
	else {
		// default, simply add to total count
		deltaCount = currentHardCount - encoder->prevHardCount;
	}

	// Calculate and update speed
	encoder->speed = deltaCount / deltaTimeMs;

	// Update totalCount
	encoder->totalCount += deltaCount;

	// Update previous hardware count
	encoder->prevHardCount = currentHardCount;
}
