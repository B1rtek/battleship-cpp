cmake_minimum_required(VERSION 3.20)
project(battleship-cpp)

set(CMAKE_CXX_STANDARD 17)

set(PATH_TO_QT5 "D:\\Kody\\Qt5\\5.15.2\\mingw81_64") # path to your Qt5 directory goes here
if(WIN32)
    set(CMAKE_PREFIX_PATH ${PATH_TO_QT5})
endif(WIN32)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Core REQUIRED)

set(BASE_SOURCE_FILES Fleet.cpp Fleet.h Field.cpp Field.h Board.cpp Board.h GameBoard.cpp GameBoard.h ShipSegment.cpp ShipSegment.h Ship.cpp Ship.h Enemy.cpp Enemy.h Settings.cpp Settings.h FleetCreator.cpp FleetCreator.h Game.cpp Game.h BattleshipCLI.cpp BattleshipCLI.h)
set(GUI_SOURCE_FILES BattleshipGUI.cpp BattleshipGUI.h BoardButton.cpp BoardButton.h UIBoard.cpp UIBoard.h UIFleet.cpp UIFleet.h)

add_executable(battleship-cli main-cli.cpp ${BASE_SOURCE_FILES})
target_include_directories(battleship-cli PRIVATE "ExtLibs")
if(WIN32)
    add_executable(battleship-win32 WIN32 main.cpp ${BASE_SOURCE_FILES} ${GUI_SOURCE_FILES})
    target_include_directories(battleship-win32 PRIVATE "ExtLibs")
    target_link_libraries(battleship-win32 Qt5::Widgets Qt5::Gui Qt5::Core)
endif(WIN32)
if(UNIX)
    add_executable(battleship-linux main.cpp ${BASE_SOURCE_FILES} ${GUI_SOURCE_FILES})
    target_include_directories(battleship-linux PRIVATE "ExtLibs")
    target_link_libraries(battleship-linux Qt5::Widgets Qt5::Gui Qt5::Core)
endif(UNIX)

