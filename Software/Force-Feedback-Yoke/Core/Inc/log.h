/*
 * log.h
 *
 *  Created on: Jul 12, 2026
 *      Author: Jennyston
 */

#ifndef INC_LOG_H_
#define INC_LOG_H_

#include <stdint.h>
#include <stdbool.h>
#include "hardware_config.h"

#define LOG_INCLUDE_SOURCE 1

typedef enum LogLevel {
	LOG_LEVEL_NONE = 0,
	LOG_LEVEL_ERROR,
	LOG_LEVEL_WARN,
	LOG_LEVEL_INFO,
	LOG_LEVEL_DEBUG,
	LOG_LEVEL_TRACE
} LogLevel_e;

void Log_Print(LogLevel_e level, const char *file, uint32_t line,
		const char *fmt, ...);

void Log_StartDMA(void);

void Log_UpdateDMA(void);

#define LOG_ERROR(fmt, ...) \
    Log_Print(LOG_LEVEL_ERROR, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#define LOG_WARN(fmt, ...) \
    Log_Print(LOG_LEVEL_WARN, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#define LOG_INFO(fmt, ...) \
    Log_Print(LOG_LEVEL_INFO, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#define LOG_DEBUG(...) Log_Print(LOG_LEVEL_DEBUG, __FILE__, __LINE__, \
		__VA_ARGS__)
#else
#define LOG_DEBUG(...)
#endif

#define LOG_TRACE(fmt, ...) \
    Log_Print(LOG_LEVEL_TRACE, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#if LOG_LEVEL_ACTIVE >= LOG_LEVEL_DEBUG


#endif /* INC_LOG_H_ */
