#ifndef BATTLESHIP_CPP_BATTLESHIPGUI_H
#define BATTLESHIP_CPP_BATTLESHIPGUI_H

#include <QtWidgets/QMainWindow>
#include "ui_battleship.h"
#include "BattleshipCLI.h"
#include "UIBoard.h"
#include "UIFleet.h"

std::map<FieldStatus, QIcon> loadIcons();

/**
 * @brief Class operating the game in the GUI version
 */
class BattleshipGUI : public QMainWindow {
    Ui_Battleship ui;
    FleetCreator fleetCreator;
    Game game;
    UIBoard fleetCreatorBoard;
    UIBoard gamePlayerBoard;
    UIBoard gameEnemyBoard;
//    UIFleet gamePlayerFleet;
//    UIFleet gameEnemyFleet;
    Settings settings;

    void setupBoards();

    void setupFleetDisplays();

    void linkButtons();

    void applySettings();

    void fixPySide2UICBug();

    void resizeWindow();

    void fleetCreatorStart();

    void HTPShow();

    void returnToMain();

    void fleetCreatorLeftClick(char x, int y);

    void fleetCreatorRand();

    void fleetCreatorRot();

    void fleetCreatorDone();

    void fleetCreatorRefresh();

    void gameLeftClick(char x, int y);

    void gameRightClick(char x, int y);

    void gameRefresh();

    void settingsShow();

    void settingsToggleMMA();

    void settingsToggleHardEnemy();

    void settingsSaveAndBack();

    void quit();

public:
    explicit BattleshipGUI(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *event) override;
};

#endif //BATTLESHIP_CPP_BATTLESHIPGUI_H
