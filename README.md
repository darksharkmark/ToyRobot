# ToyRobot
The application is a simulation of a toy robot moving on a square table top, of dimensions 5 units x 5 units. 
gtest 

## Dependencies
- GTest https://github.com/google/googletest
- GoogleTestAdapter Visual studio extension https://github.com/csoltenborn/GoogleTestAdapter
  - [see usage here](https://github.com/csoltenborn/GoogleTestAdapter#usage)

## Building the Application
- Visual Studio 2019, run ToyRobot Project

## Usage
- Input is processed via command line in order e.g.
  - ./ToyRobot.exe PLACE 0,0,NORTH 
  - ./ToyRobot.exe PLACE 3,4,EAST MOVE REPORT
 
## Tests
- using Gtest Framework
- There is a specific Post Build step in the Main project to build the executable as a library, then we can link that library against our Test project
  - ToyRobot Project > Properties > Configuration Properties > Build Events > Post Build Event > Command Line
    - lib /NOLOGO /OUT:"$(OutDir)$(TargetName).lib"

## Coding Methodolgies
- Early Return pattern
  - validate input as early as possible to avoid wasted compute
  - since input is validated early, we can assume clean data later on
- Focusing on code readability over effeciency
- makes use of the std library where appropriate

## Improvements
- State can stored as a file or other means if necesarry

## Known Issues
- Release x64 will not build
- Some tests are failing, I have left them in as talking points about the program