#include "pch.h"

class InitialiseMoveTests :public ::testing::TestWithParam<std::vector<std::string>> { };

TEST_P(InitialiseMoveTests, GoodArgs)
{
	Robot robot;
	bool result = robot.Initialise(GetParam());
	EXPECT_TRUE(result);
}

INSTANTIATE_TEST_CASE_P(
	ToyRobotTests,
	InitialiseMoveTests,
	::testing::Values(
		std::vector<std::string>{ "MOVE"},
		std::vector<std::string>{ " MOVE"},
		std::vector<std::string>{ "MOVE "},
		std::vector<std::string>{ " MOVE "},
		std::vector<std::string>{ "move"}
	));