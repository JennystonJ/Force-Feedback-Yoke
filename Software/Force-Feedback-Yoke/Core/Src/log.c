/*
 * log.c
 *
 *  Created on: Jul 12, 2026
 *      Author: Jennyston
 */

#include "log.h"
#include "utilities/utilities.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include "main.h"

static char ringBufferTx[2048];
static int	ringBufferTxHead = 0;
static int ringBufferTxTail = 0;
static bool uartDmaBusy;
static uint16_t bytesWriting = 0;


static void Log_Write(const char *buffer, int length);
static void Log_RingBufferWrite(const char *buffer, int length);
static uint16_t Log_RingBufferGetContiguousReadLength(void);
static bool Log_Append(char **p, size_t *remaining, const char *fmt, ...);
char *Log_RingBufferGetReadPointer(void);

static const char *strLevels[] = { "",
		"[ERROR]", "[WARN]", "[INFO]", "[DEBUG]", "[TRACE]"
};

void Log_Print(LogLevel_e level, const char *file, uint32_t line,
		const char *fmt, ...) {

	char buffer[256];
	char *p = buffer;
	size_t remaining = sizeof(buffer);

	if(!Log_Append(&p, &remaining, "%s ", strLevels[level])) {
		return;
	}

#if LOG_INCLUDE_SOURCE
	if(!Log_Append(&p, &remaining, "%s:%lu ", file, (unsigned long)line)) {
		return;
	}
#endif

	if(!Log_Append(&p, &remaining, fmt)) {
		return;
	}

	 if(!Log_Append(&p, &remaining, "\r\n")) {
	 		return;
	 }

	 Log_Write(buffer, strnlen(buffer, sizeof(buffer)));
}

void Log_UpdateDMA(void) {
	ringBufferTxHead = (ringBufferTxHead + bytesWriting) % sizeof(ringBufferTx);

	bytesWriting = 0;
	uartDmaBusy = false;

	Log_StartDMA();
}

static void Log_Write(const char *buffer, int length) {
	Log_RingBufferWrite(buffer, length);

	if(!uartDmaBusy) {
		Log_StartDMA();
	}
}

void Log_StartDMA(void) {
	uint16_t len = Log_RingBufferGetContiguousReadLength();

	if(len == 0) {
		return;
	}

	uartDmaBusy = true;

	bytesWriting = len;
	HAL_UART_Transmit_DMA(&LOGGING_UART,
			(uint8_t *)Log_RingBufferGetReadPointer(), len);
}

void Log_RingBufferWrite(const char *buffer, int length) {

	for(int i = 0; i < length; i++) {
		ringBufferTx[ringBufferTxTail] = buffer[i];
		// Increment, wrap around if necessary
		ringBufferTxTail = (ringBufferTxTail + 1) % sizeof(ringBufferTx);

		if(ringBufferTxTail == ringBufferTxHead) {
			// Buffer full
			break;
		}
	}
}

static uint16_t Log_RingBufferGetContiguousReadLength(void) {
	if(ringBufferTxTail >= ringBufferTxHead) {
		return ringBufferTxTail - ringBufferTxHead;
	}
	else {
		return sizeof(ringBufferTx) - ringBufferTxHead;
	}
}

static bool Log_Append(char **p, size_t *remaining, const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);

	int written = vsnprintf(*p, *remaining, fmt, args);

	va_end(args);

	if(written < 0) {
		return false;
	}

	size_t advance = (written >= (int)*remaining) ?
			*remaining - 1 : (size_t)written;

	*p += advance;
	*remaining -= advance;

	return true;
}

char *Log_RingBufferGetReadPointer(void) {
	return ringBufferTx + ringBufferTxHead;
}
