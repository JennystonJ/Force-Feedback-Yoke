/*
 * bsp_it.h
 *
 *  Created on: Jul 14, 2025
 *      Author: Jennyston
 */

#ifndef INC_BSP_IT_H_
#define INC_BSP_IT_H_

#include <stm32h7xx_hal.h>

void BspIT_TimIT(TIM_HandleTypeDef *htim);
void BspIT_ADCIT(ADC_HandleTypeDef *hadc);
void BspIT_ADCWatchDogIT(ADC_HandleTypeDef *hadc);
void BspIT_EXTIIT(uint16_t gpioPin);
void BspIT_SPIIT(SPI_HandleTypeDef *hspi);
void BspIT_I2CIT(I2C_HandleTypeDef *hi2c);

void BspIT_UARTTxCpltIT(UART_HandleTypeDef *huart);
void BspIT_UARTRxCpltIT(UART_HandleTypeDef *huart);

#endif /* INC_BSP_IT_H_ */
