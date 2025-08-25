/*
 * anti_cog.c
 *
 *  Created on: May 25, 2023
 *      Author: Jennyston
 */

#include "anti_cog.h"
#include <stdbool.h>
#include <stdio.h>

static uint32_t antiCogDtData[4][ENCODER_COUNT_PER_REV];

static int32_t antiCogData[ENCODER_COUNT_PER_REV] = {
		480,
		700,
		680,
		830,
		430,
		560,
		490,
		600,
		510,
		700,
		710,
		10,
		380,
		530,
		510,
		550,
		490,
		640,
		740,
		840,
		560,
		570,
		490,
		500,
		420,
		570,
		640,
		720,
		390,
		490,
		480,
		470,
		460,
		620,
		730,
		10,
		20,
		410,
		550,
		590,
		490,
		690,
		10,
		10,
		20,
		380,
		520,
		560,
		400,
		600,
		720,
		10,
		380,
		560,
		530,
		540,
		380,
		630,
		20,
		10,
		10,
		440,
		500,
		610,
		480,
		730,
		10,
		10,
		360,
		550,
		500,
		610,
		570,
		770,
		10,
		10,
		10,
		520,
		560,
		10,
		590,
		790,
		10,
		10,
		570,
		620,
		510,
		620,
		540,
		730,
		10,
		10,
		570,
		590,
		550,
		580,
		560,
		720,
		10,
		10,
		20,
		460,
		540,
		620,
		610,
		750,
		10,
		10,
		420,
		560,
		570,
		610,
		620,
		10,
		10,
		10,
		620,
		10,
		620,
		10,
		10,
		10,
		10,
		10,
		10,
		420,
		550,
		10,
		30,
		730,
		10,
		10,
		30,
		550,
		10,
		630,
		590,
		10,
		10,
		10,
		10,
		530,
		10,
		580,
		550,
		760,
		10,
		10,
		390,
		590,
		580,
		690,
		10,
		10,
		10,
		10,
		540,
		10,
		480,
		620,
		570,
		770,
		10,
		10,
		10,
		470,
		520,
		630,
		530,
		740,
		10,
		10,
		10,
		440,
		490,
		560,
		560,
		710,
		10,
		10,
		510,
		590,
		530,
		540,
		550,
		680,
		10,
		10,
		20,
		390,
		510,
		590,
		590,
		730,
		10,
		10,
		550,
		10,
		620,
		10,
		10,
		10,
		10,
		10,
		10,
		370,
		510,
		590,
		500,
		660,
		10,
		10,
		390,
		590,
		570,
		620,
		570,
		790,
		10,
		10,
		10,
		570,
		10,
		570,
		530,
		760,
		10,
		10,
		440,
		600,
		530,
		620,
		550,
		760,
		10,
		10,
		510,
		640,
		10,
		550,
		550,
		750,
		10,
		10,
		480,
		610,
		550,
		630,
		490,
		730,
		10,
		10,
		390,
		520,
		480,
		530,
		500,
		650,
		750,
		10,
		490,
		580,
		530,
		530,
		450,
		620,
		710,
		10,
		460,
		410,
		500,
		510,
		530,
		680,
		10,
		10,
		10,
		430,
		570,
		630,
		540,
		750,
		10,
		10,
		10,
		360,
		500,
		590,
		470,
		640,
		760,
		10,
		370,
		570,
		530,
		570,
		390,
		670,
		750,
		10,
		490,
		640,
		550,
		630,
		350,
		650,
		670,
		770,
		390,
		520,
		450,
		510,
		440,
		650,
		700,
		10,
		490,
		600,
		500,
		560,
		470,
		690,
		700,
		10,
		480,
		600,
		510,
		600,
		460,
		670,
		670,
		10,
		360,
		480,
		430,
		470,
		410,
		570,
		680,
		810,
		550,
		560,
		490,
		520,
		310,
		540,
		630,
		710,
		400,
		490,
		480,
		470,
		390,
		590,
		720,
		10,
		590,
		630,
		600,
		270,
		460,
		620,
		720,
		10,
		510,
		610,
		580,
		580,
		400,
		590,
		700,
		10,
		410,
		580,
		520,
		570,
		300,
		580,
		660,
		830,
		570,
		650,
		540,
		630,
		320,
		650,
		690,
		790,
		470,
		550,
		500,
		540,
		500,
		730,
		10,
		10,
		10,
		430,
		500,
		600,
		510,
		750,
		10,
		10,
		520,
		640,
		570,
		640,
		480,
		720,
		10,
		10,
		420,
		560,
		500,
		570,
		510,
		680,
		10,
		10,
		640,
		640,
		490,
		590,
		530,
		680,
		10,
		10,
		10,
		360,
		500,
		560,
		580,
		740,
		10,
		10,
		10,
		590,
		680,
		680,
		660,
		10,
		10,
		10,
		10,
		460,
		620,
		660,
		530,
		750,
		10,
		10,
		470,
		690,
		660,
		700,
		530,
		810,
		10,
		10,
		10,
		570,
		630,
		10,
		570,
		820,
		10,
		10,
		420,
		640,
		590,
		710,
		650,
		880,
		10,
		10,
		10,
		620,
		20,
		660,
		650,
		880,
		10,
		10,
		10,
		590,
		650,
		10,
		20,
		890,
		10,
		10,
		640,
		10,
		420,
		630,
		620,
		790,
		10,
		10,
		10,
		380,
		490,
		570,
		600,
		720,
		20,
		10,
		480,
		580,
		590,
		630,
		650,
		20,
		10,
		10,
		10,
		680,
		10,
		10,
		10,
		10,
		10,
		10,
		610,
		10,
		10,
		680,
		650,
		800,
		10,
		10,
		460,
		670,
		640,
		680,
		610,
		840,
		10,
		10,
		650,
		10,
		10,
		600,
		570,
		820,
		10,
		10,
		510,
		640,
		580,
		720,
		650,
		10,
		10,
		10,
		550,
		720,
		10,
		700,
		670,
		910,
		10,
		10,
		650,
		10,
		10,
		720,
		680,
		10,
		10,
		10,
		10,
		490,
		560,
		640,
		630,
		780,
		10,
		10,
		640,
		500,
		590,
		620,
		600,
		740,
		10,
		10,
		490,
		600,
		590,
		620,
		640,
		800,
		10,
		10,
		10,
		510,
		660,
		690,
		690,
		10,
		10,
		10,
		660,
		10,
		10,
		630,
		600,
		760,
		10,
		10,
		520,
		680,
		620,
		660,
		590,
		810,
		10,
		10,
		10,
		520,
		580,
		700,
		530,
		820,
		10,
		10,
		490,
		630,
		570,
		700,
		630,
		840,
		10,
		10,
		510,
		690,
		610,
		650,
		620,
		840,
		10,
		10,
		570,
		680,
		610,
		720,
		640,
		850,
		10,
		10,
		460,
		630,
		610,
		670,
		670,
		830,
		10,
		10,
		550,
		670,
		630,
		650,
		620,
		770,
		10,
		10,
		490,
		610,
		600,
		670,
		670,
		840,
		10,
		10,
		10,
		590,
		710,
		820,
		10,
		10,
		10,
		10,
		10,
		450,
		600,
		730,
		690,
		840,
		10,
		10,
		460,
		670,
		630,
		760,
		670,
		920,
		10,
		10,
		690,
		10,
		10,
		680,
		670,
		900,
		10,
		10,
		500,
		660,
		600,
		790,
		720,
		960,
		10,
		10,
		500,
		710,
		670,
		790,
		720,
		950,
		10,
		20,
		10,
		620,
		690,
		10,
		10,
		960,
		10,
		10,
		10,
		550,
		640,
		730,
		720,
		870,
		10,
		10,
		540,
		680,
		670,
		720,
		680,
		810,
		900,
		10,
		490,
		630,
		640,
		720,
		720,
		890,
		10,
		10,
		10,
		490,
		640,
		860,
		840,
		10,
		10,
		10,
		560,
		730,
		750,
		800,
		740,
		880,
		10,
		10,
		540,
		720,
		670,
		820,
		720,
		950,
		10,
		10,
		670,
		20,
		10,
		780,
		750,
		980,
		10,
		10,
		570,
		740,
		690,
		880,
		780,
		10,
		10,
		10,
		600,
		790,
		10,
		10,
};

