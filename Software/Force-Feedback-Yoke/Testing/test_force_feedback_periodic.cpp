#include "gtest/gtest.h"
#include "force_feedback_periodic.h"

TEST(FFBPeriodicTest, FFBPeriodicZeroTest) {
	FFBPeriodic_t periodic;
	FFBPeriodicInit(&periodic, 0, 0, 0);

	float result = CalcFFBPeriodic(&periodic, 0);

	EXPECT_EQ(result, 0) << "FFBPeriodic output not 0 when parameters are " <<
			"all 0";
}

TEST(FFBPeriodicTest, FFBPeriodicQuarterWaveTest) {
	FFBPeriodic_t periodic;
	FFBPeriodicInit(&periodic, 1, 1, 0);

	float result = CalcFFBPeriodic(&periodic, 250);
	EXPECT_EQ(result, 0) << "FFBPeriodic output not 0.0 for 0ms, " \
			"amplitude 1.0, offset 0";

	float result2 = CalcFFBPeriodic(&periodic, 250);
	EXPECT_EQ(result2, 1.0) << "FFBPeriodic output not 1.0 for 250ms, " \
				"amplitude 1.0, offset 0";

}
