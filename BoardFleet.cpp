#include "BoardFleet.h"

/*
 * Initializes a field, assigning it a status of FieldStatus::NOTHING
 */

Field::Field() {
    this->status = FieldStatus::NOTHING;
}

/*
 * Used to print out the fields in the console
 * returns: a character representing a field's status
 */

char Field::toString() {
    char representations[5] = {' ', '.', char(219), char(177), '#'};
    return representations[this->status];
}

FieldStatus Field::getStatus() {
    return this->status;
}

void Field::setStatus(FieldStatus newStatus) {
    this->status = newStatus;
}

/*
 * Function used to translate in-game coordinates (like 'a', 7) to board field
 * coordinates ('a' 7 is 0 6, since 'a' is the first column and 7 is the 7th
 * row, and computers count from 0)
 * x: x coordinate of the field, a letter from a to j
 * y: y coordinate of the field, a number from 1 to 10
 * returns: a tuple of coordinates translated to indices of the fields array
 */

pair<int, int> gameToArrayCoords(char x, int y) {
    x = int(x) < 97 ? x = char(int(x) + 32) : x;
    int cx = int(x) - 97;
    y -= 1;
    return make_pair(cx, y);
}

/*
 * Returns a list of tuples containing coordinates of all fields on the board
 * returns a list of 100 tuples with field coordinates
 */

set<pair<char, int>> returnAllFieldCoordinates() {
    set<pair<char, int>> allFields;
    for (char x = 'a'; x <= 'j'; x++) {
        for (int y = 1; y <= 10; y++) {
            allFields.insert(make_pair(x, y));
        }
    }
    return allFields;
}

/*
 * Checks if given coordinates are a coordinates of a valid field on a board
 * field: tuple of a field's coordinates
 * returns: true if coordinates point to a field on the board, otherwise false
 */

bool fieldOnBoard(pair<char, int> field) {
    return returnAllFieldCoordinates().count(field);
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

string Board::toString() {
    string boardStr = "   abcdefghij\n  +=-=-=-=-=-+\n";
    for (int i = 0; i < 10; i++) {
        string current;
        current += i + 1 < 9 ? ' ' + to_string(i + 1) : to_string(i + 1);
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
            field.setStatus(FieldStatus::NOTHING);
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
        pair<char, int> position = segment.getPosition();
        this->setFieldStatus(position.first, position.second, FieldStatus::SHIP);
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
        pair<char, int> position = segment.getPosition();
        this->setFieldStatus(position.first, position.second, FieldStatus::SUNK);
    }
}

/*
 * Returns the status of a field on the specified coordinates
 * x: x coordinate of a field
 * y: y coordinate of a field
 * returns: status of the specified field
 */

FieldStatus Board::getFieldStatus(char x, int y) {
    pair<int, int> coords = gameToArrayCoords(x, y);
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
    pair<int, int> coords = gameToArrayCoords(x, y);
    this->fields[coords.first][coords.second].setStatus(status);
}

/*
 * Marks fields around the Ship with FieldStatus::MISS to prevent ships from
 * generating directly next to each other
 * ship: Ship around which the fields will be marked
 * placement_board: Board on which the fields will be marked
 */

void markMissesAround(Ship ship, Board &placementBoard) {
    //todo
}

/*
 * Creates a GameBoard, by taking a data board and creating a visible
 * board for it
 * dataBoard: raw board with all positions of the ships etc.
 */

GameBoard::GameBoard(Board dataBoard) {
    this->dataBoard = dataBoard;
    this->visibleBoard = Board();
}

/*
 * Discovers a field when a player decides to shoot at it
 * x: x coordinate of the field
 * y: y coordinate of the field
 * returns: true if there was a hit, false if it was a miss. The return
 * value will be used to check which ship has been hit, and if that ship
 * sunk because of it
 */

bool GameBoard::discoverField(char x, int y) {
    FieldStatus fieldStatus = this->dataBoard.getFieldStatus(x, y);
    if (fieldStatus == FieldStatus::NOTHING) {
        fieldStatus = FieldStatus::MISS;
        this->dataBoard.setFieldStatus(x, y, fieldStatus);
    }
    this->visibleBoard.setFieldStatus(x, y, fieldStatus);
    if (fieldStatus == FieldStatus::SHIP) {
        fieldStatus = FieldStatus::SUNK;
        this->dataBoard.setFieldStatus(x, y, fieldStatus);
        return true;
    }
    return false;
}

/*
 * Marks a field as empty (with a miss) on the visible board, as a visual
 * indicator for a player, only if the field that is being marked has
 * nothing on it
 * x: x coordinate of the field
 * y: y coordinate of the field
 * returns: true if the field was marked, false if it wasn't due to it
 * containing a ship
 */

bool GameBoard::markAsEmpty(char x, int y) {
    FieldStatus currentStatus = this->visibleBoard.getFieldStatus(x, y);
    if (currentStatus != FieldStatus::NOTHING) {
        return false;
    }
    this->visibleBoard.setFieldStatus(x, y, FieldStatus::MISS);
    return true;
}

/*
 * Removes the marker from the specified field
 * x: x coordinate of the field
 * y: y coordinate of the field
 * returns: true if the field was marked, False if it wasn't due to it
 * containing a ship
 */

bool GameBoard::unmarkAsEmpty(char x, int y) {
    FieldStatus currentStatus = this->visibleBoard.getFieldStatus(x, y);
    if (currentStatus != FieldStatus::MISS) {
        return false;
    }
    this->visibleBoard.setFieldStatus(x, y, FieldStatus::NOTHING);
    return true;
}

/*
 * Called when a ship in a fleet has sunk to mark him as sunk on the map
 * shipToSink: Ship to be sunk
 */

void GameBoard::sinkShip(Ship shipToSink) {
    this->dataBoard.markSunkenShip(shipToSink);
    this->visibleBoard.markSunkenShip(shipToSink);
}

/*
 * Creates a data board representing what the specified player would see
 * displayAsEnemy: if set to True, the data will reflect what the
 * enemy would see, otherwise it'll look like what the player should see
 * returns: a Board containing data necessary to draw this board on the
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
            if(status == FieldStatus::NOTHING) {
                status = this->visibleBoard.getFieldStatus(field.first, field.second);
            }
            displayBoard.setFieldStatus(field.first, field.second, status);
        }
    }
    return displayBoard;
}

/*
 * Checks if a field on the specified coordinates is undiscovered
 * x: x coordinate of the field
 * y: y coordinate of the field
 * returns: true if the specified field is undiscovered, false otherwise
 */

bool GameBoard::fieldUndiscovered(char x, int y) {
    return this->visibleBoard.getFieldStatus(x, y) == FieldStatus::NOTHING;
}

/*
 * Marks misses around the specified Ship
 * shipToMarkAround: Ship to mark misses around
 */

void GameBoard::markMissesAround(Ship shipToMarkAround) {
    ::markMissesAround(shipToMarkAround, this->visibleBoard);
    this->sinkShip(shipToMarkAround);
}













