/*
 * bsp_it.c
 *
 *  Created on: Jul 14, 2025
 *      Author: Jennyston
 */

#include "bsp_it.h"
#include "bsp.h"
#include "hardware_config.h"

void BspIT_TimIT(TIM_HandleTypeDef *htim) {
	if(htim == &FFB_CONTROL_LOOP_TIM) {
		Bsp_FFBControlLoopIT(FFB_CONTROL_LOOP_PERIOD_MS);
	}
}

void BspIT_ADCIT(ADC_HandleTypeDef *hadc) {
	if(hadc == &CURRENT_SENSE_PITCH_ADC) {
		Bsp_MotorControlLoopIT(&pitchMotor, &pitchEncoder, PITCH_ADC_ID,
				PITCH_MOTOR_CONTROL_LOOP_PERIOD_MS);
	}
	else if(hadc == &CURRENT_SENSE_ROLL_ADC) {
		Bsp_MotorControlLoopIT(&rollMotor, &rollEncoder, ROLL_ADC_ID,
				ROLL_MOTOR_CONTROL_LOOP_PERIOD_MS);
	}
	else {
		// Do nothing (invalid interrupt)
	}
}

void BspIT_ADCWatchDogIT(ADC_HandleTypeDef *hadc) {
	Bsp_ADCWatchDogIT(hadc);
}

void BspIT_EXTIIT(uint16_t gpioPin) {
	switch(gpioPin) {
		case E_STOP_Pin:
			Bsp_EStopIT();
			break;
		case ADC1_DRDY_Pin:
			Bsp_ADS1256DrdyUpdate(gpioPin);
			break;
		default:
			// Invalid, do nothing
			break;
	}
}

void BspIT_SPIIT(SPI_HandleTypeDef *hspi) {
	if(hspi == &hspi2) {
		Bsp_ADS1256Update();
	}
}

void BspIT_I2CIT(I2C_HandleTypeDef *hi2c) {

}

void BspIT_UARTTxCpltIT(UART_HandleTypeDef *huart) {
	if(huart == &SERIAL_DAQ_UART) {
		Bsp_SerialDAQTxIT();
	}
}

void BspIT_UARTRxCpltIT(UART_HandleTypeDef *huart) {
	if(huart == &SERIAL_DAQ_UART) {
		Bsp_SerialDAQRxIT();
	}
}
