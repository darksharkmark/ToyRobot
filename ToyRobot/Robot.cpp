#include "Robot.h"

#include <cstdlib>
#include <type_traits>
#include <iostream>

bool Robot::Initialise(const std::vector<std::string>& commandLineArgs)
{
	for (auto iter = commandLineArgs.begin(); iter != commandLineArgs.end(); iter++)
	{
		DataTypes::Command command = DataTypes::Command::INVALID;
		try
		{
			command = _commandMap.at(*iter);
		}
		catch (std::out_of_range e)
		{
			std::cerr << "Error - invalid command " << *iter << std::endl;
			continue;
		}

		// special case for PLACE, needs to have co-ordinates & direction after it
		if (command == DataTypes::Command::Place)
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

	return true;
}

void Robot::ProcessCommands()
{
	while (!_commandQueue.empty())
	{
		DataTypes::Command currentCommand = _commandQueue.front();

		if (!isPlaced && currentCommand != DataTypes::Command::Place)
		{
			_commandQueue.pop();
			continue;
		}

		switch (currentCommand)
		{
			case DataTypes::Command::Place:
			{
				DoPlace();
				break;
			}
			case DataTypes::Command::Move:
			{
				DoMove();
				break;
			}
			case DataTypes::Command::Left:
			{
				DoLeft();
				break;
			}
			case DataTypes::Command::Right:
			{
				DoRight();
				break;
			}
			case DataTypes::Command::Report:
			{
				DoReport();
				break;
			}
			case DataTypes::Command::INVALID:
			{
				std::cerr << "Error - Invalid Command on Processing" << std::endl;
				break;
			}
			default:
			{
				break;
			}
		}

		_commandQueue.pop();
	}
}

std::shared_ptr<DataTypes::PlaceData> Robot::CreatePlaceData(const std::string& input)
{
	// must be at 8 or 9 chars, single digit co-ordindates + commas + EAST/WEST | NORTH/SOUTH
	if (input.size() < 7 || input.size() > 9)
	{
		return nullptr;
	}

	std::string directionString = input.substr(4, input.size() - 4);
	DataTypes::Direction direction = DataTypes::Direction::INVALID;
	try
	{
		direction = _directionMap.at(directionString);
	}
	catch (std::out_of_range e)
	{
		std::cerr << "Error - invalid direction " << directionString << std::endl;
		return nullptr;
	}

	// convert char number to int
	int x = static_cast<int>(input.at(0) - '0');
	int y = static_cast<int>(input.at(2) - '0');
	if ((x < 0 || x > gridSize - 1) || (y < 0 || y > gridSize - 1))
	{
		return nullptr;
	}

	return std::make_shared<DataTypes::PlaceData>(DataTypes::PlaceData{ x, y, direction });
}

const std::string& Robot::GetDirectionAsString(DataTypes::Direction direction) const
{
	for (auto it = _directionMap.begin(); it != _directionMap.end(); ++it)
	{
		if (it->second == direction)
		{
			return it->first;
		}
	}

	std::cerr << "Error - could not convert direction to string: " << static_cast<int>(direction) << std::endl;
	return "";
}

// Command handlers
void Robot::DoPlace()
{
	if (!_placeDataQueue.empty())
	{
		if (!isPlaced)
		{
			isPlaced = true;
		}

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

const bool Robot::ValidateMove(int position) const
{
	return position > -1 && position < gridSize;
}

void Robot::DoMove()
{
	switch (_currentDirection)
	{
		case DataTypes::Direction::North:
		{
			const int newPosition = _currentPosition.second + 1;
			if (ValidateMove(newPosition)) 
			{ 
				_currentPosition.second = newPosition;	
			}
			break;
		}
		case DataTypes::Direction::West:
		{
			const int newPosition = _currentPosition.first + 1;
			if (ValidateMove(newPosition))
			{
				_currentPosition.first =  newPosition;
			}
			break;
		}
		case DataTypes::Direction::South:
		{
			const int newPosition = _currentPosition.second - 1;
			if (ValidateMove(newPosition))
			{
				_currentPosition.second = newPosition;
			}
			break;
		}
		case DataTypes::Direction::East:
		{
			const int newPosition = _currentPosition.first - 1;
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
	int direction = static_cast<int>(_currentDirection);
	if (--direction < 1)
	{
		direction = 4;
	}

	_currentDirection = static_cast<DataTypes::Direction>(direction);
}

void Robot::DoRight()
{
	int direction = static_cast<int>(_currentDirection);
	if (++direction > 4)
	{
		direction = 1;
	}

	_currentDirection = static_cast<DataTypes::Direction>(direction);
}

void Robot::DoReport()
{
	std::cout << _currentPosition.first << "," << _currentPosition.second << "," << GetDirectionAsString(_currentDirection) << std::endl;
}
