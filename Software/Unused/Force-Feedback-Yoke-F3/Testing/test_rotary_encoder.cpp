/*
 * rotary_encoder_test.cpp
 *
 *  Created on: Jun 2, 2023
 *      Author: Jennyston
 */

#include "gtest/gtest.h"
#include "rotary_encoder.h"

TEST(RotaryEncTest, RotaryEncInitTest) {
	RotaryEncoder_t encoder;
	RotaryEncInit(&encoder);

	//ensure proper initialization values
	ASSERT_EQ(encoder.prevHardCount, 0);
	ASSERT_EQ(encoder.count32, 0);
	ASSERT_EQ(encoder.speed, 0);
}

TEST(RotaryEncTest, RotaryEncUpdateZeroTest) {
	RotaryEncoder_t encoder;
	RotaryEncInit(&encoder);

	//0 change in count
	RotaryEncUpdate(&encoder, 0, 1);
	EXPECT_EQ(RotaryEncGetCount(&encoder), 0) <<
			"Encoder count changed with no change in count";
}

TEST(RotaryEncTest, RotaryEncUpdateChangeTest) {
	RotaryEncoder_t encoder;
	RotaryEncInit(&encoder);

	RotaryEncUpdate(&encoder, 1, 1);
	EXPECT_EQ(RotaryEncGetCount(&encoder), 1) <<
			"Encoder count did not change";
}

TEST(RotaryEncTest, RotaryEncUpdateNoWrapTest) {
	RotaryEncoder_t encoder;
	RotaryEncInit(&encoder);

	RotaryEncUpdate(&encoder, ENC_COUNT_WRAP_THRESHOLD-1, 1);
	EXPECT_EQ(RotaryEncGetCount(&encoder), ENC_COUNT_WRAP_THRESHOLD-1) <<
			"Encoder count wrapped when not supposed to";
}

TEST(RotaryEncTest, RotaryEncUpdateUnderflowWrapTest) {
	RotaryEncoder_t encoder;
	RotaryEncInit(&encoder);

	RotaryEncUpdate(&encoder, 0xFFFF, 1);
	EXPECT_EQ(RotaryEncGetCount(&encoder), -1) <<
			"Encoder count underflow did not wrap when supposed to";
}

TEST(RotaryEncTest, RotaryEncUpdateOverflowWrapTest) {
	RotaryEncoder_t encoder;
	RotaryEncInit(&encoder);

	RotaryEncUpdate(&encoder, ENC_COUNT_WRAP_THRESHOLD-1, 1);
	RotaryEncUpdate(&encoder, (ENC_COUNT_WRAP_THRESHOLD-1)*2, 1);

	RotaryEncUpdate(&encoder, 0, 1);
	EXPECT_EQ(RotaryEncGetCount(&encoder), 65536) <<
			"Encoder count overflow did not wrap when supposed to";
}


