/*
 * dwt.h
 *
 *  Created on: Jul 26, 2026
 *      Author: Jennyston
 */

#ifndef INC_PERIPHERALS_DWT_H_
#define INC_PERIPHERALS_DWT_H_

#include <stdint.h>

void DWT_Init(void);
uint32_t DWT_GetCount(void);
float DWT_ConvertCyclesToUs(uint32_t cycles);

#endif /* INC_PERIPHERALS_DWT_H_ */
