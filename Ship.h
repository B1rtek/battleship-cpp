#ifndef BATTLESHIP_CPP_SHIP_H
#define BATTLESHIP_CPP_SHIP_H

#include "ShipSegment.h"
#include <vector>
#include <string>

/**
 * @brief Class containing information about a single ship. It contains coordinates
 * of all its parts, and it can tell if it isSunk or not.
 */
class Ship {
    std::vector<ShipSegment> segments;
    int size;
    bool vertical;
    std::pair<char, int> origin;

public:
    Ship(std::pair<char, int> origin, int size, bool vertical);

    bool operator==(Ship other);

    std::vector<std::pair<char, int>> getSegmentCoordinates();

    bool checkIfBelongs(char x, int y);

    void sink(char x, int y);

    bool sunk();

    std::string toString(bool drawAsEnemy = false);

    std::vector<ShipSegment> getSegments();

    int getSize();

    bool isVertical();

    std::pair<char, int> getOrigin();
};

#endif //BATTLESHIP_CPP_SHIP_H
