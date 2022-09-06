#include <memory>
#include "Robot.h"
#include <cstdlib>

using namespace DataTypes;

Robot::Robot()
{
}

Robot::~Robot()
{
}

bool Robot::Initialise(const std::vector<std::string>& commandLineArgs)
{
	// must have at least 3 args to start
	// (1) exe name
	// (2) PLACE
	// (3) X,Y,[NORTH | EAST | SOUTH | WEST]
	{
		std::string firstCommand = commandLineArgs.front();
		if (firstCommand != "PLACE")
		{
			std::cerr << "Error - First command is: " << firstCommand << std::endl;
			std::cerr << "First command must be PLACE" << std::endl;
			return false;
		}
	}

	for (auto iter = commandLineArgs.begin(); iter != commandLineArgs.end(); iter++)
	{
		try
		{
			// catch below will handle invalid input
			Command command = _commandMap.at(*iter);

			// special case for PLACE
			// PLACE needs to have co-ordinates & direction after it
			if (command == Command::Place)
			{
				if(iter != commandLineArgs.end() - 1)
				{
					// should be X, Y, [NORTH | EAST | SOUTH | WEST]
					std::string nextCommand = *(++iter);
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

					// only push PLACE if we have valid "place data" i.e. co-ordinates & direction
					_commandQueue.push(command);
				}
			}
			else
			{
				// all other commands push without other args
				_commandQueue.push(command);
			}
		}
		catch (std::out_of_range e)
		{
			std::cerr << "Error - invalid command " << *iter << std::endl;
		}
	}

	return true;
}

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
	int x = static_cast<int>(input.at(0) - '0');
	int y = static_cast<int>(input.at(2) - '0');
	if ((x < 0 || x > gridSize - 1) || (y < 0 || y > gridSize - 1))
	{
		return nullptr;
	}

	return std::make_shared<PlaceData>(PlaceData{ x, y, direction });
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
	else
	{
		std::cerr << "Error - We should have place data but we dont?" << std::endl;
	}
}

bool ValidateMove(int position)
{
	return position > -1 && position < gridSize;
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


