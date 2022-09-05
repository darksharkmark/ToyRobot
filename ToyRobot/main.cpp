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


#include "Robot.h"

int main(int argc, char* argv[])
{
	Robot robot;
	if (!robot.Initialise(argc, argv))
	{
		return -1;
	}

	return 0;
}

