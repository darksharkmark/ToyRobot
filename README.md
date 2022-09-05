# ToyRobot
The application is a simulation of a toy robot moving on a square table top, of dimensions 5 units x 5 units. 

## Building the Application
Visual Studio 2019

## Usage
- Input is processed via commandline e.g.
  - ./ToyRobot.exe PLACE 1,2,NORTH 
  - ./ToyRobot.exe PLACE 3,4,EAST MOVE REPORT
 

## Coding Methodolgies
- Early Return pattern
  - validate input as easrly as possible to avoid wasted compute
  - since input is validated early, we can assume clean data later on
- Focusing on code readability over effeciency
- makes use of the std library where appropriate

