#include "FleetCreator.h"

/**
 * @brief Creates game objects and variables needed to operate the fleet creator
 */
FleetCreator::FleetCreator() {
    this->board = Board();
    this->fleet = Fleet();
}

/**
 * @brief Adds the message about ship being selected to the messages vector
 */
void FleetCreator::messageShipSelected() {
    this->messages.push_back(FCMessage::SHIP_SELECTED);
}

/**
 * @brief Adds the message about failing to move a ship to the messages vector
 */
void FleetCreator::messageShipMoveFail() {
    this->messages.push_back(FCMessage::SHIP_MOVE_FAIL);
}

/**
 * @brief Adds the message about failing to rotate a ship to the messages vector
 */
void FleetCreator::messageShipRotationFail() {
    this->messages.push_back(FCMessage::SHIP_ROTATION_FAIL);
}

/**
 * @brief Adds the setup help content to the messages vector
 */
void FleetCreator::messageSetupHelp() {
    this->messages.push_back(FCMessage::SETUP_HELP);
}

/**
 * @brief Starts the Fleet Creator
 *
 * Creates a new random fleet and places it on the board
 */
void FleetCreator::start() {
    this->fleet.createRandom();
    this->board.placeFleet(this->fleet);
}

/**
 * @brief Handles the ship selecteion process in the board setup process
 * @param x x coordinate of a field
 * @param y y coordinate of a field
 */
void FleetCreator::selectShip(char x, int y) {
    bool result = this->fleet.selectShip(x, y);
    if (result) {
        this->messageShipSelected();
    }
}

/**
 * @brief Handles the ship position setting in the board setup process
 * @param x x coordinate of a field
 * @param y y coordinate of a field
 */
void FleetCreator::setShipPosition(char x, int y) {
    bool result = this->fleet.setShipPosition(x, y);
    if (!result) {
        this->messageShipMoveFail();
    } else {
        this->board.placeFleet(this->fleet);
    }
}

/**
 * @brief Handles the selected ship rotation change
 */
void FleetCreator::changeShipRotation() {
    bool result = this->fleet.changeShipRotation();
    if (!result) {
        this->messageShipRotationFail();
    } else {
        this->board.placeFleet(this->fleet);
    }
}

/**
 * @brief Handles the creation of a new random fleet
 */
void FleetCreator::randomFleet() {
    this->fleet.createRandom();
    this->board.placeFleet(this->fleet);
}

/**
 * @brief Handles the help command output
 */
void FleetCreator::setupHelp() {
    this->messageSetupHelp();
}

/**
 * @brief Checks if the specified field contains a ship that is not selected
 * @param x x coordinate of a field
 * @param y y coordinate of a field
 * @return true if this field does not contain a ship or contains a
 * selected one, false otherwise
 *
 * Used in the GUI version of the game to determine if the player selected
 * or wanted to move a ship
 */
bool FleetCreator::containsNotSelectedShip(char x, int y) {
    if (this->fleet.getSelectedShip() == nullptr) {
        return true;
    }
    if (this->fleet.getSelectedShip()->checkIfBelongs(x, y)) {
        return false;
    }
    if (this->fleet.findShip(x, y) != nullptr) {
        return true;
    }
    return false;
}

/**
 * @brief A getter for the messages vector used by the Battleship classes to get
 * the messages to display
 * @return a vector with all messages generated during last action
 */
std::vector<FCMessage> FleetCreator::getDisplayMessages() {
    std::vector<FCMessage> messagesToGet = this->messages;
    this->messages.clear();
    return messagesToGet;
}

/**
 * @return Board with the representation of the current setup
 */
Board FleetCreator::getBoardDisplay() {
    return this->board;
}

/**
 * @return a pair of the Board and Fleet created in the Fleet Creator
 *
 * called when the played uses the "done" command or clicks the
 * "Done" button
 */
std::pair<Board, Fleet> FleetCreator::getSetup() {
    return std::make_pair(this->board, this->fleet);
}

/**
 * @return Selected ship from the setup fleet
 */
Ship *FleetCreator::getSelectedShip() {
    return this->fleet.getSelectedShip();
}
