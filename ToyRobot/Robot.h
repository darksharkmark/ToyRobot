#pragma once

#include <utility> // std::pair
#include <queue>
#include <unordered_map>

#include "DataTypes.h"

const int gridSize = 5;
/*
*	To help visualise
* 
	{{0,4}, {1,4}, {2,4}, {3,4}, {4,4}},
	{{0,3}, {1,3}, {2,3}, {3,3}, {4,3}},
	{{0,2}, {1,2}, {2,2}, {3,2}, {4,2}},
	{{0,1}, {1,1}, {2,1}, {3,1}, {4,1}},
	{{0,0}, {1,0}, {2,0}, {3,0}, {4,0}},
*/

class Robot
{
public:
	Robot();
	~Robot();
	bool Initialise(int argc, char* argv[]);
	void ProcessCommands();

private:
// helpers
	std::shared_ptr<DataTypes::PlaceData> CreatePlaceData(std::string input);

// Command handlers
	void DoPlace();
	void DoMove();
	void DoLeft();
	void DoRight();
	void DoReport();

private:
	// input data queues
	std::queue<DataTypes::Command> _commandQueue;
	std::queue<std::shared_ptr<DataTypes::PlaceData>> _placeDataQueue;

	// immutable containers
	const std::unordered_map<std::string, DataTypes::Command> _commandMap = {
		{"PLACE", DataTypes::Command::Place},
		{"MOVE", DataTypes::Command::Move},
		{"LEFT", DataTypes::Command::Left},
		{"RIGHT", DataTypes::Command::Right},
		{"REPORT", DataTypes::Command::Report},
	};



	// state
	std::pair<int, int> _currentPosition = { 0,0 };
	DataTypes::Direction _currentDirection = DataTypes::Direction::INVALID;
};

