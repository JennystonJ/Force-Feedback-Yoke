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
	float time;
} FFBPeriodic_t;

#ifdef __cplusplus
}
#endif

#endif /* FORCE_FEEDBACK_PERIODIC_H_ */
