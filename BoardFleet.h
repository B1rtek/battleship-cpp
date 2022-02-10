#ifndef BATTLESHIP_CPP_BOARDFLEET_H
#define BATTLESHIP_CPP_BOARDFLEET_H

#include <string>
#include <vector>
#include <set>

using namespace std;

enum FieldStatus {
    NOTHING, MISS, SHIP, SUNK, SELECTED
};

class Field {
    /*
     * Class that stores information about a field on a game board.
     */
    FieldStatus status;

public:
    Field();

    char toString();

    FieldStatus getStatus();

    void setStatus(FieldStatus newStatus);
};

pair<int, int> gameToArrayCoords(char x, int y);

set<pair<char, int>> returnAllFieldCoordinates();

bool fieldOnBoard(pair<char, int> field);

class ShipSegment {

public:
    pair<char, int> getPosition();
};

class Ship {

public:
    vector<ShipSegment> getSegments();
};

class Fleet {

public:
    vector<Ship> getShips();
};

class Board {
    /*
     * Class being an array of fields, representing a 10x10 board
     */
    Field fields[10][10]{};

public:
    Board();

    string toString();

    void clearBoard();

    void placeShip(Ship ship);

    void placeFleet(Fleet fleetToPlace);

    void markSunkenShip(Ship shipToSink);

    FieldStatus getFieldStatus(char x, int y);

    void setFieldStatus(char x, int y, FieldStatus status);
};

void markMissesAround(Ship ship, Board &placementBoard);

class GameBoard {
    /*
     * Board used in game, consists of two Boards, one of them being the data
     * board, visible for the player, and one of them being the visible board,
     * seen by the enemy, based on the data board.
     */
    Board dataBoard, visibleBoard;
public:
    explicit GameBoard(Board dataBoard);

    bool discoverField(char x, int y);

    bool markAsEmpty(char x, int y);

    bool unmarkAsEmpty(char x, int y);

    void sinkShip(Ship shipToSink);

    Board getDisplayBoard(bool displayAsEnemy = false);

    bool fieldUndiscovered(char x, int y);

    void markMissesAround(Ship shipToMarkAround);
};



#endif //BATTLESHIP_CPP_BOARDFLEET_H
