#include "pch.h"
#include <streambuf>
class EdgeCaseTests :public ::testing::TestWithParam<std::vector<std::string>> { };

TEST_P(EdgeCaseTests, GoodArgs)
{
	Robot robot;
	bool result = robot.Initialise(GetParam());
	ASSERT_TRUE(result);

}

INSTANTIATE_TEST_CASE_P(
	ToyRobotTests,
	EdgeCaseTests,
	::testing::Values(
		std::vector<std::string>{ "PLACE", "1,2,NORTH", "REPORT"} 
));

