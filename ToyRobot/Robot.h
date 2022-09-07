#pragma once

#include <utility> // pair
#include <queue>
#include <unordered_map>
#include <memory> // shared_ptr

namespace DataTypes
{
	enum class Direction : int
	{
		INVALID = 0,
		North = 1,
		East = 2,
		South = 3,
		West = 4
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
}

/*
*	To help visualise
* 
	{{0,4}, {1,4}, {2,4}, {3,4}, {4,4}},
	{{0,3}, {1,3}, {2,3}, {3,3}, {4,3}},
	{{0,2}, {1,2}, {2,2}, {3,2}, {4,2}},
	{{0,1}, {1,1}, {2,1}, {3,1}, {4,1}},
	{{0,0}, {1,0}, {2,0}, {3,0}, {4,0}},
*/
// constants
const int gridSize = 5;

// typedefs
using CommandQueue = std::queue<DataTypes::Command>;
using PlaceDataQueue = std::queue<std::shared_ptr<DataTypes::PlaceData>>;
using CommandMap = const std::unordered_map<std::string, DataTypes::Command>;
using DirectionMap = const std::unordered_map<std::string, DataTypes::Direction>;
using Coordinates = std::pair<int, int>;

class Robot
{
	friend class ToyRobotTests;

public:
	bool Initialise(const std::vector<std::string>& commandLineArgs);
	void ProcessCommands();

private:
// helpers
	std::shared_ptr<DataTypes::PlaceData> CreatePlaceData(const std::string& input);
	const std::string GetDirectionAsString(DataTypes::Direction direction) const;
	const bool ValidateMove(int position) const;

// Command handlers
	void DoPlace();
	void DoMove();
	void DoLeft();
	void DoRight();
	void DoReport();

// input data queues
	CommandQueue _commandQueue;
	PlaceDataQueue _placeDataQueue;

// immutable containers
	CommandMap _commandMap {
		{"PLACE", DataTypes::Command::Place},
		{"MOVE", DataTypes::Command::Move},
		{"LEFT", DataTypes::Command::Left},
		{"RIGHT", DataTypes::Command::Right},
		{"REPORT", DataTypes::Command::Report},
	};
	DirectionMap _directionMap {
		{"NORTH", DataTypes::Direction::North},
		{"EAST", DataTypes::Direction::East},
		{"SOUTH", DataTypes::Direction::South},
		{"WEST", DataTypes::Direction::West},
	};

// state
	Coordinates _currentPosition { 0,0 };
	DataTypes::Direction _currentDirection { DataTypes::Direction::INVALID };
	bool isPlaced;
};

