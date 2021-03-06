#ifndef BATTLESHIP_CPP_BOARD_H
#define BATTLESHIP_CPP_BOARD_H

/// Needed because linker gets angry
class Fleet;

#include <string>
#include <set>
#include "Field.h"
#include "Ship.h"
#include "Fleet.h"

std::pair<int, int> gameToArrayCoords(char x, int y);

std::set<std::pair<char, int>> returnAllFieldCoordinates();

bool fieldOnBoard(std::pair<char, int> field);

/**
 * @brief Class being an array of fields, representing a 10x10 board
 */
class Board {
    Field fields[10][10]{};

public:
    Board();

    std::string toString();

    void clearBoard();

    void placeShip(Ship ship);

    void placeFleet(Fleet fleetToPlace);

    void markSunkenShip(Ship shipToSink);

    FieldStatus getFieldStatus(char x, int y);

    void setFieldStatus(char x, int y, FieldStatus status);
};

#endif //BATTLESHIP_CPP_BOARD_H
