#include "pch.h"

class InitialiseReportTests :public ::testing::TestWithParam<std::vector<std::string>> { };

TEST_P(InitialiseReportTests, GoodArgs)
{
	Robot robot;
	bool result = robot.Initialise(GetParam());
	EXPECT_TRUE(result);
}

INSTANTIATE_TEST_CASE_P(
	ToyRobotTests,
	InitialiseReportTests,
	::testing::Values(
		std::vector<std::string>{ "REPORT"},
		std::vector<std::string>{ " REPORT"},
		std::vector<std::string>{ "REPORT "},
		std::vector<std::string>{ " REPORT "},
		std::vector<std::string>{ "report"}
));