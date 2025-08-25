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
#include "load_cell.h"
#include "peripherals/gpio.h"

#include <stdbool.h>

#include "stm32f4xx.h"

#define TIM_PITCH_F_CH TIM_CHANNEL_1
#define TIM_PITCH_R_CH TIM_CHANNEL_2
#define TIM_ROLL_F_CH TIM_CHANNEL_3
#define TIM_ROLL_R_CH TIM_CHANNEL_4

//#define ADC_PITCH_F_RANK ADC_INJECTED_RANK_1
//#define ADC_PITCH_R_RANK ADC_INJECTED_RANK_2

#define ADC_PITCH_LOAD_CELL_CHANNEL 0
#define ADC_PITCH_CURRENT_SENSOR_CHANNEL 0

extern Encoder_t pitchEncoder;
extern Encoder_t rollEncoder;

extern Motor_t pitchMotor;
extern Motor_t rollMotor;

extern GPIO_t gpioAccept;
extern GPIO_t gpioStatus;

extern LoadCell_t pitchLoadCell;

extern bool pitchEncoderUpdateFlag;

// PID tuner variables
extern float pidTunerSetPoint;
extern bool pidTunerUpdateFlag;

void BspInit(void);

void BspSetEStop(bool eStop);

// Interrupt call backs
void BspUARTRxUpdate(UART_HandleTypeDef *huart);
void BspUARTTxUpdate(UART_HandleTypeDef *huart);
void BspADCUpdate(ADC_HandleTypeDef *hadc);
void BspEXTIUpdate(uint16_t GPIO_Pin);
void BspSPIITUpdate(SPI_HandleTypeDef *hspi);
void BspTIMITUpdate(TIM_HandleTypeDef *htim);
void BspDumpCogData(float *cogMap, int cogMapLength, const char *title);
void BspUpdateDeviceData();
void BspUpdatePIDTuner(float actual, float data, PID_t *pid);

#endif /* INC_BSP_H_ */
