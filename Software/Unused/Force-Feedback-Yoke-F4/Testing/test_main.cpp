/*
 * test_main.cpp
 *
 *  Created on: Apr 7, 2024
 *      Author: Jennyston
 */

#include "gtest/gtest.h"

int main(int ac, char* av[])
{
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}

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

