#include <memory>
#include "Robot.h"

using namespace DataTypes;

Robot::Robot()
{
}

Robot::~Robot()
{
}

bool Robot::Initialise(int argc, char* argv[])
{
	// must have at least 3 args to start
	// (1) exe name
	// (2) PLACE
	// (3) X,Y,[NORTH | EAST | SOUTH | WEST]
	{
		if (argc < 3)
		{
			std::cerr << "Error - no input found" << std::endl;
			return false;
		}
	
		std::string firstCommand = argv[1];
		if (firstCommand != "PLACE")
		{
			std::cerr << "Error - First command is: " << argv[1] << std::endl;
			std::cerr << "First command must be PLACE" << std::endl;
			return false;
		}
	}

	//std::cout << "args: " << std::endl;
	for (int i = 1; i < argc; ++i)
	{
		std::string rawCommand = argv[i];
		try
		{
			// catch below will handle invalid input
			Command command = _commandMap.at(rawCommand);
			_commandQueue.push(command);

			// not ideal but cant think of a better way, TODO: cleanup 
			if (command == Command::Place)
			{
				if (i < (argc - 1))
				{
					// should be X, Y, [NORTH | EAST | SOUTH | WEST]
					std::string nextCommand = argv[++i];
					auto placeData = CreatePlaceData(nextCommand);
					if (placeData)
					{
						_placeDataQueue.push(placeData);
					}
					else
					{
						std::cerr << "Error - Invalid place data: " << nextCommand << std::endl;
						return false;
					}
				}
			}
		}
		catch (std::out_of_range e)
		{
			std::cerr << "Error - no command " << rawCommand << std::endl;
		}
	}

	return true;
}


/*
* TODO:
	Place,
	Move,
	Left,
	Right,
	Report
*/
void Robot::ProcessCommands()
{
	while (!_commandQueue.empty())
	{
		Command currentCommand = _commandQueue.front();

		switch (currentCommand)
		{
		case DataTypes::Command::INVALID:
			std::cerr << "Error - Invalid Command on Processing" << std::endl;
			break;
		case DataTypes::Command::Place:
			DoPlace();
			break;
		case DataTypes::Command::Move:
			DoMove();
			break;
		case DataTypes::Command::Left:
			DoLeft();
			break;
		case DataTypes::Command::Right:
			DoRight();
			break;
		case DataTypes::Command::Report:
			DoReport();
			break;
		default:
			break;
		}

		_commandQueue.pop();
	}
}

std::shared_ptr<PlaceData> Robot::CreatePlaceData(std::string input)
{
	// must be at 8 or 9 chars, single digit co-ordindates + commas + EAST/WEST | NORTH/SOUTH
	if (input.size() < 7 || input.size() > 9)
	{
		return nullptr;
	}

	auto directionString = input.substr(4, input.size() - 4);
	Direction direction = DirectionAsEnum(directionString);
	if (direction == Direction::INVALID)
	{
		return nullptr;
	}

	// convert char number to int
	int x = static_cast<int>(input.at(0) - 48);
	int y = static_cast<int>(input.at(2) - 48);
	if ((x < 0 || x > gridSize - 1) || (y < 0 || y > gridSize - 1))
	{
		return nullptr;
	}

	std::shared_ptr<PlaceData> placeData = std::make_shared<PlaceData>();
	placeData->x = x;
	placeData->y = y;
	placeData->direction = direction;

	return placeData;
}



// Command handlers
void Robot::DoPlace()
{
	if (!_placeDataQueue.empty())
	{
		const auto& currentPlaceData = _placeDataQueue.front();

		_currentPosition = { currentPlaceData->x, currentPlaceData->y };
		_currentDirection = currentPlaceData->direction;

		_placeDataQueue.pop();
	}
}

bool ValidateMove(int position)
{
	return position > -1 || position < gridSize;
}

void Robot::DoMove()
{
	switch (_currentDirection)
	{
		case Direction::North:
		{
			int newPosition = _currentPosition.second + 1;
			if (ValidateMove(newPosition)) 
			{ 
				_currentPosition.second = newPosition;	
			}
			break;
		}
		case Direction::West:
		{
			int newPosition = _currentPosition.first + 1;
			if (ValidateMove(newPosition))
			{
				_currentPosition.first =  newPosition;
			}
			break;
		}
		case Direction::South:
		{
			int newPosition = _currentPosition.second - 1;
			if (ValidateMove(newPosition))
			{
				_currentPosition.second = newPosition;
			}
			break;
		}
		case Direction::East:
		{
			int newPosition = _currentPosition.first - 1;
			if (ValidateMove(newPosition))
			{
				_currentPosition.first = newPosition;
			}
			break;
		}
	default:
		break;
	}
}

void Robot::DoLeft()
{
	int directionAsInt = static_cast<int>(_currentDirection);
	if (--directionAsInt < 1)
	{
		directionAsInt = 4;
	}

	_currentDirection = static_cast<Direction>(directionAsInt);
}

void Robot::DoRight()
{
	int directionAsInt = static_cast<int>(_currentDirection);
	if (++directionAsInt > 4)
	{
		directionAsInt = 1;
	}

	_currentDirection = static_cast<Direction>(directionAsInt);
}

void Robot::DoReport()
{
	std::cout << _currentPosition.first << "," << _currentPosition.second << "," << DataTypes::DirectionAsString(_currentDirection) << std::endl;
}


