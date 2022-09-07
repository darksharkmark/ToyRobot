#include "pch.h"

class SimpleSingleCommands :public ::testing::TestWithParam<std::vector<std::string>> { };

TEST_P(SimpleSingleCommands, GoodArgs)
{
	Robot robot;
	bool result = robot.Initialise(GetParam());
	EXPECT_TRUE(result);
}

INSTANTIATE_TEST_CASE_P(
	ToyRobotTests,
	SimpleSingleCommands,
	::testing::Values(
		std::vector<std::string>{ "PLACE", "0,0,NORTH" },
		std::vector<std::string>{ "PLACE", "0,0,EAST" },
		std::vector<std::string>{ "PLACE", "0,0,SOUTH" },
		std::vector<std::string>{ "PLACE", "0,0,WEST" },
		std::vector<std::string>{ "MOVE"},
		std::vector<std::string>{ "LEFT"},
		std::vector<std::string>{ "RIGHT"},
		std::vector<std::string>{ "REPORT"}
));

