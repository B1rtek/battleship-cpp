cmake_minimum_required(VERSION 3.20)
project(battleship-cpp)

set(CMAKE_CXX_STANDARD 17)

set(PATH_TO_QT5 "D:\\Kody\\Qt5\\5.15.2\\mingw81_64") # path to your Qt5 directory goes here
if (WIN32)
    set(CMAKE_PREFIX_PATH ${PATH_TO_QT5})
endif (WIN32)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Core REQUIRED)

set(BASE_SOURCE_FILES src/Fleet.cpp include/Fleet.h src/Field.cpp include/Field.h src/Board.cpp include/Board.h src/GameBoard.cpp include/GameBoard.h src/ShipSegment.cpp include/ShipSegment.h src/Ship.cpp include/Ship.h src/Enemy.cpp include/Enemy.h src/Settings.cpp include/Settings.h src/FleetCreator.cpp include/FleetCreator.h src/Game.cpp include/Game.h src/BattleshipCLI.cpp include/BattleshipCLI.h)
set(GUI_SOURCE_FILES src/BattleshipGUI.cpp include/BattleshipGUI.h src/BoardButton.cpp include/BoardButton.h src/UIBoard.cpp include/UIBoard.h src/UIFleet.cpp include/UIFleet.h)

add_executable(battleship-cli main-cli.cpp ${BASE_SOURCE_FILES})
target_include_directories(battleship-cli PRIVATE ExtLibs include)
if (WIN32)
    set(EXECUTABLE_NAME "battleship-win32")
    add_executable(${EXECUTABLE_NAME} WIN32 main.cpp ${BASE_SOURCE_FILES} ${GUI_SOURCE_FILES})
    add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/WindowsQt5files ${CMAKE_CURRENT_BINARY_DIR})
endif (WIN32)
if (UNIX)
    set(EXECUTABLE_NAME "battleship-linux")
    add_executable(${EXECUTABLE_NAME} main.cpp ${BASE_SOURCE_FILES} ${GUI_SOURCE_FILES})
endif (UNIX)
target_include_directories(${EXECUTABLE_NAME} PRIVATE ExtLibs include)
target_link_libraries(${EXECUTABLE_NAME} Qt5::Widgets)
add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/res ${CMAKE_CURRENT_BINARY_DIR}/res)
