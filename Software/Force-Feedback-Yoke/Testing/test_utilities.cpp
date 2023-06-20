/*
 * utilities_test.cpp
 *
 *  Created on: Jun 2, 2023
 *      Author: Jennyston
 */

#include "gtest/gtest.h"
#include "utilities.h"

TEST(UtilitiesTest, UnwrapAtThreshold16NoWrapTest) {
	int32_t result = UnwrapAtThreshold16(0, 9, 10);

	ASSERT_EQ(result, 9) << "Result unwrapped when not supposed to";
}

TEST(UtilitiesTest, UnwrapAtThreshold16WrapUnderflowTest) {
	int32_t result = UnwrapAtThreshold16(0, 65535, 32767);

	ASSERT_EQ(result, -1) << "Result did not unwrap on underflow";
}

TEST(UtilitiesTest, UnwrapAtThreshold16WrapOverflowTest) {
	int32_t result = UnwrapAtThreshold16(65535, 0, 32767);

	ASSERT_EQ(result, 1) << "Result did not unwrap on overflow";
}

TEST(UtitlitesTest, ConstrainWithinTest) {
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
