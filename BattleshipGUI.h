#ifndef BATTLESHIP_CPP_BATTLESHIPGUI_H
#define BATTLESHIP_CPP_BATTLESHIPGUI_H

#include <QtWidgets/QMainWindow>
#include "ui_battleship.h"
#include "BattleshipCLI.h"

/**
 * @brief Class operating the game in the GUI version
 */
class BattleshipGUI : QMainWindow {
    Ui_Battleship ui;
    FleetCreator fleetCreator;
    Game game;
    Settings settings;
};

#endif //BATTLESHIP_CPP_BATTLESHIPGUI_H
