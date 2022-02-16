#include "UIFleet.h"

/**
 * @brief Initializes all values and creates a button array
 */
UIFleet::UIFleet() {
    this->cachedFleet = Fleet();
    this->positionsArray[0] = std::vector<std::pair<int, int>>{{0, 0},
                                                               {1, 0},
                                                               {2, 0},
                                                               {3, 0}};
    this->positionsArray[1] = std::vector<std::pair<int, int>>{{5, 0},
                                                               {6, 0},
                                                               {7, 0}};
    this->positionsArray[2] = std::vector<std::pair<int, int>>{{9,  0},
                                                               {10, 0},
                                                               {11, 0}};
    this->positionsArray[3] = std::vector<std::pair<int, int>>{{0, 1},
                                                               {1, 1}};
    this->positionsArray[4] = std::vector<std::pair<int, int>>{{3, 1},
                                                               {4, 1}};
    this->positionsArray[5] = std::vector<std::pair<int, int>>{{12, 1},
                                                               {13, 1}};
    this->positionsArray[6] = std::vector<std::pair<int, int>>{{6, 1}};
    this->positionsArray[7] = std::vector<std::pair<int, int>>{{8, 1}};
    this->positionsArray[8] = std::vector<std::pair<int, int>>{{10, 1}};
    this->positionsArray[9] = std::vector<std::pair<int, int>>{{13, 0}};
    this->createButtonArray();
    this->initializeCachedFleet();
}

/**
 * @brief Creates the button array which will be shown in the GUI
 */
void UIFleet::createButtonArray() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < this->positionsArray[i].size(); j++) {
            BoardButton *button = new BoardButton();
            button->setGameCoordinates(' ', 0);
            this->buttonArray[i][j] = button;
        }
    }
}

/**
 * @brief Initializes the cached Fleet
 *
 * Sets all segments' statuses to FieldStatus.SUNK to ensure that all display buttons
 * in this UIFleet will refresh their state and start showing the correct start state
 * at the beginning of the game, as the updateBoard() function only refreshes a button
 * if there was a change of state of it's corresponding ShipSegment to improve
 * performance
 */
void UIFleet::initializeCachedFleet() {
    this->cachedFleet.createRandom();
    std::vector<Ship> *ships = cachedFleet.getShips();
    for (auto &ship: *ships) {
        std::vector<ShipSegment> *segments = ship.getSegments();
        for (auto &segment: *segments) {
            segment.sink();
        }
    }
}

/**
 * @brief Updates the displayed fleet by changing icons of the buttons which
 * corresponding fields' status has changed.
 * @param displayFleet display Fleet from Game
 *
 * Only the fields with their status changed are updated to improve performance
 */
void UIFleet::updateFleetDisplay(Fleet displayFleet) {
    std::vector<Ship> *ships = displayFleet.getShips();
    std::vector<Ship> *cachedShips = this->cachedFleet.getShips();
    for (int shipNum = 0; shipNum < 10; shipNum++) {
        std::vector<ShipSegment> *segments = ships->at(shipNum).getSegments();
        std::vector<ShipSegment> *cachedSegments = cachedShips->at(shipNum).getSegments();
        for (int segmentNum = 0; segmentNum < this->positionsArray[shipNum].size(); segmentNum++) {
            ShipSegment segment = segments->at(segmentNum);
            ShipSegment cachedSegment = cachedSegments->at(segmentNum);
            if (cachedSegment.isSunk() != segment.isSunk()) {
                if (segment.isSunk()) {
                    this->buttonArray[shipNum][segmentNum]->setIcon(this->icons[FieldStatus::SUNK]);
                    cachedSegment.sink();
                } else {
                    this->buttonArray[shipNum][segmentNum]->setIcon(this->icons[FieldStatus::SHIP]);
                    cachedSegment.unsink();
                }
            }
        }
    }
}

/**
 * @brief Creates the array in the actual window's UI
 * @param parentGridLayout grid layout in which the fleet will be placed
 */
void UIFleet::placeButtonArray(QGridLayout *parentGridLayout) {
    for (int i = 0; i < 10; i++) {
        for (int bIndex = 0; bIndex < this->positionsArray[i].size(); bIndex++) {
            std::pair<int, int> position = positionsArray[i][bIndex];
            parentGridLayout->addWidget(this->buttonArray[i][bIndex], position.second, position.first);
        }
    }
}

/**
 * @brief Sets a function or a method that will be called when a button in this
 * UIFleet is clicked on with the left mouse button
 * @param leftClickAction a function or a method to assign to the buttons
 */
void UIFleet::defineLeftClickAction(std::function<void(char, int)> *leftClickAction) {
    for (auto &y: this->buttonArray) {
        for (auto &x: y) {
            x->setLeftClickAction(leftClickAction);
        }
    }
}

/**
 * @brief Sets a function or a method that will be called when a button in this
 * UIFleet is clicked on with the right mouse button
 * @param rightClickAction a function or a method to assign to the buttons
 */
void UIFleet::defineRightClickAction(std::function<void(char, int)> *rightClickAction) {
    for (auto &y: this->buttonArray) {
        for (auto &x: y) {
            x->setRightClickAction(rightClickAction);
        }
    }
}

/**
 * Sets the provided icons' map as the one used by this fleet display
 * @param iconsMap map containing all icons needed to display the fleet
 */
void UIFleet::setIcons(std::map<FieldStatus, QIcon> iconsMap) {
    this->icons = iconsMap;
}


