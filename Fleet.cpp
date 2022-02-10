#include "Fleet.h"
#include "Field.h"
#include "Board.h"
#include "Ship.h"
#include "Enemy.h"

/**
 * Checks if a ship with given position, size and rotation can be placed on
 * the board
 * @param tempShip a ship which placement will be tested
 * @param tempBoard board on which the proposed Ship is to be placed
 * @return true if the proposed ship can be placed, false otherwise
 *
 * Check is performed by checking if all segments of the ship have valid board
 * coordinates, and if it doesn't collide with any ships placed earlier
 */
bool fieldAvailable(Ship tempShip, Board &tempBoard) {
    std::vector<std::pair<char, int>> fields = tempShip.getSegmentCoordinates();
    for (auto &field: fields) {
        if (fieldOnBoard(field)) {
            FieldStatus status = tempBoard.getFieldStatus(field.first, field.second);
            if (status != FieldStatus::NOTHING) {
                return false;
            }
        } else {
            return false;
        }
    }
    return true;
}

/**
 * Creates a list of fields around the specified field
 * @param source the field to generate surrounding fields of
 * @return list containing coordinates of all fields around the source field
 */
std::vector<std::pair<char, int>> fieldsAroundField(std::pair<char, int> source) {
    std::vector<std::pair<char, int>> adherent = createListOfAdherent(source);
    std::vector<std::pair<char, int>> tangents = createListOfTangents(source);
    adherent.insert(adherent.end(), tangents.begin(), tangents.end());
    return adherent;
}

/**
 * Creates a set with the same content as the given vector
 * @param baseVector vector to generate a set from
 * @return a set with the same content as the given vector
 */
std::set<std::pair<char, int>> setFromVector(std::vector<std::pair<char, int>> baseVector) {
    std::set<std::pair<char, int>> basedSet;
    for (auto i: baseVector) {
        basedSet.insert(i);
    }
    return basedSet;
}

/**
 * @brief Creates a list of fields around the given ship
 * @param ship ship to generate fields around
 * @return a vector of field coordinates around that ship
 */
std::vector<std::pair<char, int>> fieldsAroundShip(Ship ship) {
    std::set<std::pair<char, int>> allFields = returnAllFieldCoordinates();
    std::set<std::pair<char, int>> shipFields = setFromVector(ship.getSegmentCoordinates());
    std::set<std::pair<char, int>> setAround;
    std::vector<std::pair<char, int>> around;
    for (auto &shipField: shipFields) {
        std::vector<std::pair<char, int>> fieldsAroundCurrent = fieldsAroundField(shipField);
        for (auto field: fieldsAroundCurrent) {
            if (allFields.count(field) && !setAround.count(field) && !shipFields.count(field)) {
                around.push_back(field);
                setAround.insert(field);
            }
        }
    }
    return around;
}

/**
 * @brief Marks fields around the Ship with FieldStatus::MISS to prevent ships from
 * generating directly next to each other
 * @param ship Ship around which the fields will be marked
 * @param placementBoard Board on which the fields will be marked
 */

void markMissesAround(Ship ship, Board &placementBoard) {
    std::vector<std::pair<char, int>> fieldsAround = fieldsAroundShip(ship);
    for (auto i: fieldsAround) {
        placementBoard.setFieldStatus(i.first, i.second, FieldStatus::MISS);
    }
}
