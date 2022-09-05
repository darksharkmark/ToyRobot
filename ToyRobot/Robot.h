#pragma once

#include <utility> // std::pair
#include <queue>
#include <unordered_map>

#include "DataTypes.h"

class Robot
{
public:
	bool Initialise(int argc, char* argv[]);
	bool ProcessInput(int argc, char* argv[]);
	std::shared_ptr<DataTypes::PlaceData> CreatePlaceData(std::string input);
private:

private:
	std::queue<std::shared_ptr<DataTypes::PlaceData>> _placeDataContainer;
	std::queue<DataTypes::Command> _instructions;

	std::unordered_map<std::string, DataTypes::Command> _commandMap = {
		{"PLACE", DataTypes::Command::Place},
		{"MOVE", DataTypes::Command::Move},
		{"LEFT", DataTypes::Command::Left},
		{"RIGHT", DataTypes::Command::Right},
		{"REPORT", DataTypes::Command::Report},
	};

	std::pair<int, int> _grid[5][5] = {
		{{0,4}, {1,4}, {2,4}, {3,4}, {4,4}},
		{{0,3}, {1,3}, {2,3}, {3,3}, {4,3}},
		{{0,2}, {1,2}, {2,2}, {3,2}, {4,2}},
		{{0,1}, {1,1}, {2,1}, {3,1}, {4,1}},
		{{0,0}, {1,0}, {2,0}, {3,0}, {4,0}},
	};
};

