#include "pch.h"

// need to explicity include entry point since we linked
// against and "executable" with its own entry point,
// yet we built it as a library
int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}