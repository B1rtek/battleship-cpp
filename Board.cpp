#include "Board.h"

/*
 * Function used to translate in-game coordinates (like 'a', 7) to board field
 * coordinates ('a' 7 is 0 6, since 'a' is the first column and 7 is the 7th
 * row, and computers count from 0)
 * x: x coordinate of the field, a letter from a to j
 * y: y coordinate of the field, a number from 1 to 10
 * returns: a tuple of coordinates translated to indices of the fields array
 */

std::pair<int, int> gameToArrayCoords(char x, int y) {
    x = int(x) < 97 ? x = char(int(x) + 32) : x;
    int cx = int(x) - 97;
    y -= 1;
    return std::make_pair(cx, y);
}

/*
 * Creates a 10x10 array with empty fields, which status can be set with
 * setFieldStatus() method
 */

Board::Board() {
    for (auto &row: fields) {
        for (auto &field: row) {
            field = Field();
        }
    }
}

/*
 * Creates a string representation of the board
 */

std::string Board::toString() {
    std::string boardStr = "   abcdefghij\n  +=-=-=-=-=-+\n";
    for (int i = 0; i < 10; i++) {
        std::string current;
        current += i + 1 < 9 ? ' ' + std::to_string(i + 1) : std::to_string(i + 1);
        char border = i % 2 == 0 ? '|' : char(186);
        current += border;
        for (int j = 0; j < 10; j++) {
            current += fields[i][j].toString();
        }
        current += border + '\n';
        boardStr += current;
    }
    boardStr += "  +=-=-=-=-=-+";
    return boardStr;
}

/*
 * Sets states of all fields in the board to FieldStatus::NOTHING
 */

void Board::clearBoard() {
    for (auto &row: this->fields) {
        for (auto &field: row) {
            field.setStatus(NOTHING);
        }
    }
}

/*
 * Places a ship on the board by marking all fields it occupies with a
 * status of FieldStatus::SHIP
 * ship: Ship to be placed
 */

void Board::placeShip(Ship ship) {
    vector<ShipSegment> segments = ship.getSegments();
    for (auto &segment: segments) {
        std::pair<char, int> position = segment.getPosition();
        this->setFieldStatus(position.first, position.second, SHIP);
    }
}

/*
 * Places ships defined in ships on the board
 * fleetToPlace: a Fleet containing player's ships
 */

void Board::placeFleet(Fleet fleetToPlace) {
    this->clearBoard();
    vector<Ship> ships = fleetToPlace.getShips();
    for (auto &ship: ships) {
        this->placeShip(ship);
    }
}

/*
 * Marks a given ship as a sunken ship on the board
 * shipToSink: Ship to be marked as sunken
 */

void Board::markSunkenShip(Ship shipToSink) {
    vector<ShipSegment> segments = shipToSink.getSegments();
    for (auto &segment: segments) {
        std::pair<char, int> position = segment.getPosition();
        this->setFieldStatus(position.first, position.second, SUNK);
    }
}

/*
 * Returns the status of a field on the specified coordinates
 * x: x coordinate of a field
 * y: y coordinate of a field
 * returns: status of the specified field
 */

FieldStatus Board::getFieldStatus(char x, int y) {
    std::pair<int, int> coords = gameToArrayCoords(x, y);
    FieldStatus status = this->fields[coords.first][coords.second].getStatus();
    return status;
}

/*
 * Sets the status of a field on the specified coordinates
 * x: x coordinate of a field
 * y: y coordinate of a field
 * status: new status of a field
 */

void Board::setFieldStatus(char x, int y, FieldStatus status) {
    std::pair<int, int> coords = gameToArrayCoords(x, y);
    this->fields[coords.first][coords.second].setStatus(status);
}

/*
 * Returns a list of tuples containing coordinates of all fields on the board
 * returns a list of 100 tuples with field coordinates
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

/*
 * Checks if given coordinates are a coordinates of a valid field on a board
 * field: tuple of a field's coordinates
 * returns: true if coordinates point to a field on the board, otherwise false
 */

bool fieldOnBoard(std::pair<char, int> field) {
    return returnAllFieldCoordinates().count(field);
}