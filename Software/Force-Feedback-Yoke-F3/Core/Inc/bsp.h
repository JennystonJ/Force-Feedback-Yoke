/*
 * bsp.h
 *
 *  Created on: Jul 13, 2024
 *      Author: Jennyston
 */

#ifndef INC_BSP_H_
#define INC_BSP_H_

#include "encoder.h"
#include "motor.h"
#include "button.h"
#include "peripherals/gpio.h"

#include "stm32f3xx.h"

#define TIM_PITCH_F_CH TIM_CHANNEL_4
#define TIM_PITCH_R_CH TIM_CHANNEL_3
#define TIM_ROLL_F_CH TIM_CHANNEL_2
#define TIM_ROLL_R_CH TIM_CHANNEL_1

extern Encoder_t pitchEncoder;
extern Encoder_t rollEncoder;

extern Motor_t pitchMotor;
extern Motor_t rollMotor;

extern GPIO_t gpioAccept;

void BspInit(void);

#endif /* INC_BSP_H_ */
