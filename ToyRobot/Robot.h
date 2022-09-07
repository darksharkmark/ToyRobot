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

// constants
const int gridSize = 5;

// typedefs
using CommandQueue = std::queue<DataTypes::Command>;
using PlaceDataQueue = std::queue<std::shared_ptr<DataTypes::PlaceData>>;
using CommandMap = const std::unordered_map<std::string, DataTypes::Command>;
using DirectionMap = const std::unordered_map<std::string, DataTypes::Direction>;
using Coordinates = std::pair<int, int>;

struct State {
	Coordinates currentPosition;
	DataTypes::Direction currentDirection;
	bool isPlaced;
};

class Robot
{
public:
	bool Initialise(const std::vector<std::string>& commandLineArgs);
	void ProcessCommands();
	State GetState(); // mainly used for debug help and testing
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
	bool isPlaced{ false };
};

