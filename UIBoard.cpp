#include "UIBoard.h"

/**
 * @brief Initializes all values and creates a button array
 */
UIBoard::UIBoard() {
    this->cachedBoard = Board();
    this->createButtonArray();
    this->initializeCachedBoard();
}

/**
 * @brief Creates the button array which will be shown in the GUI
 */
void UIBoard::createButtonArray() {
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            BoardButton *button = new BoardButton();
            std::pair<char, int> coords = arrayToGameCoords(x, y);
            button->setGameCoordinates(coords.first, coords.second);
            this->buttonArray[y][x] = button;
        }
    }
}

/**
 * @brief Initializes the internal cached Board
 *
 * Sets all fields' statuses to FieldStatus.SUNK to ensure that all buttons in this
 * UIBoard will refresh their state and start showing the correct start state as the
 * Setup phase or the Game begins, as the update_board() function only refreshes a
 * button if there was a change of state of it's corresponding field to improve
 * performance
 */
void UIBoard::initializeCachedBoard() {
    for (auto &field: returnAllFieldCoordinates()) {
        this->cachedBoard.setFieldStatus(field.first, field.second, FieldStatus::SUNK);
    }
}

/**
 * @brief Updates the displayed board by changing icons of the buttons which
 * corresponding fields' status has changed.
 * @param displayBoard display board from Game or FleetCreator
 * @param selectedShip Selected ship that will be marked in a special way on the
 * board, only used in the FleetCreator
 *
 * Only the fields with their status changed are updated to improve performance
 */
void UIBoard::updateBoard(Board displayBoard, Ship *selectedShip) {
    for (auto &field: returnAllFieldCoordinates()) {
        FieldStatus newStatus = displayBoard.getFieldStatus(field.first, field.second);
        if (this->cachedBoard.getFieldStatus(field.first, field.second) != newStatus) {
            std::pair<int, int> arrayCoords = gameToArrayCoords(field.first, field.second);
            this->buttonArray[arrayCoords.second][arrayCoords.first]->setIcon(this->icons[newStatus]);
            this->cachedBoard.setFieldStatus(field.first, field.second, newStatus);
        }
    }
    if (selectedShip != nullptr) {
        std::vector<std::pair<char, int>> selected = selectedShip->getSegmentCoordinates();
        for (auto &field: selected) {
            std::pair<int, int> arrayCoords = gameToArrayCoords(field.first, field.second);
            this->buttonArray[arrayCoords.second][arrayCoords.first]->setIcon(this->icons[FieldStatus::SELECTED]);
            this->cachedBoard.setFieldStatus(field.first, field.second, FieldStatus::SELECTED);
        }
    }
}

/**
 * @brief Creates the array in the actual window's UI
 * @param parentGridLayout grid layout in which the board will be placed
 */
void UIBoard::placeButtonArray(QGridLayout *parentGridLayout) {
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            parentGridLayout->addWidget(this->buttonArray[y][x], y, x);
        }
    }
}

/**
 * @brief Sets a function or a method that will be called when a button in this
 * UIBoard is clicked on with the left mouse button
 * @param leftClickAction a function or a method to assign to the buttons
 */
void UIBoard::defineLeftClickAction(std::function<void(char, int)> *leftClickAction) {
    for (auto &y: this->buttonArray) {
        for (auto &x: y) {
            x->setLeftClickAction(leftClickAction);
        }
    }
}

/**
 * @brief Sets a function or a method that will be called when a button in this
 * UIBoard is clicked on with the right mouse button
 * @param rightClickAction a function or a method to assign to the buttons
 */
void UIBoard::defineRightClickAction(std::function<void(char, int)> *rightClickAction) {
    for (auto &y: this->buttonArray) {
        for (auto &x: y) {
            x->setRightClickAction(rightClickAction);
        }
    }
}

/**
 * Sets the provided icons' map as the one used by this board
 * @param iconsMap map containing all icons needed to display the board
 */
void UIBoard::setIcons(std::map<FieldStatus, QIcon> iconsMap) {
    this->icons = iconsMap;
}
