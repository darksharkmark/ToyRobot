#include <memory>
#include "Robot.h"

using namespace DataTypes;

bool Robot::Initialise(int argc, char* argv[])
{
	if (!ProcessInput(argc, argv))
	{
		return false;
	}

	while (!_instructions.empty())
	{
		Command instruction = _instructions.front();
		std::cout << CommandAsString(instruction) << std::endl;

		if (instruction == Command::Place)
		{
			if (!_placeDataContainer.empty())
			{
				auto& placeData = _placeDataContainer.front();
				placeData->Print();
				_placeDataContainer.pop();
			}
		}

		_instructions.pop();
	}

	return true;
}

bool Robot::ProcessInput(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cerr << "Error - no input found" << std::endl;
		return false;
	}

	std::cout << "args: " << std::endl;
	for (int i = 1; i < argc; ++i)
	{
		std::string rawCommand = argv[i];
		try
		{
			// catch below will handle invalid input
			Command command = _commandMap.at(rawCommand);
			_instructions.emplace(command);

			// not ideal but cant think of a better way, TODO: cleanup 
			if (command == Command::Place)
			{
				if (i < (argc - 1))
				{
					// should be X, Y, F
					std::string nextCommand = argv[++i];
					auto placeData = CreatePlaceData(nextCommand);
					_placeDataContainer.push(placeData);
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

std::shared_ptr<PlaceData> Robot::CreatePlaceData(std::string input)
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
