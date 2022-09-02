/*
* Toy Robot
* 5 x 5 grid
* 
* Commands:
* PLACE X,Y, [NORTH, EAST, SOUTH, WEST]
* MOVE
* LEFT (rotate, not move)
* RIGHT (rotate, not move)
* REPORT (print position and direction)
* 
* (0,0) -> SOUTH WEST corner
* Must be placed first
* any sequence of commands can be issued

*/

/*
	TODO:
		Command line argument parser
*/

#include <utility>
#include <iostream>
#include <queue>
#include <memory>

enum class Direction
{
	North,
	West,
	South, 
	East
};

std::string DirectionAsString(Direction direction);

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

enum class Command
{
	Place,
	Move, 
	Left,
	Right,
	Report
};

bool ProcessInput(int argc, char* argv[]);
void Place(int x, int y, Direction direction);
std::shared_ptr<PlaceData> CreatePlaceData(std::string input);
Direction DirectionAsEnum(std::string input);
std::string CommandAsString(Command command);

std::queue<std::shared_ptr<PlaceData>> placeDatas;
std::queue<Command> instructions;

std::pair<int, int> grid[5][5] = {
	{{0,4}, {1,4}, {2,4}, {3,4}, {4,4}},
	{{0,3}, {1,3}, {2,3}, {3,3}, {4,3}},
	{{0,2}, {1,2}, {2,2}, {3,2}, {4,2}},
	{{0,1}, {1,1}, {2,1}, {3,1}, {4,1}},
	{{0,0}, {1,0}, {2,0}, {3,0}, {4,0}},
};

int main(int argc, char* argv[])
{
	if (!ProcessInput(argc, argv))
	{
		return 0;
	}

	while(!instructions.empty())
	{
		Command instruction = instructions.front();
		std::cout << CommandAsString(instruction) << std::endl;

		if (instruction == Command::Place)
		{
			if (!placeDatas.empty())
			{
				auto& placeData = placeDatas.front();
				placeData->Print();
				placeDatas.pop();
			}
		}

		instructions.pop();
	}

	return 0;
}

bool ProcessInput(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cerr << "no input found" << std::endl;
		return false;
	}

	std::cout << "args: " << std::endl;
	for (size_t i = 1; i < argc; i++)
	{
		std::string command = argv[i];

		if (command == "PLACE")
		{
			instructions.emplace(Command::Place);
			if (i < (argc - 1))
			{
				// should be X, Y, F
				std::string nextCommand = argv[++i];
				auto placeData = CreatePlaceData(nextCommand);
				placeDatas.push(placeData);
			}
		}
		else if (command == "MOVE")
		{
			instructions.emplace(Command::Move);
		}
		else if (command == "LEFT")
		{
			instructions.emplace(Command::Left);
		}
		else if (command == "RIGHT")
		{
			instructions.emplace(Command::Right);
		}
		else if (command == "REPORT")
		{
			instructions.emplace(Command::Report);
		}
		else
		{
			// invalid command
			std::cerr << "Error - Invalid Commmand: " << command << std::endl;
		}
	}

	return true;
}

std::shared_ptr<PlaceData> CreatePlaceData(std::string input)
{
	if (input.size() < 8) // invalid
	{
		return {};
	}

	std::shared_ptr<PlaceData> placeData = std::make_unique<PlaceData>();

	// e.g. 1,2,NORTH or 3,4,WEST 
	placeData->x = static_cast<int>(input.at(0) - 48);
	placeData->y = static_cast<int>(input.at(2) - 48);
	
	auto directionString = input.substr(4, input.size() - 4);
	placeData->direction = DirectionAsEnum(directionString);

	return placeData;
}

Direction DirectionAsEnum(std::string input)
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
}

std::string DirectionAsString(Direction direction)
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
		break;
	}
}


std::string CommandAsString(Command command)
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
		break;
	}
}

void Place(int x, int y, Direction direction)
{

}