//static void AntiCogSetPosition(AntiCog_t *antiCog, int32_t targetPosition);
static int32_t AntiCogFindMinPower(AntiCog_t *antiCog, int32_t position);

void AntiCogInit(AntiCog_t *antiCog, MotorController_t *controller,
		PID_t *pid) {
	antiCog->controller = controller;
	antiCog->pid = pid;

	for(int i = 0; i < ENCODER_COUNT_PER_REV; i++) {
		antiCog->calForward[i] = antiCogData[i];
	}
}

void AntiCogRun(AntiCog_t *antiCog) {

	MotorControllerSetPosition(antiCog->controller, ENCODER_COUNT_PER_REV);
//
//	//Start at initial position
	MotorControllerSetPosition(antiCog->controller, 0);

	/*
	 * Go through each encoder count and measure minimum power required to
	 * advance to next count.
	 */
	for(int i = 0; i < ENCODER_COUNT_PER_REV; i++) {
		antiCog->calForward[i] = AntiCogFindMinPower(antiCog, i);
		printf("%d,\r\n", (int)(antiCog->calForward[i]));
	}

	/*
	 * Test calibration values
	 */
//	for(int i = 0; i < ENCODER_COUNT_PER_REV; i++) {
//		MotorControllerSetPosition(antiCog->controller, i);
//		MotorControllerSetPower(antiCog->controller,
//				AntiCogGetCalAt(antiCog, i));
//		HAL_Delay(800);
//		while(1) {
//			HAL_Delay(8);
//			if(MotorControllerGetPosition(antiCog->controller) == i) {
//				antiCog->calForward[i] += 10;
//			}
//			else {
//				break;
//			}
//		}
//	}

	printf("\r\nCalibration Results:\r\n");
	for(int i = 0; i < ENCODER_COUNT_PER_REV; i++) {
		printf("%d,\r\n", (int)AntiCogGetCalAt(antiCog, i));
	}

//	//get motor up to speed
//	MotorControllerSetPower(antiCog->controller, 1250);
//	while(MotorControllerGetPosition(antiCog->controller) !=
//			ENCODER_COUNT_PER_REV*3){
//		//do nothing
//	}
//
//	for(int dataSet = 0; dataSet < 4; dataSet++) {
//		for(int i = 0; i < ENCODER_COUNT_PER_REV; i++) {
//			while(MotorControllerGetPosition(antiCog->controller) %
//					ENCODER_COUNT_PER_REV !=
//							i){
//				//do nothing
//			}
//			//TODO: implement getter function for prevDt
//			antiCogDtData[dataSet][i] =
//					antiCog->controller->init.encoder->prevDt;
//		}
//	}
//
//	MotorControllerSetPower(antiCog->controller, 0);
//
//	printf("*** Anti-cog Speed Data ***\r\n");
//	//Averaging
//	for(int i = 0; i < ENCODER_COUNT_PER_REV; i++) {
//		uint32_t average = 0;
//		for(int dataSet = 0; dataSet < 4; dataSet++) {
//			average += antiCogDtData[dataSet][i];
//		}
//		average /= 4;
//		printf("%d,\r\n", (int)(average));
//	}

//	for(int i = 0; i < ENCODER_COUNT_PER_REV; i++) {
//		for(int dataSet = 0; dataSet < 4; dataSet++) {
//			printf("%d,", antiCogDrDate[dataSet][i]);
//		}
//		printf("\r\n");
//	}

	//AntiCogSetPosition(antiCog, 0);
}

