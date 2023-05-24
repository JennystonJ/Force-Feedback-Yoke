/*
 * utilities.h
 *
 *  Created on: May 19, 2023
 *      Author: Jennyston
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

int32_t Constrain(int32_t value, int32_t min, int32_t max);
int32_t UnwrapAtThreshold16(uint16_t currentCount, uint16_t newCount,
		uint16_t threshold);
int32_t Abs(int32_t x);

#ifdef __cplusplus
}
#endif

#endif /* UTILITIES_H_ */
