/*
 * utilities_test.cpp
 *
 *  Created on: Jun 2, 2023
 *      Author: Jennyston
 */

#include "gtest/gtest.h"
#include "utilities/utilities.h"

TEST(UtilitiesTest, MapEqualTest) {
	// Arrange
	int32_t in = 10;
	int32_t min = 0;
	int32_t max = 100;

	// Act
	int32_t result = Map(in, min, max, min, max);

	//Assert
	ASSERT_EQ(result, 10);
}

TEST(UtilitiesTest, MapScaleUpTest) {
	// Arrange
	int32_t in = 10;
	int32_t min = 0;
	int32_t inMax = 100;
	int32_t outMax = 1000;

	// Act
	int32_t result = Map(in, min, inMax, min, outMax);

	//Assert
	ASSERT_EQ(result, 100);
}

TEST(UtilitiesTest, MapScaleDownTest) {
	// Arrange
	int32_t in = 50;
	int32_t min = 0;
	int32_t inMax = 100;
	int32_t outMax = 10;

	// Act
	int32_t result = Map(in, min, inMax, min, outMax);

	//Assert
	ASSERT_EQ(result, 5);
}

TEST(UtilitiesTest, MapScaleUpMinMaxTest) {
	// Arrange
	int32_t in = 15;
	int32_t min = 10;
	int32_t inMax = 110;
	int32_t outMin = 100;
	int32_t outMax = 1100;

	// Act
	int32_t result = Map(in, min, inMax, outMin, outMax);

	//Assert
	ASSERT_EQ(result, 150);
}

TEST(UtilitiesTest, MapScaleDownMinMaxTest) {
	// Arrange
	int32_t in = 150;
	int32_t min = 100;
	int32_t inMax = 1100;
	int32_t outMin = 10;
	int32_t outMax = 110;

	// Act
	int32_t result = Map(in, min, inMax, outMin, outMax);

	//Assert
	ASSERT_EQ(result, 15);
}

TEST(UtilitiesTest, ConstrainWithinTest) {
	int32_t result = Constrain(0, -1, 1);

	ASSERT_EQ(result, 0);
}

TEST(UtitlitesTest, ConstrainMinTest) {
	int32_t result = Constrain(-1, 0, 1);

	ASSERT_EQ(result, 0);
}

TEST(UtitlitesTest, ConstrainMaxTest) {
	int32_t result = Constrain(2, 0, 1);

	ASSERT_EQ(result, 1);
}
