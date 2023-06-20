/*
 * feed_forward.h
 *
 *  Created on: Jun 2, 2023
 *      Author: Jennyston
 */

#ifndef FEED_FORWARD_H_
#define FEED_FORWARD_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct FeedForward {

	float ks;
	float kv;
	float ka;

} FeedForward_t;

/*
 * Initializes feed forward controller structure.
 * parameter controller: pointer to feed forward controller structure.
 */
void FFInit(FeedForward_t *controller);
float FFCompute(FeedForward_t *controller, float velocity, float acceleration);
void FFSetKs(FeedForward_t * controller, float ks);
void FFSetKv(FeedForward_t * controller, float kv);
void FFSetKa(FeedForward_t * controller, float ka);

#ifdef __cplusplus
}
#endif

#endif /* FEED_FORWARD_H_ */
