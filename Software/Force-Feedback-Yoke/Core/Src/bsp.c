/*
 * bsp.c
 *
 *  Created on: Jul 13, 2024
 *      Author: Jennyston
 */

#include "bsp.h"
#include "main.h"

#include "devices/as5600.h"
#include "devices/as5600_interface.h"
#include "devices/bts7960.h"
#include "devices/bts7960_interface.h"

// External variables
Encoder_t pitchEncoder;
Encoder_t rollEncoder;

Motor_t pitchMotor;
Motor_t rollMotor;

GPIO_t gpioAccept;

// Private variables
AS5600_t pitchAS5600;
AS5600_t rollAS5600;

BTS7960_t pitchDriver;
BTS7960_t rollDriver;


// Private function prototypes
void SetupEncoders(void);
void SetupMotors(void);
void SetupButtons(void);

void BspInit(void) {
	SetupEncoders();
	SetupMotors();
	SetupButtons();

	// --- Timer setup ----
	// Motor PWM timer
	HAL_TIM_Base_Start_IT(&htim3);
	// Update timer
	HAL_TIM_Base_Start_IT(&htim6);
	// Control loop timer
	HAL_TIM_Base_Start_IT(&htim7);
}

void SetupEncoders(void) {
	// Pitch
	AS5600Init(&pitchAS5600, &hi2c1);
	EncoderInterface_t pitchEncoderI;
	AS5600InterfaceInit(&pitchEncoderI, &pitchAS5600);
	EncoderInit(&pitchEncoder, pitchEncoderI);

	// Roll
	AS5600Init(&rollAS5600, &hi2c2);
	EncoderInterface_t rollEncoderI;
	AS5600InterfaceInit(&rollEncoderI, &rollAS5600);
	EncoderInit(&rollEncoder, rollEncoderI);
}

void  SetupMotors(void) {
	// Pitch
	// Initialize forward/reverse enable GPIOs
	GPIO_t forwardPitchEnGpio;
	GPIO_t reversePitchEnGpio;

	GPIOInit(&forwardPitchEnGpio,
			MOTOR_PITCH_F_EN_GPIO_Port, MOTOR_PITCH_F_EN_Pin);
	GPIOInit(&reversePitchEnGpio,
			MOTOR_PITCH_R_EN_GPIO_Port, MOTOR_PITCH_R_EN_Pin);

	// Initialize driver
	BTS7960Init(&pitchDriver, forwardPitchEnGpio, reversePitchEnGpio, &htim3,
			TIM_PITCH_F_CH, TIM_PITCH_R_CH);

	// Set up interface
	MotorInterface_t pitchMotorI;
	BTS7960InterfaceInit(&pitchMotorI, &pitchDriver);

	// Initialize motor
	MotorInit(&pitchMotor, pitchMotorI);

	// Roll
	// Initialize forward/reverse enable GPIOs
	GPIO_t forwardRollEnGpio;
	GPIO_t reverseRollEnGpio;

	GPIOInit(&forwardRollEnGpio,
			MOTOR_ROLL_F_EN_GPIO_Port, MOTOR_ROLL_F_EN_Pin);
	GPIOInit(&reverseRollEnGpio,
			MOTOR_ROLL_R_EN_GPIO_Port, MOTOR_ROLL_R_EN_Pin);

	// Initialize driver
	BTS7960Init(&rollDriver, forwardRollEnGpio, reverseRollEnGpio, &htim3,
			TIM_ROLL_F_CH, TIM_ROLL_R_CH);

	// Set up interface
	MotorInterface_t rollMotorI;
	BTS7960InterfaceInit(&rollMotorI, &rollDriver);

	// Initialize motor
	MotorInit(&rollMotor, rollMotorI);
}

void SetupButtons(void) {
	GPIOInit(&gpioAccept, BUTTON_ACCEPT_GPIO_Port, BUTTON_ACCEPT_Pin);
}
