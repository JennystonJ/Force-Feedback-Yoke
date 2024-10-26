/*
 * test_encoder.cpp
 *
 *  Created on: Jul 12, 2024
 *      Author: Jennyston
 */

#include "gtest/gtest.h"
#include "force_feedback_controller.h"

#include "encoder.h"

int mock_GetEncoderCount_NormalOperation(EncoderInterface_t *interface) {
	return 0;
}

int mock_GetEncoderCount_Overflow(EncoderInterface_t *interface) {
	// Simulate sensor count greater than prevHardCount + countPerRev / 2
	return 20;
}

int mock_GetEncoderCount_Underflow(EncoderInterface_t *interface) {
	// Simulate sensor count less than prevHardCount - countPerRev / 2
	return 80;
}

int mock_GetEncoderCount_SpeedPositive(EncoderInterface_t *interface) {
	// Simulate sensor count increasing linearly
	static int count = 0;
	count++;
	return count;
}

int mock_GetEncoderCount_SpeedZero(EncoderInterface_t *interface) {
	// Simulate a speed of 0 (constant sensor count)
	return 10;
}

TEST(EncoderTest, EncoderUpdate_NormalOperation) {
	// Arrange
	Encoder_t encoder;
	encoder.prevHardCount = 0;
	encoder.countPerRev = 100;
	encoder.totalCount = 0;
	encoder.interface.GetEncoderSensorCount =
			&mock_GetEncoderCount_NormalOperation;

	// Act
	EncoderUpdate(&encoder, 1);

	// Assert
	EXPECT_EQ(0, EncoderGetCount(&encoder));
}

TEST(EncoderTest, EncoderUpdate_Overflow) {
	// Arrange
	Encoder_t encoder;
	encoder.prevHardCount = 90; // Previous count close to maximum
	encoder.countPerRev = 100;
	encoder.totalCount = 0;
	encoder.interface.GetEncoderSensorCount = &mock_GetEncoderCount_Overflow;

	// Act
	EncoderUpdate(&encoder, 1);

	// Assert
	EXPECT_EQ(30, encoder.totalCount);
}

TEST(EncoderTest, EncoderUpdate_Underflow) {
	// Arrange
	Encoder_t encoder;
	encoder.prevHardCount = 10; // Previous count close to minimum
	encoder.countPerRev = 100;
	encoder.totalCount = 0;
	encoder.interface.GetEncoderSensorCount = &mock_GetEncoderCount_Underflow;

	// Act
	EncoderUpdate(&encoder, 1);

	// Assert
	EXPECT_EQ(-30, encoder.totalCount);
}

TEST(EncoderTest, EncoderUpdate_SpeedPositive) {
	// Arrange
	Encoder_t encoder;
	encoder.prevHardCount = 0;
	encoder.countPerRev = 100;
	encoder.totalCount = 0;
	encoder.interface.GetEncoderSensorCount =
			&mock_GetEncoderCount_SpeedPositive;

	// Act
	EncoderUpdate(&encoder, 1);
//	EncoderUpdate(&encoder, 1);

	// Assert
	EXPECT_EQ(1, encoder.speed);
}
