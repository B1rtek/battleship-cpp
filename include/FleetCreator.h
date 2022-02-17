#ifndef BATTLESHIP_CPP_FLEETCREATOR_H
#define BATTLESHIP_CPP_FLEETCREATOR_H

#include "Board.h"

enum FCMessage {
    SHIP_SELECTED, SHIP_MOVE_FAIL, SHIP_ROTATION_FAIL, SETUP_HELP
};

/**
 * @brief Class handling player board's setup in the setup phase of the game
 *
 * Acts as a layer between the core game classes and the player's inputs
 */
class FleetCreator {
    Board board;
    Fleet fleet;
    std::vector<FCMessage> messages;

    void messageShipSelected();

    void messageShipMoveFail();

    void messageShipRotationFail();

    void messageSetupHelp();

public:
    FleetCreator();

    void start();

    void selectShip(char x, int y);

    void setShipPosition(char x, int y);

    void changeShipRotation();

    void randomFleet();

    void setupHelp();

    bool containsNotSelectedShip(char x, int y);

    std::vector<FCMessage> getDisplayMessages();

    Board getBoardDisplay();

    std::pair<Board, Fleet> getSetup();

    Ship *getSelectedShip();
};

#endif //BATTLESHIP_CPP_FLEETCREATOR_H
