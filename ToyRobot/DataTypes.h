#pragma once

#include <string>
#include <iostream>

namespace DataTypes
{

enum class Direction
{
	INVALID,
	North,
	West,
	South,
	East
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
		return "North";
		break;
	}
	case Direction::East:
	{
		return "East";
		break;
	}
	case Direction::South:
	{
		return "South";
		break;
	}
	case Direction::West:
	{
		return "West";
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

struct PlaceData
{
	int x;
	int y;
	Direction direction;
	void Print()
	{
		std::cout << "X: " << x << ", ";
		std::cout << "Y: " << y << ", ";
		std::cout << "F: " << DirectionAsString(direction) << std::endl;
	}
};

}
