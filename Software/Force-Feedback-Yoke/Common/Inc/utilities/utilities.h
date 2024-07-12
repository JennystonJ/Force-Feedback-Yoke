/*
 * utilities.h
 *
 *  Created on: May 19, 2023
 *      Author: Jennyston
 */

#ifndef INC_UTILITIES_UTILITIES_H_
#define INC_UTILITIES_UTILITIES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

int32_t Map(int32_t in, int32_t inMin, int32_t inMax, int32_t outMin,
		int32_t outMax);
int32_t Constrain(int32_t value, int32_t min, int32_t max);
float ConstrainFloat(float value, float min, float max);
int32_t Abs(int32_t x);
int32_t Min(int32_t a, int32_t b);
int32_t Max(int32_t a, int32_t b);

#ifdef __cplusplus
}
#endif

#endif /* INC_UTILITIES_UTILITIES_H_ */
