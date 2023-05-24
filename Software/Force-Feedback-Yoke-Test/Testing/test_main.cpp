/* Testing/test_main.cpp */
#include "gtest/gtest.h"
#include "utilities.h"
#include "rotary_encoder.h"

int main(int ac, char* av[])
{
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}

/** Utilities Test **/
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

/** Rotary Encoder Test **/
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


//
//TEST(BasicTest, PassingTest)
//{
//	TrivialClass t;
//	EXPECT_TRUE(t.returnsTrue());
//}
//
//TEST(BasicTest, FailingTest)
//{
//	TrivialClass t;
//	EXPECT_TRUE(t.returnsFalse());
//}
