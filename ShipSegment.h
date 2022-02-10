#ifndef BATTLESHIP_CPP_SHIPSEGMENT_H
#define BATTLESHIP_CPP_SHIPSEGMENT_H

#include <utility>

/**
 * @brief Class representing a part of a ship on the board
 */
class ShipSegment {
    char x;
    int y;
    bool sunk;

public:
    ShipSegment(char x, int y);

    void sink();

    void unsink();

    bool isSunk();

    std::pair<char, int> getPosition();
};

#endif //BATTLESHIP_CPP_SHIPSEGMENT_H
