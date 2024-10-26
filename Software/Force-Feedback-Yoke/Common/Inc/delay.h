/*
 * delay.h
 *
 *  Created on: Jul 25, 2024
 *      Author: Jennyston
 */

#ifndef INC_DELAY_H_
#define INC_DELAY_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

void delayMsInit(void (*delayMs_func)(uint32_t milliseconds));
void delayMs(uint32_t milliseconds);

#ifdef __cplusplus
}
#endif

#endif /* INC_DELAY_H_ */
