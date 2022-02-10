#include "GameBoard.h"
#include "Ship.h"

/**
 * @brief Creates a GameBoard, by taking a data board and creating a visible
 * board for it
 * @param dataBoard raw board with all positions of the ships etc.
 */
GameBoard::GameBoard(Board dataBoard) {
    this->dataBoard = dataBoard;
    this->visibleBoard = Board();
}

/**
 * @brief Discovers a field when a player decides to shoot at it
 * @param x x coordinate of the field
 * @param y y coordinate of the field
 * @returns true if there was a hit, false if it was a miss. The return
 * value will be used to check which ship has been hit, and if that ship
 * sunk because of it
 */
bool GameBoard::discoverField(char x, int y) {
    FieldStatus fieldStatus = this->dataBoard.getFieldStatus(x, y);
    if (fieldStatus == NOTHING) {
        fieldStatus = MISS;
        this->dataBoard.setFieldStatus(x, y, fieldStatus);
    }
    this->visibleBoard.setFieldStatus(x, y, fieldStatus);
    if (fieldStatus == SHIP) {
        fieldStatus = SUNK;
        this->dataBoard.setFieldStatus(x, y, fieldStatus);
        return true;
    }
    return false;
}

/**
 * @brief Marks a field as empty (with a miss) on the visible board, as a visual
 * indicator for a player, only if the field that is being marked has
 * nothing on it
 * @param x x coordinate of the field
 * @param y y coordinate of the field
 * @returns true if the field was marked, false if it wasn't due to it
 * containing a ship
 */
bool GameBoard::markAsEmpty(char x, int y) {
    FieldStatus currentStatus = this->visibleBoard.getFieldStatus(x, y);
    if (currentStatus != NOTHING) {
        return false;
    }
    this->visibleBoard.setFieldStatus(x, y, MISS);
    return true;
}

/**
 * @brief Removes the marker from the specified field
 * @param x x coordinate of the field
 * @param y y coordinate of the field
 * @returns true if the field was marked, False if it wasn't due to it
 * containing a ship
 */
bool GameBoard::unmarkAsEmpty(char x, int y) {
    FieldStatus currentStatus = this->visibleBoard.getFieldStatus(x, y);
    if (currentStatus != MISS) {
        return false;
    }
    this->visibleBoard.setFieldStatus(x, y, NOTHING);
    return true;
}

/**
 * @brief Called when a ship in a fleet has sunk to mark him as sunk on the map
 * @param shipToSink Ship to be sunk
 */
void GameBoard::sinkShip(Ship shipToSink) {
    this->dataBoard.markSunkenShip(shipToSink);
    this->visibleBoard.markSunkenShip(shipToSink);
}

/**
 * @brief Creates a data board representing what the specified player would see
 * @param displayAsEnemy if set to True, the data will reflect what the
 * enemy would see, otherwise it'll look like what the player should see
 * @returns a Board containing data necessary to draw this board on the
 * screen
 */
Board GameBoard::getDisplayBoard(bool displayAsEnemy) {
    Board displayBoard;
    if (displayAsEnemy) {
        displayBoard = this->visibleBoard;
    } else {
        displayBoard = Board();
        for (auto field: returnAllFieldCoordinates()) {
            FieldStatus status = this->dataBoard.getFieldStatus(field.first, field.second);
            if(status == NOTHING) {
                status = this->visibleBoard.getFieldStatus(field.first, field.second);
            }
            displayBoard.setFieldStatus(field.first, field.second, status);
        }
    }
    return displayBoard;
}

/**
 * @brief Checks if a field on the specified coordinates is undiscovered
 * @param x x coordinate of the field
 * @param y y coordinate of the field
 * @returns true if the specified field is undiscovered, false otherwise
 */
bool GameBoard::fieldUndiscovered(char x, int y) {
    return this->visibleBoard.getFieldStatus(x, y) == NOTHING;
}

/**
 * @brief Marks misses around the specified Ship
 * @param shipToMarkAround Ship to mark misses around
 */
void GameBoard::markMissesAround(Ship shipToMarkAround) {
    ::markMissesAround(shipToMarkAround, this->visibleBoard);
    this->sinkShip(shipToMarkAround);
}