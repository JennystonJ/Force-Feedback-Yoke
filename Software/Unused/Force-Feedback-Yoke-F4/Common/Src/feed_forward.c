/*
 * feed_forward.c
 *
 *  Created on: Jun 2, 2023
 *      Author: Jennyston
 */

#include "feed_forward.h"

void FFInit(FeedForward_t *controller) {
	controller->ks = 1000;
	controller->kv = 0.583878439;
	controller->ka = 0;
}

float FFCompute(FeedForward_t *controller, float velocity, float acceleration) {
	int sign = velocity < 0 ? -1 : 1;
	return controller->ks*sign + controller->kv*velocity +
			controller->ka*acceleration;
}

void FFSetKs(FeedForward_t * controller, float ks) {
	controller->ks = ks;
}

void FFSetKv(FeedForward_t * controller, float kv) {
	controller->kv = kv;
}

void FFSetKa(FeedForward_t * controller, float ka) {
	controller->ka = ka;
}
