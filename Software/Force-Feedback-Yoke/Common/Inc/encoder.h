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

#define ENCODER_DEFAULT_COUNT_PER_REV 4096

typedef struct EncoderInterface EncoderInterface_t;

struct EncoderInterface {
	void *hardwareEncoder;
	int (*GetEncoderSensorCount)(EncoderInterface_t *);
};

typedef struct Encoder {
	EncoderInterface_t interface;
	int totalCount;
	int prevHardCount;
	int countPerRev;
	float speed;

} Encoder_t;

/*
 * Initializes encoder structure.
 * parameter encoder: pointer to encoder structure to initialize.
 * parameter interface: encoder interface that has already been initialized
 */
void EncoderInit(Encoder_t *encoder, EncoderInterface_t interface);

/*
 * Obtains encoder count.
 * parameter encoder: pointer to encoder structure.
 * returns: encoder count.
 */
int EncoderGetCount(Encoder_t *encoder);

/*
 * Assigns encoder count.
 * parameter encoder: pointer to encoder structure.
 * parameter count: count to be set to encoder.
 */
void EncoderSetCount(Encoder_t *encoder, int count);

/*
 * Resets encoder count to 0.
 * parameter encoder: pointer to encoder structure.
 */
void EncoderResetCount(Encoder_t *encoder);

/*
 * Obtains encoder speed in counts per millisecond.
 * parameter encoder: pointer to encoder structure.
 * returns: speed in counts per millisecond.
 */
float EncoderGetSpeed(Encoder_t *encoder);

/*
 * Obtains number of counts per each encoder revolution.
 * parameter encoder: pointer to encoder structure.
 * returns: number of counts per each encoder revolution.
 */
int EncoderGetCountPerRev(Encoder_t *encoder);



/*
 * Updates count and calculates speed in encoder structure.
 * parameter encoder: pointer to encoder structure.
 * parameter deltaTimeMs: change in time from current and previous call in
 * milliseconds.
 */
void EncoderUpdate(Encoder_t *encoder, float deltaTimeMs);

#ifdef __cplusplus
}
#endif

#endif /* INC_ENCODER_H_ */
