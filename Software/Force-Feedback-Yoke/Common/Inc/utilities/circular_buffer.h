/*
 * circular_buffer.h
 *
 *  Created on: Aug 23, 2025
 *      Author: Jennyston
 */

#ifndef INC_UTILITIES_CIRCULAR_BUFFER_H_
#define INC_UTILITIES_CIRCULAR_BUFFER_H_

#include <stdbool.h>

typedef struct CircularBuffer {
	int headIndex;
	int tailIndex;
	int *data;
	int len;
} CircularBuffer_t;

void CircularBuffer_Init(CircularBuffer_t *buffer, int data[],
		int lengthInBytes);
void CircularBuffer_Append(CircularBuffer_t *buffer, int value);
int CircularBuffer_GetNext(CircularBuffer_t *buffer);
bool CircularBuffer_HasNext(CircularBuffer_t *buffer);
int *CircularBuffer_GetData(CircularBuffer_t *buffer);

#endif /* INC_UTILITIES_CIRCULAR_BUFFER_H_ */
