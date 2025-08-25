/*
 * bldc_foc_math.h
 *
 *  Created on: Jul 8, 2025
 *      Author: Jennyston
 */

#ifndef INC_BLDC_FOC_MATH_H_
#define INC_BLDC_FOC_MATH_H_

#include "bldc_foc_types.h"

DQCurrent_t FOCMath_CalcDQCurrent(ABCurrent_t abCurrent, float angleElec);
ABCurrent_t FOCMath_CalcABCurrent(PhaseCurrents_t currents);
PhaseVoltages_t FOCMath_CalcPhaseVoltages(float ud, float uq, float angleElec,
		float busVoltage);


#endif /* INC_BLDC_FOC_MATH_H_ */
