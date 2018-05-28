#include "pch.h"
#include "../Blog projekt piszemy gre/Player.h"


TEST(Player, pierwszy_test) {
	
	Player test(10, 10);
	auto te = test.get_endGame();
	EXPECT_EQ(10, te);
}