#pragma once

#include <string>
#include <iostream>

namespace DataTypes
{

enum class Direction
{
	INVALID,
	North = 1,
	East, // 2
	South, // 3
	West // 4
};

enum class Command
{
	INVALID,
	Place,
	Move,
	Left,
	Right,
	Report
};

struct PlaceData
{
	int x;
	int y;
	Direction direction;
};

// helper functions for enum <-> string
static Direction DirectionAsEnum(std::string input)
{
	if (input == "NORTH")
	{
		return Direction::North;
	}

	if (input == "EAST")
	{
		return Direction::East;
	}

	if (input == "SOUTH")
	{
		return Direction::South;
	}

	if (input == "WEST")
	{
		return Direction::West;
	}

	std::cerr << "Error - unknown direciton: " << input << std::endl;
	return Direction::INVALID;
}

static std::string DirectionAsString(Direction direction)
{
	switch (direction)
	{
	case Direction::North:
	{
		return "NORTH";
		break;
	}
	case Direction::East:
	{
		return "EAST";
		break;
	}
	case Direction::South:
	{
		return "SOUTH";
		break;
	}
	case Direction::West:
	{
		return "WEST";
		break;
	}
	default:
		return "";
		break;
	}
}

static std::string CommandAsString(Command command)
{
	switch (command)
	{
	case Command::Place:
	{
		return "Place";
		break;
	}
	case Command::Move:
	{
		return "Move";
		break;
	}
	case Command::Left:
	{
		return "Left";
		break;
	}
	case Command::Right:
	{
		return "Right";
		break;
	}
	case Command::Report:
	{
		return "Report";
		break;
	}
	default:
		return "";
		break;
	}
}
}
