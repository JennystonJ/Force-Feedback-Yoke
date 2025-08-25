/*
 * anti_cog.h
 *
 *  Created on: May 30, 2025
 *      Author: Jennyston
 */

#ifndef INC_ANTI_COG_H_
#define INC_ANTI_COG_H_

#include "encoder.h"
#include "pid.h"
#include <stdint.h>
#include <stdbool.h>
#include "utilities/filters.h"

#define ANTI_COG_CAL_POS_COUNT_TOLERANCE 150.0f
#define ANTI_COG_CAL_POS_HOLD_TIME 500000

#define ANTI_COG_CALIBRATION_SPEED 16.5f
#define ANTI_COG_CALIBRATION_BUFFER_SIZE 16

typedef struct AntiCogCalibrationBuffer {
	uint16_t counts[512];
	float *cogMap;
	int cogMapLength;
	float data[ANTI_COG_CALIBRATION_BUFFER_SIZE];
	uint8_t batch;
	uint16_t binSize;
} AntiCogCalibrationBuffer_t;

typedef struct AntiCog {
	struct {
		Encoder_t *encoder;
//		Motor_t *motor; // used only for calibration
	} hardware;

	const float *cogMap;
	int cogMapLength;
	float cogMapStepsPerCount;

	float gain;

	struct {
		PID_t pidPosition;
		PID_t pidSpeed;
		float velocityDampingCo;
		LowPass_t lpfSpeed;
		LowPass_t lpfError;
		LowPass_t lpfOutput;
		LowPass_t lpfDerivative;
		int currentCogMapIndex;
		bool calibrating;
		int timeHeld;
		float speed;
		bool speedLocked;
		AntiCogCalibrationBuffer_t calibrationBuffer;
	} calibration;
} AntiCog_t;

void AntiCogInit(AntiCog_t *antiCog, Encoder_t *encoder,
		const float *cogMap, int cogMapLength);
float AntiCogCalc(AntiCog_t *antiCog);
//void AntiCogStartCalibration(AntiCog_t *antiCog, Motor_t *motor, bool reverse,
//		float *cogMap, int cogMapLength);
void AntiCogCalibrationUpdate(AntiCog_t *antiCog, int dt);
void AntiCogCalibrationUpdate2(AntiCog_t *antiCog, int deltaTimeUs);
bool AntiCogIsCalibration(AntiCog_t *antiCog);

#endif /* INC_ANTI_COG_H_ */
