/*
 * motor_logger.c
 *
 *  Created on: Jun 2, 2023
 *      Author: Jennyston
 */

#include <stdio.h>
#include <testing/motor_logger.h>

void MotorLoggerInit(MotorLogger_t *mLogger, MotorController_t *controller) {
	mLogger->controller = controller;
}

void MotorLoggerVRun(MotorLogger_t *mLogger, int32_t maxPower,
		int32_t rampStep) {

	int32_t currentPower = 0;
	while(currentPower < maxPower) {
		MotorControllerSetPower(mLogger->controller, currentPower);

		//wait before measuring speed
		HAL_Delay(3000 - currentPower);

//		int32_t prevEncCount = RotaryEncGetCount(
//				mLogger->controller->init.encoder);
//
//		HAL_Delay(4000 - currentPower);
//
//		//calculate speed
//		float speed = (RotaryEncGetCount(
//				mLogger->controller->init.encoder) - prevEncCount)/
//						((4000 - currentPower)/1000.0f);

		float speed = MotorControllerGetSpeed(mLogger->controller);

		//log power and speed
		printf("%d,%f,\r\n", (int)currentPower, speed);

		currentPower += rampStep;
	}

	MotorControllerSetPower(mLogger->controller, 0);
}

void MotorLoggerARun(MotorLogger_t *mLogger, int32_t power, int32_t timeStep) {

	float dataPoints[MOTOR_LOGGER_A_MAX_POINTS];
	int dataPointIndex = 0;

	MotorControllerSetPower(mLogger->controller, power);
	float accel;
	float prevSpeed = 0.0f;
	do {

		float currentSpeed = MotorControllerGetSpeed(mLogger->controller);
		//accel = (currentSpeed - prevSpeed) / 0.005f;

		HAL_Delay(5);

		//prevSpeed = currentSpeed;


//		int32_t prevEncCount1 = RotaryEncGetCount(
//				mLogger->controller->init.encoder);
//		HAL_Delay(10);
//		//calculate speed
//		float speed1 = (RotaryEncGetCount(
//				mLogger->controller->init.encoder) - prevEncCount1)/0.01;
//
//		HAL_Delay(10);
//
//		int32_t prevEncCount2 = RotaryEncGetCount(
//				mLogger->controller->init.encoder);
//		HAL_Delay(10);
//		//calculate speed
//		float speed2 = (RotaryEncGetCount(
//				mLogger->controller->init.encoder) - prevEncCount2)/0.01;
//
//		accel = (speed2 - speed1) / 0.03;

		dataPoints[dataPointIndex] = currentSpeed;
		dataPointIndex++;
	} while(dataPointIndex <
			MOTOR_LOGGER_A_MAX_POINTS);

	for(int i = 0; i < dataPointIndex; i++) {
		printf("%f,%f,\r\n", (i * 0.005f), dataPoints[i]);
	}
}


