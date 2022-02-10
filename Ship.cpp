#include "Ship.h"

/**
 * @brief Creates a ship according to the given parameters
 * @param origin The position of the upper left segment of the ship
 * @param size length of the ship
 * @param vertical If set to true, the ship will be created vertically,
 * otherwise it'll be created horizontally, by default set to true
 */
Ship::Ship(std::pair<char, int> origin, int size, bool vertical) {
    this->size = size;
    this->vertical = vertical;
    this->origin = origin;
    std::vector<std::pair<char, int>> fieldCoordinates;
    if (vertical) {
        for (int y = origin.second; y < origin.second + size; y++) {
            fieldCoordinates.emplace_back(origin.first, y);
        }
    } else {
        for (char x = origin.first; x < char(int(origin.first) + size); x++) {
            fieldCoordinates.emplace_back(x, origin.second);
        }
    }
    for (auto &i: fieldCoordinates) {
        this->segments.emplace_back(i.first, i.second);
    }
}

/**
 * @brief Equality operator, used in some cases to compare Ships.
 * @param other ship to compare against
 * @return true if both ships are equal, false if they aren't
 */
bool Ship::operator==(Ship other) {
    return (this->origin == other.getOrigin() && this->size == other.getSize() && this->vertical == other.isVertical());
}

/**
 * @brief Returns coordinates of segments that make this Ship
 * @returns a vector of pairs with segment coordinates
 */
std::vector<std::pair<char, int>> Ship::getSegmentCoordinates() {
    std::vector<std::pair<char, int>> segmentsToGet;
    for (auto &i: this->segments) {
        segmentsToGet.push_back(i.getPosition());
    }
    return segmentsToGet;
}

/**
 * @brief Checks if the given coordinates belong to any of this Ship's segments
 * @param x x coordinate of a field
 * @param y y coordinate of a field
 * @return true if the given coordinates belong to this Ship,
 * otherwise false
 */
bool Ship::checkIfBelongs(char x, int y) {
    for (auto &i: segments) {
        if (i.getPosition() == std::make_pair(x, y)) {
            return true;
        }
    }
    return false;
}

/**
 * Sinks the specified segment of this ship.
 * @note Always called after check_if_belongs
 * @param x x coordinate of a segment
 * @param y y coordinate of a segment
 */
void Ship::sink(char x, int y) {
    for (auto &i: segments) {
        if (i.getPosition() == std::make_pair(x, y)) {
            i.sink();
            return;
        }
    }
}

/**
 * @brief Checks if this Ship sunk or not
 * @return true if it sunk, dalse otherwise
 *
 * Check is performed by checking each segment, and if they all sunk,
 * the Ship did as well
 */
bool Ship::sunk() {
    for (auto &i: segments) {
        if (!i.isSunk()) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Prints out a representation of the ship's condition in a graphical form
 * @param drawAsEnemy if set to true, the ship will be drawn as a sunk
 * one or undamaged one, to not indicate which part has been struck to the
 * enemy, false by default
 * @return a string representing this Ship
 *
 * For example, "████" represents a ship of size 4 without any damage,
 * "█▒▒" represents a ship of size 3 with two of its segments destroyed
 */
std::string Ship::toString(bool drawAsEnemy) {
    std::string representation;
    if (drawAsEnemy) {
        if (this->sunk()) {
            for (int i = 0; i < size; i++) {
                representation += char(177);
            }
        } else {
            for (int i = 0; i < size; i++) {
                representation += char(219);
            }
        }
    } else {
        for (auto &i: segments) {
            representation += i.isSunk() ? char(177) : char(219);
        }
    }
    return representation;
}

std::vector<ShipSegment> Ship::getSegments() {
    return this->segments;
}

int Ship::getSize() {
    return this->size;
}

bool Ship::isVertical() {
    return this->vertical;
}

std::pair<char, int> Ship::getOrigin() {
    return this->origin;
}
