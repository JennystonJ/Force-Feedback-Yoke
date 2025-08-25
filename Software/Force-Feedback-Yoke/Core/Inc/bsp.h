/*
 * bsp.h
 *
 *  Created on: Jul 4, 2025
 *      Author: Jennyston
 */

#ifndef INC_BSP_H_
#define INC_BSP_H_

#include "main.h"
#include "encoder.h"
#include "bldc_driver.h"
#include "bldc_motor.h"
#include "motor.h"
#include "load_cell.h"
#include "peripherals/gpio.h"
#include <stdbool.h>
#include <stdint.h>
#include "devices/serial_daq.h"

// External variables
extern bool bspInitialized;

extern BLDCDriver_t pitchDriver;
extern BLDCMotor_t pitchBLDCMotor;
extern Motor_t pitchMotor;
extern Encoder_t pitchEncoder;
extern LoadCell_t pitchLoadCell;

extern Encoder_t rollEncoder;

extern GPIO_t statusLedGpio;
extern GPIO_t probeGpio;
extern GPIO_t eStopGpio;
extern SerialDAQ_t daq;

void Bsp_Init(void);

void Bsp_EStopIT(void);
void Bsp_MotorControlLoopIT(Motor_t *motor, Encoder_t *encoder,
		float deltaTimeMs);
void Bsp_FFBControlLoopIT(float deltaTimeMs);
void Bsp_SerialDAQTxIT(void);
void Bsp_SerialDAQRxIT(void);
void Bsp_ADCWatchDogIT(ADC_HandleTypeDef *hadc);

void Bsp_ADS1256DrdyUpdate(uint16_t pin);
void Bsp_ADS1256Update(void);

void Bsp_RegisterSerialDAQTxCallback(void (*SerialDAQTxIT)
		(SerialDAQ_t *serialDaq)) ;
void Bsp_RegisterSerialDAQRxCallback(void (*SerialDAQRxIT)
		(SerialDAQ_t *serialDaq));
void Bsp_RegisterMotorControlLoopITCallback(void (*MotorControlLoopIT)
		(Motor_t *motor, Encoder_t *encoder, float deltaTimeMs));
void Bsp_RegisterFFBControlLoopITCallback(void (*FFBControlLoopIT)
		(float deltaTimeMs));
void Bsp_RegisterLoadCellReadCpltCallback(void (*LoadCellReadCpltIT));

void Bsp_ADCUpdate(void);

uint32_t Bsp_GetTick(void);

#endif /* INC_BSP_H_ */
