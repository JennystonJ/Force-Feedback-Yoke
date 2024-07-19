/*
 * force_feedback_periodic.h
 *
 *  Created on: May 27, 2023
 *      Author: Jennyston
 */

#ifndef FORCE_FEEDBACK_PERIODIC_H_
#define FORCE_FEEDBACK_PERIODIC_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct FFBPeriodic {
	float amplitude;
	float frequency;
	float offset;
	long time;
} FFBPeriodicParam_t;

/*
 * Initializes force feedback periodic structure.
 * parameter peri: pointer to force feedback periodic structure to be
 * 		initialized.
 * parameter amplitude: amplitude of periodic effect.
 * parameter frequency: frequency of periodic effect.
 * parameter offset: offset of periodic effect.
 */
void FFBPeriodicInit(FFBPeriodicParam_t *peri, float amplitude, float frequency,
		float offset);

/*
 * Calculate force feedback periodic effect.
 * parameter dt: time delta between previous and current call.
 * returns: calculated force feedback
 */
float FFBPeriodicCalc(FFBPeriodicParam_t *peri);

/*
 * Update force feedback periodic internal time.
 * parameter dt: time delta between previous and current call.
 */
void FFBPeriodicUpdateTime(int dt);

#ifdef __cplusplus
}
#endif

#endif /* FORCE_FEEDBACK_PERIODIC_H_ */
