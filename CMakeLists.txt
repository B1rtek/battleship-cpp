cmake_minimum_required(VERSION 3.20)
project(battleship-cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH "D:\\Kody\\Qt5\\5.15.2\\mingw81_64")

find_package(Qt5Widgets REQUIRED)

set(BASE_SOURCE_FILES Fleet.cpp Fleet.h Field.cpp Field.h Board.cpp Board.h GameBoard.cpp GameBoard.h ShipSegment.cpp ShipSegment.h Ship.cpp Ship.h Enemy.cpp Enemy.h Settings.cpp Settings.h FleetCreator.cpp FleetCreator.h Game.cpp Game.h BattleshipCLI.cpp BattleshipCLI.h)
set(GUI_SOURCE_FILES BattleshipGUI.cpp BattleshipGUI.h BoardButton.cpp BoardButton.h UIBoard.cpp UIBoard.h UIFleet.cpp UIFleet.h)

add_executable(battleship main.cpp ${BASE_SOURCE_FILES} ${GUI_SOURCE_FILES})
add_executable(battleship-cli main-cli.cpp ${BASE_SOURCE_FILES})
target_include_directories(battleship PRIVATE "ExtLibs")
target_include_directories(battleship-cli PRIVATE "ExtLibs")
target_link_libraries(battleship Qt5::Widgets)