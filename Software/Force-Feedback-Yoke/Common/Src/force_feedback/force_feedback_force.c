/*
 * force_feedback_force.c
 *
 *  Created on: Aug 21, 2025
 *      Author: Jennyston
 */

#include "force_feedback/force_feedback_force.h"

void FFB_ForceUnpack(FFBForces_t *unpackedForce,
		const FFBForcesPacked_t *packedForce) {
	unpackedForce->constantForce = packedForce->constantForce;
	unpackedForce->springForce = packedForce->springForce;
	unpackedForce->damperForce = packedForce->damperForce;
}
