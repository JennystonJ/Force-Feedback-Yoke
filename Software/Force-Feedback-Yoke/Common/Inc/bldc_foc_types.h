/*
 * bldc_foc_types.h
 *
 *  Created on: Jul 8, 2025
 *      Author: Jennyston
 */

#ifndef INC_UTILITIES_BLDC_FOC_TYPES_H_
#define INC_UTILITIES_BLDC_FOC_TYPES_H_

typedef struct PhaseVoltages {
	float a;
	float b;
	float c;
} PhaseVoltages_t;

typedef struct PhaseCurrents {
	float a;
	float b;
	float c;
} PhaseCurrents_t;

typedef struct ABCurrent {
	float alpha;
	float beta;
} ABCurrent_t;

typedef struct DQCurrent {
	float d;
	float q;
} DQCurrent_t;

#endif /* INC_UTILITIES_BLDC_FOC_TYPES_H_ */
