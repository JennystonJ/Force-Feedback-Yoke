/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim8;

extern SPI_HandleTypeDef hspi2;
extern SPI_HandleTypeDef hspi3;

extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define M2_DRIVER_NCS_Pin GPIO_PIN_3
#define M2_DRIVER_NCS_GPIO_Port GPIOE
#define M2_DRIVER_EN_Pin GPIO_PIN_4
#define M2_DRIVER_EN_GPIO_Port GPIOE
#define E2_NCS_Pin GPIO_PIN_5
#define E2_NCS_GPIO_Port GPIOE
#define M1_DRIVER_NCS_Pin GPIO_PIN_6
#define M1_DRIVER_NCS_GPIO_Port GPIOE
#define STATUS_LED_Pin GPIO_PIN_13
#define STATUS_LED_GPIO_Port GPIOC
#define E_STOP_Pin GPIO_PIN_0
#define E_STOP_GPIO_Port GPIOC
#define E_STOP_EXTI_IRQn EXTI0_IRQn
#define ADC1_NCS_Pin GPIO_PIN_3
#define ADC1_NCS_GPIO_Port GPIOC
#define M1_DRIVER_EN_Pin GPIO_PIN_14
#define M1_DRIVER_EN_GPIO_Port GPIOE
#define M2_NOCTW_Pin GPIO_PIN_12
#define M2_NOCTW_GPIO_Port GPIOB
#define M2_NFAULT_Pin GPIO_PIN_13
#define M2_NFAULT_GPIO_Port GPIOB
#define M1_NOCTW_Pin GPIO_PIN_8
#define M1_NOCTW_GPIO_Port GPIOD
#define M1_NFAULT_Pin GPIO_PIN_10
#define M1_NFAULT_GPIO_Port GPIOD
#define E1_NCS_Pin GPIO_PIN_9
#define E1_NCS_GPIO_Port GPIOC
#define PROBE_OUT_Pin GPIO_PIN_2
#define PROBE_OUT_GPIO_Port GPIOD
#define ADC1_DRDY_Pin GPIO_PIN_4
#define ADC1_DRDY_GPIO_Port GPIOD
#define ADC1_DRDY_EXTI_IRQn EXTI4_IRQn
#define ADC2_DRDY_Pin GPIO_PIN_7
#define ADC2_DRDY_GPIO_Port GPIOD
#define AUX_INT_Pin GPIO_PIN_5
#define AUX_INT_GPIO_Port GPIOB
#define ADC2_NCS_Pin GPIO_PIN_0
#define ADC2_NCS_GPIO_Port GPIOE
#define AUX_NCS_Pin GPIO_PIN_1
#define AUX_NCS_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