void AntiCogTest(AntiCog_t *antiCog) {
	MotorControllerSetPosition(antiCog->controller, 0);

	while(1) {
		int32_t currentPosition = MotorControllerGetPosition(
				antiCog->controller);
		int32_t motorPower = AntiCogGetCalAt(antiCog,
				currentPosition);

		MotorControllerSetPower(antiCog->controller, motorPower);
		HAL_Delay(1);
	}

//	while(1) {
//		int32_t currentPosition = MotorControllerGetPosition(
//				antiCog->controller);
//		int32_t motorPower = AntiCogGetCalAt(antiCog,
//				currentPosition % ENCODER_COUNT_PER_REV) * 100 - 300;
//
//		//TODO: collect data to verify calibration
//
//		MotorControllerSetPower(antiCog->controller, motorPower);
//		HAL_Delay(1);
//	}

//	//Complete rotation
//	bool rotationComplete = false;
//	while(!rotationComplete) {
//		int32_t currentPosition = MotorControllerGetPosition(
//				antiCog->controller);
//
//		if(0 <= currentPosition && currentPosition < ENCODER_COUNT_PER_REV) {
//			int32_t motorPower = antiCog->calForward[currentPosition] +
//					1600;
//			if(motorPower >= 2400) {
//				motorPower = 2400-1;
//			}
//
//			MotorControllerSetPower(antiCog->controller, motorPower);
//		}
//		else {
//			rotationComplete = true;
//		}
//	}

//	MotorControllerSetPosition(antiCog->controller, antiCog->pid, 0);
}

