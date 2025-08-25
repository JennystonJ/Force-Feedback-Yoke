/*
 * force_feedback_force.h
 *
 *  Created on: Aug 21, 2025
 *      Author: Jennyston
 */

#ifndef INC_FORCE_FEEDBACK_FORCE_FEEDBACK_FORCE_H_
#define INC_FORCE_FEEDBACK_FORCE_FEEDBACK_FORCE_H_

#include <stdint.h>

typedef enum FFBForceType {
	FFB_FORCE_TYPE_CLEAR,
	FFB_FORCE_TYPE_CONSTANT,
	FFB_FORCE_TYPE_SPRING,
	FFB_FORCE_TYPE_DAMPER,
	FFB_FORCE_TYPE_PERIODIC
} FFBForceType_e;

// *** Unpacked structures ***
typedef struct FFBForces {
	float constantForce;
	float springForce;
	float damperForce;
//	FFBPeriodicForce_t periodic;
} FFBForces_t;

// *** Packed structures ***

typedef struct __attribute__((packed)) FFBForcesPacked {
	float constantForce;
	float springForce;
	float damperForce;
//	FFBPeriodicForce_t periodic;
} FFBForcesPacked_t;

void FFB_ForceUnpack(FFBForces_t *unpackedForce,
		const FFBForcesPacked_t *packedForce);

#endif /* INC_FORCE_FEEDBACK_FORCE_FEEDBACK_FORCE_H_ */
