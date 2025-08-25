/*
 * circular_buffer.c
 *
 *  Created on: Aug 23, 2025
 *      Author: Jennyston
 */

#include "utilities/circular_buffer.h"
#include <string.h>

void CircularBuffer_Init(CircularBuffer_t *buffer, int data[],
		int lengthInBytes){
	buffer->headIndex = 0;
	buffer->tailIndex = 0;
	buffer->data = data;
	buffer->len = lengthInBytes/sizeof(int);

	memset(buffer->data, 0, lengthInBytes);
}
void CircularBuffer_Append(CircularBuffer_t *buffer, int value){
	buffer->data[buffer->tailIndex] = value;
	// Increment tail index, wrap if needed
	buffer->tailIndex = (buffer->tailIndex + 1) % buffer->len;
}
int CircularBuffer_GetNext(CircularBuffer_t *buffer){
	if(CircularBuffer_HasNext(buffer)) {
		int data = buffer->data[buffer->headIndex];
		// Increment head index, wrap if needed
		buffer->headIndex = (buffer->headIndex + 1) % buffer->len;
	}
	else {
		// No data available
		return 0;
	}
}
bool CircularBuffer_HasNext(CircularBuffer_t *buffer){
	return buffer->headIndex != buffer->tailIndex;
}
int *CircularBuffer_GetData(CircularBuffer_t *buffer){
	return buffer->data;
}
