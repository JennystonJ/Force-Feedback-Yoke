/*
 * encoder_ex.h
 *
 *  Created on: Jun 14, 2026
 *      Author: Jennyston
 */

#ifndef INC_ENCODER_EX_H_
#define INC_ENCODER_EX_H_

#include "encoder.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct EncoderCaptureBuffer {
	uint16_t pulseTimes[16];
} EncoderCaptureBuffer_t;

typedef struct EncoderEx {
	Encoder_t base;


	EncoderCaptureBuffer_t *captureBuffer;
} EncoderEx_t;

void EncoderEx_Init(EncoderEx_t *encoder, EncoderInterface_t *interface,
		EncoderCaptureBuffer_t *captureBuffer);

#endif /* INC_ENCODER_EX_H_ */
