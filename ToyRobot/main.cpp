#include "Robot.h"
#include <vector>

std::vector<std::string> formatCommandLineArgs(int argc, char* argv[]);

int main(int argc, char* argv[])
{
	const std::vector<std::string>& commandLineArgs = formatCommandLineArgs(argc, argv);

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
	commandLineArgs.reserve(argc - 1);

	for (int i = 1; i < argc; ++i)
	{
		commandLineArgs.push_back(argv[i]);
	}

	return commandLineArgs;
}
