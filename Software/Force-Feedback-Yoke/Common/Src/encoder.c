/*
 * encoder.c
 *
 *  Created on: Mar 17, 2024
 *      Author: Jennyston
 */

#include "encoder.h"

void Encoder_Init(Encoder_t *encoder, EncoderInterface_t interface) {
	encoder->interface = interface;

	encoder->countPerRev = ENCODER_DEFAULT_COUNT_PER_REV;

	encoder->offset = 0;
	encoder->speed = 0;
	encoder->prevSpeed = 0;

	encoder->prevCount = interface.GetEncoderSensorCount(&interface);

}

void Encoder_SetReverse(Encoder_t *encoder, bool reverse) {
	encoder->reverse = reverse;
}

int Encoder_GetCount(Encoder_t *encoder) {
	int count = encoder->interface.GetEncoderSensorCount(
			&encoder->interface);
	return encoder->reverse ? -(count + encoder->offset) : count +
			encoder->offset;
}

void Encoder_SetCount(Encoder_t *encoder, int count) {
	encoder->offset = count - encoder->interface.GetEncoderSensorCount(
			&encoder->interface);
}

void Encoder_ResetCount(Encoder_t *encoder) {
	Encoder_SetCount(encoder, 0);
}

int Encoder_GetHardCount(Encoder_t *encoder) {
	return encoder->reverse ? encoder->countPerRev - 1 -
			encoder->interface.GetEncoderSensorAbsCount(&encoder->interface) :
			encoder->interface.GetEncoderSensorAbsCount(&encoder->interface);
}

float Encoder_GetSpeed(Encoder_t *encoder) {
	return encoder->speed;
}

void Encoder_SetCountPerRev(Encoder_t *encoder, int countPerRev) {
	encoder->countPerRev = countPerRev;
}

int Encoder_GetCountPerRev(Encoder_t *encoder) {
	return encoder->countPerRev;
}

void Encoder_Update(Encoder_t *encoder, float deltaTimeMs) {

	int currentCount = Encoder_GetCount(encoder);

	int deltaCount = currentCount - encoder->prevCount;

	// Calculate and update speed
	encoder->speed = deltaCount / deltaTimeMs;

	// Calculate and update acceleration
	float deltaSpeed = encoder->speed - encoder->prevSpeed;
	encoder->acceleration = deltaSpeed / deltaTimeMs;

	// Update previous values
	encoder->prevCount = currentCount;
	encoder->prevSpeed = encoder->speed;
}
