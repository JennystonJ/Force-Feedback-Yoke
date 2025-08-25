/*
 * encoder.h
 *
 *  Created on: Mar 17, 2024
 *      Author: Jennyston
 */

#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#define ENCODER_DEFAULT_COUNT_PER_REV 65536

typedef struct EncoderInterface EncoderInterface_t;

struct EncoderInterface {
	void *hardwareEncoder;
	int (*GetEncoderSensorCount)(EncoderInterface_t *);
	int (*GetEncoderSensorAbsCount)(EncoderInterface_t *);
};

typedef struct Encoder {
	EncoderInterface_t interface;

	bool reverse;
	int offset;

	int prevCount;
	int countPerRev;
	float speed;
	float prevSpeed;
	float acceleration;

} Encoder_t;

/*
 * Initializes encoder structure.
 * parameter encoder: pointer to encoder structure to initialize.
 * parameter interface: encoder interface that has already been initialized.
 */
void Encoder_Init(Encoder_t *encoder, EncoderInterface_t interface);

/*
 * Sets direction for encoder count.
 * parameter encoder: pointer to encoder structure.
 * parameter reverse: sets reverse parameter of encoder (true = reverse).
 */
void Encoder_SetReverse(Encoder_t *encoder, bool reverse);

/*
 * Obtains encoder count.
 * parameter encoder: pointer to encoder structure.
 * returns: encoder count.
 */
int Encoder_GetCount(Encoder_t *encoder);

/*
 * Assigns encoder count.
 * parameter encoder: pointer to encoder structure.
 * parameter count: count to be set to encoder.
 */
void Encoder_SetCount(Encoder_t *encoder, int count);

/*
 * Resets encoder count to 0.
 * parameter encoder: pointer to encoder structure.
 */
void Encoder_ResetCount(Encoder_t *encoder);

/*
 * Returns encoder hardware count.
 * parameter encoder: pointer to encoder structure.
 */
int Encoder_GetHardCount(Encoder_t *encoder);

/*
 * Obtains encoder speed in counts per millisecond.
 * parameter encoder: pointer to encoder structure.
 * returns: speed in counts per millisecond.
 */
float Encoder_GetSpeed(Encoder_t *encoder);

/*
 * Obtains number of counts per each encoder revolution.
 * parameter encoder: pointer to encoder structure.
 * returns: number of counts per each encoder revolution.
 */
int Encoder_GetCountPerRev(Encoder_t *encoder);

/*
 * Assigns the number of counts per each encoder revolution.
 * parameter encoder: pointer to encoder structure.
 * parameter countPerRev: number of counts per each encoder revolution.
 */
void Encoder_SetCountPerRev(Encoder_t *encoder, int countPerRev);

/*
 * Updates count and calculates speed and acceleration in encoder structure.
 * parameter encoder: pointer to encoder structure.
 * parameter deltaTimeMs: change in time from current and previous call in
 * milliseconds.
 */
void Encoder_Update(Encoder_t *encoder, float deltaTimeMs);

#ifdef __cplusplus
}
#endif

#endif /* INC_ENCODER_H_ */
