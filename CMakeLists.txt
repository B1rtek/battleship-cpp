cmake_minimum_required(VERSION 3.20)
project(battleship-cpp)

set(CMAKE_CXX_STANDARD 14)

add_executable(battleship main.cpp BoardFleet.cpp BoardFleet.h)
