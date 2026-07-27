/*
 * encoder_ex.c
 *
 *  Created on: Jun 14, 2026
 *      Author: Jennyston
 */

#include "encoder_ex.h"

void EncoderEx_Init(EncoderEx_t *encoder, EncoderInterface_t *interface,
		EncoderCaptureBuffer_t *captureBuffer) {
	Encoder_Init(&encoder->base, *interface);

	encoder->captureBuffer = captureBuffer;
}
