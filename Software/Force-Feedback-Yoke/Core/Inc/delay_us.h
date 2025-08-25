/*
 * delay_us.h
 *
 *  Created on: Aug 3, 2025
 *      Author: Jennyston
 */

#ifndef INC_DELAY_US_H_
#define INC_DELAY_US_H_

#include <stm32h7xx_hal.h>

void DelayUs_Init(TIM_HandleTypeDef *htimUs);
void DelayUs_Delay(uint16_t microseconds);

#endif /* INC_DELAY_US_H_ */
