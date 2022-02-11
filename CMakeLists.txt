cmake_minimum_required(VERSION 3.20)
project(battleship-cpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(battleship main.cpp Fleet.cpp Fleet.h Field.cpp Field.h Board.cpp Board.h GameBoard.cpp GameBoard.h ShipSegment.cpp ShipSegment.h Ship.cpp Ship.h Enemy.cpp Enemy.h Settings.cpp Settings.h)
target_include_directories(battleship PRIVATE "ExtLibs")