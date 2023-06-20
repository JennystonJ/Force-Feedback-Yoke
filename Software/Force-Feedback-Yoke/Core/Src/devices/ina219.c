/*
 * ina219.c
 *
 *  Created on: May 24, 2023
 *      Author: Jennyston
 */

#include "devices/ina219.h"
#include "devices/ina219_reg.h"
#include <stdint.h>

//private function forward declarations
static void Ina219WriteRegister(Ina219_t *cSense, Ina219Reg reg, uint16_t data);
static uint16_t Ina219ReadRegister(Ina219_t *cSense, Ina219Reg reg);

void CurrentSenseInit(Ina219_t *cSense, I2C_HandleTypeDef *hi2c) {
	cSense->hi2c = hi2c;

	//uint16_t test = Ina219ReadRegister(cSense, INA219_CONFIG);

	//Soft reset INA219
	Ina219WriteRegister(cSense, INA219_CONFIG, 0b1000000000000000);
	HAL_Delay(5);
	/*
	 * Bus Voltage Range: 16V
	 * PGA: +/- 320mV
	 * BADC: 12-bit
	 * SADC: 12-bit
	 * Operating Mode: Shunt and bus, continuous
	 */
//	Ina219WriteRegister(cSense, INA219_CONFIG, 0b0001100110011111);

	/*
	 * Bus Voltage Range: 16V
	 * PGA: +/- 320mV
	 * BADC: 12-bit
	 * SADC: 2 samples
	 * Operating Mode: Shunt and bus, continuous
	 */
	Ina219WriteRegister(cSense, INA219_CONFIG, 0b0001100111001111);

	//Calibration
	Ina219WriteRegister(cSense, INA219_CALIBRATION, 4096);

}

float CurrentSenseGetCurrent(Ina219_t *cSense) {
	//Ina219WriteRegister(cSense, INA219_CONFIG, 0b1000000000000000);

	//Ensure sensor calibration did not reset as recommended by Adafruit
	//Ina219WriteRegister(cSense, INA219_CALIBRATION, 4096);

	//Ina219WriteRegister(cSense, INA219_CONFIG, 0b0001100110011111);
	Ina219WriteRegister(cSense, INA219_CONFIG, 0b0001100111001111);


	//Calibration
	Ina219WriteRegister(cSense, INA219_CALIBRATION, 4096);

	uint16_t rawData = Ina219ReadRegister(cSense, INA219_CURRENT);
	int16_t data = *(int16_t *)&rawData;
	return data * 0.0001f;
}

static void Ina219WriteRegister(Ina219_t *cSense, Ina219Reg reg,
		uint16_t data) {
	//Prepare data for transmit
	const uint8_t TX_DATA_LENGTH = 3;
	uint8_t txData[TX_DATA_LENGTH];
	txData[0] = (uint8_t)reg;
	txData[1] = (uint8_t)((data >> 8) & 0xFF);
	txData[2] = (uint8_t)(data & 0xFF);

	//Transmit register address with provided data
	HAL_I2C_Master_Transmit(cSense->hi2c, INA219_ADDR, txData, TX_DATA_LENGTH,
			HAL_MAX_DELAY);
}

static uint16_t Ina219ReadRegister(Ina219_t *cSense, Ina219Reg reg) {
	const int RX_DATA_LENGTH = 2;
	uint8_t buffer[RX_DATA_LENGTH];
	HAL_I2C_Master_Transmit(cSense->hi2c, INA219_ADDR, (uint8_t *)&reg, 1,
			HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(cSense->hi2c, INA219_ADDR, buffer, RX_DATA_LENGTH,
			HAL_MAX_DELAY);

	//Convert 2*8-bit data to 16-bit
	uint16_t data = (((uint16_t)buffer[0])<< 8) | (buffer[1] & 0xFF);

	return data;
}
