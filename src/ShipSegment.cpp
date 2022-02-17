#include "../include/ShipSegment.h"

/**
 * @brief Creates a segment setting its position and status to not sunk
 * @param x x coordinate of this segment
 * @param y y coordinate of this segment
 */
ShipSegment::ShipSegment(char x, int y) {
    this->x = x;
    this->y = y;
    this->sunk = false;
}

/**
 * @brief Sinks this segment by setting its sunk value to true
 */
void ShipSegment::sink() {
    this->sunk = true;
}

/**
 * @brief "Unsinks" this segment by setting its _sunk value to false
 *
 * Used to initialize the Fleet displays in the UI version, since they only
 * refresh when there is a change in the state of the fleet, so to begin
 * the game all ships must be sunk for the displays to update
 */
void ShipSegment::unsink() {
    this->sunk = false;
}

bool ShipSegment::isSunk() {
    return this->sunk;
}

/**
 * @returns a pair representing this segment's position
 */
std::pair<char, int> ShipSegment::getPosition() {
    return std::make_pair(this->x, this->y);
}
