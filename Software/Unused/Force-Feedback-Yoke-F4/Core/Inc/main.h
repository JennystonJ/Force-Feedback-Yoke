/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
extern UART_HandleTypeDef huart1;

extern ADC_HandleTypeDef hadc1;

extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c3;

extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim10;
extern TIM_HandleTypeDef htim11;

//extern ADC_HandleTypeDef hadc1;

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
#define STATUS_LED_Pin GPIO_PIN_13
#define STATUS_LED_GPIO_Port GPIOC
#define BUTTON_ACCEPT_Pin GPIO_PIN_0
#define BUTTON_ACCEPT_GPIO_Port GPIOA
#define PITCH_CURRENT_Pin GPIO_PIN_4
#define PITCH_CURRENT_GPIO_Port GPIOA
#define MOTOR_PITCH_EN_Pin GPIO_PIN_5
#define MOTOR_PITCH_EN_GPIO_Port GPIOA
#define MOTOR_PITCH_F_PWM_Pin GPIO_PIN_6
#define MOTOR_PITCH_F_PWM_GPIO_Port GPIOA
#define MOTOR_PITCH_R_PWM_Pin GPIO_PIN_7
#define MOTOR_PITCH_R_PWM_GPIO_Port GPIOA
#define MOTOR_ROLL_F_PWM_Pin GPIO_PIN_0
#define MOTOR_ROLL_F_PWM_GPIO_Port GPIOB
#define MOTOR_ROLL_R_PWM_Pin GPIO_PIN_1
#define MOTOR_ROLL_R_PWM_GPIO_Port GPIOB
#define MOTOR_ROLL_EN_Pin GPIO_PIN_2
#define MOTOR_ROLL_EN_GPIO_Port GPIOB
#define PROBE_OUT_Pin GPIO_PIN_10
#define PROBE_OUT_GPIO_Port GPIOB
#define ADC_CS_Pin GPIO_PIN_12
#define ADC_CS_GPIO_Port GPIOB
#define ADC_DRDY_Pin GPIO_PIN_8
#define ADC_DRDY_GPIO_Port GPIOA
#define ADC_DRDY_EXTI_IRQn EXTI9_5_IRQn
#define nCS1_1_Pin GPIO_PIN_15
#define nCS1_1_GPIO_Port GPIOA
#define nCS1_3_Pin GPIO_PIN_8
#define nCS1_3_GPIO_Port GPIOB
#define nCS1_2_Pin GPIO_PIN_9
#define nCS1_2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
