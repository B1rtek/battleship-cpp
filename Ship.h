#ifndef BATTLESHIP_CPP_SHIP_H
#define BATTLESHIP_CPP_SHIP_H

#include "ShipSegment.h"

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

    std::vector<std::pair<char, int>> getSegmentCoordinates();

    bool checkIfBelongs(char x, int y);

    void sink(char x, int y);

    bool sunk();

    std::string toString(bool drawAsEnemy);

    std::vector<ShipSegment> getSegments();

    int getSize();

    bool isVertical();

    std::pair<char, int> getOrigin();
};

#include <string>
#include <vector>
#include <set>
#include "Field.h"
#include "ShipSegment.h"

#endif //BATTLESHIP_CPP_SHIP_H