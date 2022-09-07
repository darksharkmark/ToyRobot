/*
*	To help visualise
*
	{{0,4}, {1,4}, {2,4}, {3,4}, {4,4}},
	{{0,3}, {1,3}, {2,3}, {3,3}, {4,3}},
	{{0,2}, {1,2}, {2,2}, {3,2}, {4,2}},
	{{0,1}, {1,1}, {2,1}, {3,1}, {4,1}},
	{{0,0}, {1,0}, {2,0}, {3,0}, {4,0}},
*/

#include "pch.h"

class SequenceCommandsTest :public ::testing::Test { };
using namespace DataTypes;

TEST(SequenceCommandsTest, NoPlace)
{
	Robot robot;
	bool result = robot.Initialise({});
	ASSERT_TRUE(result);

	robot.ProcessCommands();
	auto state = robot.GetState();

	Coordinates coordinates{ 0,0 };
	EXPECT_EQ(state.currentPosition, coordinates);
	EXPECT_EQ(state.currentDirection, Direction::INVALID);
	EXPECT_FALSE(state.isPlaced);
}

TEST(SequenceCommandsTest, SimplePlace)
{
	Robot robot;
	bool result = robot.Initialise(
		{
			"PLACE",
			"0,0,NORTH"
		});
	ASSERT_TRUE(result);

	robot.ProcessCommands();
	auto state = robot.GetState();

	Coordinates coordinates{ 0,0 };
	EXPECT_EQ(state.currentPosition, coordinates);
	EXPECT_EQ(state.currentDirection, Direction::North);
	EXPECT_TRUE(state.isPlaced);
}

TEST(SequenceCommandsTest, SimpleMove)
{
	Robot robot;
	bool result = robot.Initialise(
		{
			"PLACE",
			"3,4,EAST",
			"MOVE"
		});
	ASSERT_TRUE(result);

	robot.ProcessCommands();
	auto state = robot.GetState();

	Coordinates coordinates{ 4,4 };
	EXPECT_EQ(state.currentPosition, coordinates);
	EXPECT_EQ(state.currentDirection, Direction::East);
	EXPECT_TRUE(state.isPlaced);
}


TEST(SequenceCommandsTest, SimpleLeft)
{
	Robot robot;
	bool result = robot.Initialise(
		{
			"PLACE",
			"1,2,SOUTH",
			"LEFT"
		});
	ASSERT_TRUE(result);

	robot.ProcessCommands();
	auto state = robot.GetState();

	Coordinates coordinates{ 1,2 };
	EXPECT_EQ(state.currentPosition, coordinates);
	EXPECT_EQ(state.currentDirection, Direction::East);
	EXPECT_TRUE(state.isPlaced);
}

TEST(SequenceCommandsTest, SimpleRight)
{
	Robot robot;
	bool result = robot.Initialise(
		{
			"PLACE",
			"4,2,NORTH",
			"RIGHT"
		});
	ASSERT_TRUE(result);

	robot.ProcessCommands();
	auto state = robot.GetState();

	Coordinates coordinates{ 4,2 };
	EXPECT_EQ(state.currentPosition, coordinates);
	EXPECT_EQ(state.currentDirection, Direction::East);
	EXPECT_TRUE(state.isPlaced);
}

TEST(SequenceCommandsTest, LeftFourTimes)
{
	Robot robot;
	bool result = robot.Initialise(
		{
			"PLACE",
			"4,4,NORTH",
			"LEFT",
			"LEFT",
			"LEFT",
			"LEFT"
		});
	ASSERT_TRUE(result);

	robot.ProcessCommands();
	auto state = robot.GetState();

	Coordinates coordinates{ 4,4 };
	EXPECT_EQ(state.currentPosition, coordinates);
	EXPECT_EQ(state.currentDirection, Direction::North);
	EXPECT_TRUE(state.isPlaced);
}

TEST(SequenceCommandsTest, RightFourTimes)
{
	Robot robot;
	bool result = robot.Initialise(
		{
			"PLACE",
			"4,4,NORTH",
			"RIGHT",
			"RIGHT",
			"RIGHT",
			"RIGHT"
		});
	ASSERT_TRUE(result);

	robot.ProcessCommands();
	auto state = robot.GetState();

	Coordinates coordinates{ 4,4 };
	EXPECT_EQ(state.currentPosition, coordinates);
	EXPECT_EQ(state.currentDirection, Direction::North);
	EXPECT_TRUE(state.isPlaced);
}