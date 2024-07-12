/*
 * test_pid.cpp
 *
 *  Created on: Jun 2, 2023
 *      Author: Jennyston
 */

#include "gtest/gtest.h"
#include "pid.h"

TEST(PIDTest, PIDErrorZeroTest) {
	PID_t pid;
	PIDInit(&pid);

	float result = CalcPID(&pid, 0, 0);

	EXPECT_EQ(result, 0) << "PID output not 0 when error is 0";
}

TEST(PIDTest, PIDProportionalTest) {
	PID_t pid;
	PIDInit(&pid);
	pid.kP = 2;
	pid.kI = 0;
	pid.kD = 0;

	float result = CalcPID(&pid, 1, 0);

	EXPECT_EQ(result, 2) <<
			"PID output not 2 when error is 1 and Kp is 2 (Ki = Kd = 0)";
}

TEST(PIDTest, PIDIntegralTest) {
	PID_t pid;
	PIDInit(&pid);
	pid.kP = 0;
	pid.kI = 2;
	pid.kD = 0;

	float result = CalcPID(&pid, 1, 0);

	EXPECT_EQ(result, PID_DT * 2) <<
			"PID output not " << PID_DT * 2 <<
			" when error is 1 and Ki is 2 (Kp = Kd = 0)";
}
