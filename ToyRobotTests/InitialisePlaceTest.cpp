#include "pch.h"

class PlaceTest :public ::testing::TestWithParam<std::vector<std::string>> { };

TEST_P(PlaceTest, GoodArgs)
{
	Robot robot;
	bool result = robot.Initialise(GetParam());
	EXPECT_FALSE(result);
}

INSTANTIATE_TEST_CASE_P(
	ToyRobotTests,
	PlaceTest,
	::testing::Values(
		std::vector<std::string>{ " PLACE", "0,0,NORTH" },
		std::vector<std::string>{ "PLACE ", "0,0,NORTH" },
		std::vector<std::string>{ "PLACE", " 0,0,NORTH" },
		std::vector<std::string>{ "PLACE", "0 ,0,NORTH" },
		std::vector<std::string>{ "PLACE", "0, 0,NORTH" },
		std::vector<std::string>{ "PLACE", "0,0 ,NORTH" },
		std::vector<std::string>{ "PLACE", "0,0, NORTH" },
		std::vector<std::string>{ "PLACE", "0,0,NORTH " },
		std::vector<std::string>{ "place", "0,0,NORTH" },
		std::vector<std::string>{ "PLACE", "0,0,north" },

		std::vector<std::string>{ "PLACE", "5,0,NORTH" },
		std::vector<std::string>{ "PLACE", "0,5,NORTH" },
		std::vector<std::string>{ "PLACE", "5,0,EAST" },
		std::vector<std::string>{ "PLACE", "0,5,EAST" },
		std::vector<std::string>{ "PLACE", "5,0,SOUTH" },
		std::vector<std::string>{ "PLACE", "0,5,SOUTH" },
		std::vector<std::string>{ "PLACE", "5,0,WEST" },
		std::vector<std::string>{ "PLACE", "0,5,WEST" },

		std::vector<std::string>{ "PLACE", "-1,0,NORTH" },
		std::vector<std::string>{ "PLACE", "0,-1,NORTH" },
		std::vector<std::string>{ "PLACE", "0,-1,NORTH" },

		std::vector<std::string>{ "PLACE", "\0,0,NORTH" },
		std::vector<std::string>{ "PLACE", "/0,0,NORTH" }
));

