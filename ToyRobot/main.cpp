/*
* Toy Robot
* 5 x 5 grid
* 
* Commands:
*     - PLACE X,Y, [NORTH, EAST, SOUTH, WEST]
*     - MOVE
*     - LEFT (rotate, not move)
*     - RIGHT (rotate, not move)
*     - REPORT (print position and direction)
* 
* (0,0) -> SOUTH WEST corner
* Must be placed first
* otherwise any sequence of commands can be issued

*/

#include "Robot.h"

#include <vector>

std::vector<std::string> formatCommandLineArgs(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	std::vector<std::string> commandLineArgs = formatCommandLineArgs(argc, argv);

	Robot robot;
	if (!robot.Initialise(commandLineArgs))
	{
		return -1;
	}

	robot.ProcessCommands();

	return 0;
}

std::vector<std::string> formatCommandLineArgs(int argc, char* argv[])
{
	std::vector<std::string> commandLineArgs;
	commandLineArgs.reserve(argc);

	for (int i = 1; i < argc; ++i)
	{
		commandLineArgs.push_back(argv[i]);
	}

	return commandLineArgs;
}
