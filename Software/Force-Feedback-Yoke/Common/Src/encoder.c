/*
 * encoder.c
 *
 *  Created on: Mar 17, 2024
 *      Author: Jennyston
 */

#include "encoder.h"
#include "math.h"

void Encoder_Init(Encoder_t *encoder, EncoderInterface_t interface) {
	encoder->interface = interface;

	encoder->countPerRev = ENCODER_DEFAULT_COUNT_PER_REV;

	encoder->offset = 0;
	encoder->velocity = 0;
	encoder->prevVelocity = 0;
	encoder->pulseTimerTickPeriod = 0.000001f;

	encoder->prevCount = interface.GetEncoderSensorCount(&interface);

}

void Encoder_SetReverse(Encoder_t *encoder, bool reverse) {
	encoder->reverse = reverse;
}

float Encoder_GetRad(Encoder_t *encoder) {
	return M_TWOPI * ((float)Encoder_GetCount(encoder)/
			Encoder_GetCountPerRev(encoder));
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

float Encoder_GetVelocityCountPerS(Encoder_t *encoder) {
	return encoder->velocity;
}

float Encoder_GetVelocityRadPerS(Encoder_t *encoder) {
//	return M_TWOPI * (encoder->velocity/Encoder_GetCountPerRev(encoder));
	return encoder->velocity;
}

void Encoder_SetCountPerRev(Encoder_t *encoder, int countPerRev) {
	encoder->countPerRev = countPerRev;
}

int Encoder_GetCountPerRev(Encoder_t *encoder) {
	return encoder->countPerRev;
}

EncoderEdgeTime_t Encoder_GetPulseTimeCount(Encoder_t *encoder) {
	return encoder->interface.GetEncoderSensorEdgeTime(&encoder->interface);
}

void Encoder_SetPulseTickPeriod(Encoder_t *encoder, float tickPeriod) {
	encoder->pulseTimerTickPeriod = tickPeriod;
}

float Encoder_GetPulseTickPeriod(Encoder_t *encoder) {
	return encoder->pulseTimerTickPeriod;
}

void Encoder_Update(Encoder_t *encoder, float deltaTimeMs) {

	EncoderEdgeTime_t edgeTime =
			encoder->interface.GetEncoderSensorEdgeTime(&encoder->interface);

	if(edgeTime.edgeTime != 0) {
		// TODO: Change magic numbers to constants
		float deltaRad = M_TWOPI * (edgeTime.edgeCount / 65536.0f);
		encoder->velocity = deltaRad / (edgeTime.edgeTime *
				4.1666666666666666666666666666667e-9f);
	}
	else {
		encoder->velocity = 0;
	}



	//int currentCount = Encoder_GetCount(encoder);
	/*
	int deltaCount = currentCount - encoder->prevCount;

	// Calculate and update velocity
//	float velocityCount = deltaCount / deltaTimeMs / 1000.0f;
//	float pulseCount = encoder->interface.GetEncoderSensorPulseCount(
//			&encoder->interface)/1000000.0f;
//	encoder->velocity = VelocityEstimator_CalcVelocity(&encoder->ve, velocityCount,
//			pulseCount);

//	encoder->velocity = deltaCount / deltaTimeMs / 1000.0f;

	// Calculate and update acceleration
	float deltaSpeed = encoder->velocity - encoder->prevVelocity;
	encoder->acceleration = deltaSpeed / deltaTimeMs / 1000.0f;

	// Update previous values
	encoder->prevCount = currentCount;
	encoder->prevVelocity = encoder->velocity;
	*/

//	int currentCount = Encoder_GetCount(encoder);
}
