#pragma once

#include <utility> // std::pair
#include <queue>
#include <unordered_map>
#include <memory>

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
const int gridSize = 5;
using PlaceDataQueue = std::queue<std::shared_ptr<DataTypes::PlaceData>>;

class Robot
{
public:
	Robot();
	~Robot();
	bool Initialise(const std::vector<std::string>& commandLineArgs);
	void ProcessCommands();

private:
// helpers
	std::shared_ptr<DataTypes::PlaceData> CreatePlaceData(std::string input);
	std::string GetDirectionAsString(DataTypes::Direction direction);
	std::string GetCommandAsString(DataTypes::Command command);

// Command handlers
	void DoPlace();
	void DoMove();
	void DoLeft();
	void DoRight();
	void DoReport();

private:
	// input data queues
	std::queue<DataTypes::Command> _commandQueue;
	PlaceDataQueue _placeDataQueue;

	// immutable containers
	const std::unordered_map<std::string, DataTypes::Command> _commandMap = {
		{"PLACE", DataTypes::Command::Place},
		{"MOVE", DataTypes::Command::Move},
		{"LEFT", DataTypes::Command::Left},
		{"RIGHT", DataTypes::Command::Right},
		{"REPORT", DataTypes::Command::Report},
	};

	// immutable containers
	const std::unordered_map<std::string, DataTypes::Direction> _directionMap = {
		{"NORTH", DataTypes::Direction::North},
		{"EAST", DataTypes::Direction::East},
		{"SOUTH", DataTypes::Direction::South},
		{"WEST", DataTypes::Direction::West},
	};

	// state
	std::pair<int, int> _currentPosition = { 0,0 };
	DataTypes::Direction _currentDirection = DataTypes::Direction::INVALID;
};

