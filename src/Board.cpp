#include "Board.h"

/**
 * @brief Function used to translate in-game coordinates to board field coordinates
 * coordinates
 * @param x x coordinate of the field, a letter from a to j
 * @param y y coordinate of the field, a number from 1 to 10
 * @returns a pair of coordinates translated to indices of the fields array
 *
 * Example: 'a' 7 gets translated to 6 0, since 'a' is the first column and 7 is the
 * 7th row, and computers count from 0, and the coordinates are stored as [y][x]
 */
std::pair<int, int> gameToArrayCoords(char x, int y) {
    if (int(x) < 97) x = char(int(x) + 32);
    int cx = int(x) - 97;
    y -= 1;
    return std::make_pair(y, cx);
}

/**
 * @brief Creates a 10x10 array with empty fields, which status can be set with
 * setFieldStatus() method
 */
Board::Board() {
    for (auto &row: fields) {
        for (auto &field: row) {
            field = Field();
        }
    }
}

/**
 * @brief Creates a string representation of the board
 */
std::string Board::toString() {
    std::string boardStr = "   abcdefghij\n  +=-=-=-=-=-+\n";
    for (int i = 0; i < 10; i++) {
        std::string current;
        current += i + 1 < 10 ? ' ' + std::to_string(i + 1) : std::to_string(i + 1);
        char border = i % 2 == 0 ? '|' : char(186);
        current += border;
        for (int j = 0; j < 10; j++) {
            current += fields[i][j].toString();
        }
        current += border;
        current += '\n';
        boardStr += current;
    }
    boardStr += "  +=-=-=-=-=-+";
    return boardStr;
}

/**
 * @brief Sets states of all fields in the board to FieldStatus::NOTHING
 */
void Board::clearBoard() {
    for (auto &row: this->fields) {
        for (auto &field: row) {
            field.setStatus(NOTHING);
        }
    }
}

/**
 * @brief Places a ship on the board
 * @param ship Ship to be placed
 *
 * Marks all fields the new ship occupies with a status of FieldStatus::SHIP
 */
void Board::placeShip(Ship ship) {
    std::vector<ShipSegment> *segments = ship.getSegments();
    for (auto &segment: *segments) {
        std::pair<char, int> position = segment.getPosition();
        this->setFieldStatus(position.first, position.second, SHIP);
    }
}

/**
 * @brief Places ships defined in ships on the board
 * @param fleetToPlace a Fleet containing player's ships
 */
void Board::placeFleet(Fleet fleetToPlace) {
    this->clearBoard();
    std::vector<Ship> *ships = fleetToPlace.getShips();
    for (auto &ship: *ships) {
        this->placeShip(ship);
    }
}

/**
 * @brief Marks a given ship as a sunken ship on the board
 * @param shipToSink Ship to be marked as sunken
 */
void Board::markSunkenShip(Ship shipToSink) {
    std::vector<ShipSegment> *segments = shipToSink.getSegments();
    for (auto &segment: *segments) {
        std::pair<char, int> position = segment.getPosition();
        this->setFieldStatus(position.first, position.second, SUNK);
    }
}

/**
 * @brief Returns the status of a field on the specified coordinates
 * @param x x coordinate of a field
 * @param y y coordinate of a field
 * @returns status of the specified field
 */
FieldStatus Board::getFieldStatus(char x, int y) {
    std::pair<int, int> coords = gameToArrayCoords(x, y);
    FieldStatus status = this->fields[coords.first][coords.second].getStatus();
    return status;
}

/**
 * @brief Sets the status of a field on the specified coordinates
 * @param x x coordinate of a field
 * @param y y coordinate of a field
 * @param status new status of a field
 */
void Board::setFieldStatus(char x, int y, FieldStatus status) {
    std::pair<int, int> coords = gameToArrayCoords(x, y);
    this->fields[coords.first][coords.second].setStatus(status);
}

/**
 * @brief Returns a vector of pairs containing coordinates of all fields on the board
 * @returns a set of 100 pairs with field coordinates
 */
std::set<std::pair<char, int>> returnAllFieldCoordinates() {
    std::set<std::pair<char, int>> allFields;
    for (char x = 'a'; x <= 'j'; x++) {
        for (int y = 1; y <= 10; y++) {
            allFields.insert(std::make_pair(x, y));
        }
    }
    return allFields;
}

/**
 * @brief Checks if given coordinates are a coordinates of a valid field on a board
 * @param field a field's coordinates
 * @returns true if coordinates point to a field on the board, otherwise false
 */
bool fieldOnBoard(std::pair<char, int> field) {
    return returnAllFieldCoordinates().count(field);
}