uint32_t AntiCogGetCalAt(AntiCog_t *antiCog, uint32_t index) {
	return antiCog->calForward[index % ENCODER_COUNT_PER_REV];
}

//TODO: Remove
//static void AntiCogSetPosition(AntiCog_t *antiCog, int32_t targetPosition) {
//
//	bool targetReached = false;
//	int steadyCount = 0;
//	while(!targetReached) {
//
//		/*
//		 * Calculate motor power to advance to target position based on current
//		 * position.
//		 */
//		int32_t currentPosition = RotaryEncGetCount(antiCog->encoder);
//		int32_t motorPower = ComputePID(antiCog->pid, targetPosition,
//				currentPosition);
//
//
//		//Minimum PID motor power
//		if(motorPower < 0) {
//			motorPower -= 100;
//		}
//		else if(motorPower > 0) {
//			motorPower += 100;
//		}
//
//		MotorSetPower(antiCog->motor, motorPower);
//
//		if(RotaryEncGetCount(antiCog->encoder) == targetPosition) {
//
//			steadyCount++;
//
//			//Target position is reached when encoder count is stable
//			if(steadyCount == 50) {
//				MotorSetPower(antiCog->motor, 0);
//
//				//terminate loop
//				targetReached = true;
//			}
//		}
//		else {
//
//			/*
//			 * Reset steady count when encoder count does not match target
//			 * position
//			 */
//			steadyCount = 0;
//		}
//
//		HAL_Delay(10);
//
//	}
//
//}

static int32_t AntiCogFindMinPower(AntiCog_t *antiCog, int32_t position) {
	MotorControllerSetPosition(antiCog->controller, position);

	//ramp power until motor moves to next encoder position
	int32_t motorPower = 0;
	do {
		motorPower += 10;
		MotorControllerSetPower(antiCog->controller, motorPower);
		HAL_Delay(8);
	} while (motorPower < 2400 &&
			MotorControllerGetPosition(antiCog->controller) == position);

	return motorPower;
}
