#include "pch.h"

class InitialiseLeftRightTests :public ::testing::TestWithParam<std::vector<std::string>> { };

TEST_P(InitialiseLeftRightTests, GoodArgs)
{
	Robot robot;
	bool result = robot.Initialise(GetParam());
	EXPECT_TRUE(result);
}

INSTANTIATE_TEST_CASE_P(
	ToyRobotTests,
	InitialiseLeftRightTests,
	::testing::Values(
		std::vector<std::string>{ "LEFT"},
		std::vector<std::string>{ " LEFT"},
		std::vector<std::string>{ "LEFT "},
		std::vector<std::string>{ " LEFT "},
		std::vector<std::string>{ "left"},

		std::vector<std::string>{ "RIGHT"},
		std::vector<std::string>{ " RIGHT"},
		std::vector<std::string>{ "RIGHT "},
		std::vector<std::string>{ " RIGHT "},
		std::vector<std::string>{ "right"}
));