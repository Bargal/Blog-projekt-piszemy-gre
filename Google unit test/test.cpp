#include "pch.h"

double check(const double a)
{
	return a+2;
}

TEST(SquareRootTest, PositiveNos) {
	EXPECT_EQ(326.0, check(324.0));
	EXPECT_EQ(647.16, check(645.16));
	EXPECT_EQ(2535.310224, check(2533.310224));
}

TEST(SquareRootTest, ZeroAndNegativeNos) {
	ASSERT_EQ(2.0, check(0.0));
	ASSERT_EQ(-1, check(-22.0));
}

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}
