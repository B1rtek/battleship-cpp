#include "Fleet.h"
#include "Enemy.h"
#include <ctime>
#include <algorithm>

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
bool fieldAvailable(Ship tempShip, Board tempBoard) {
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
 * Creates a vector of fields around the specified field
 * @param source the field to generate surrounding fields of
 * @return vector containing coordinates of all fields around the source field
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
std::set<std::pair<char, int>> setFromVector(const std::vector<std::pair<char, int>>& baseVector) {
    std::set<std::pair<char, int>> basedSet;
    for (auto i: baseVector) {
        basedSet.insert(i);
    }
    return basedSet;
}

/**
 * @brief Creates a vector of fields around the given ship
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
    std::vector<std::pair<char, int>> fieldsAround = fieldsAroundShip(std::move(ship));
    for (auto i: fieldsAround) {
        placementBoard.setFieldStatus(i.first, i.second, FieldStatus::MISS);
    }
}

/**
 * @brief Initializes a Fleet by creating an empty vector of ships
 *
 * Ships in the ships vector are always put in the order from biggest to smallest,
 * and that's how they are generated in createRandom() and createFleet()
 * methods. selectedShip is the ship that will be moved or rotated
 * while modifying the board
 */

Fleet::Fleet() {
    this->selectedShip = nullptr;
}

/**
 * @brief Alternate constructor used in some cases
 * @param ships A vector of ships to initialize this fleet with
 */
Fleet::Fleet(const std::vector<Ship>& ships) {
    if (!ships.empty()) {
        this->ships = ships;
    }
    this->selectedShip = nullptr;
}

/**
 * @brief Finds the index of the selected ship in the internal ships vector
 * @return index of the selected ship
 *
 * Used because std::find() doesn't want to compile for some reason
 */
int Fleet::getSelectedShipIndex() {
    Ship selectedShipValue = *this->selectedShip;
    for (int i = 0; i < this->ships.size(); i++) {
        Ship atThisIndex = ships[i];
        if (atThisIndex == selectedShipValue) {
            return i;
        }
    }
    return 0;
}

/**
 * @brief Checks if the fleet with a new ship instead of the selected one doesn't
 * collide with itself.
 * @param newShip a new ship that this fleet will be tested with
 * @return new_ship's index in the ships vector if it fits with the
 * other ships, otherwise -1 to indicate that it can't be placed
 *
 * This method is only used by setShipPosition() and changeShipRotation() methods.
 * The test is performed by creating a new fleet with the selected ship changed and
 * checking if placing it on a temporary board creates any collisions
 */
int Fleet::newShipTestFit(Ship newShip) {
    std::vector<Ship> newFleet = this->ships;
    int oldShipIndex = this->getSelectedShipIndex();
    newFleet[oldShipIndex] = std::move(newShip);
    Board tempBoard = Board();
    for (auto &ship: newFleet) {
        if (fieldAvailable(ship, tempBoard)) {
            markMissesAround(ship, tempBoard);
            tempBoard.placeShip(ship);
        } else {
            return -1;
        }
    }
    return oldShipIndex;
}

/**
 * @brief Creates ships in random places on the board
 *
 * Used by the computer enemy to place ships. First, the rotation of the ship
 * is chosen, and then a vector of fields where a ship can be placed is made.
 * Then, for every ship, a location is chosen, and the cycle continues, until all
 * ships are placed. To test if a location for a ship is valid, ships are
 * placed on a temporary board.
 */
void Fleet::createRandom() {
    this->ships.clear();
    this->selectedShip = nullptr;
    srand(time(nullptr)); // NOLINT(cert-msc51-cpp)
    /// rotation set to true means that the ship will be vertical
    bool rotations[10];
    for (bool &rotation: rotations) {
        rotation = rand() % 2; // NOLINT(cert-msc50-cpp)
    }
    int sizes[10] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    Board tempBoard = Board();
    for (int i = 0; i < 10; i++) {
        std::vector<std::pair<char, int>> goodCoords;
        for (auto field: returnAllFieldCoordinates()) {
            Ship tempShip = Ship(field, sizes[i], rotations[i]);
            if (fieldAvailable(tempShip, tempBoard)) {
                goodCoords.push_back(field);
            }
        }
        std::pair<char, int> position = goodCoords[rand() % goodCoords.size()]; // NOLINT(cert-msc50-cpp)
        Ship shipToAdd = Ship(position, sizes[i], rotations[i]);
        this->ships.push_back(shipToAdd);
        markMissesAround(shipToAdd, tempBoard);
        tempBoard.placeShip(shipToAdd);
    }
}

/**
 * @brief Damages a ship in the specified coordinates
 * @param x x coordinate of the field
 * @param y y coordinate of the field
 * @return true if the ship sinks completely, otherwise false
 */
bool Fleet::hit(char x, int y) {
    Ship *shipHit = this->findShip(x, y);
    if (shipHit == nullptr) {
        return false;
    }
    shipHit->sink(x, y);
    if (shipHit->sunk()) {
        return true;
    }
    return false;
}

/**
 * @brief Finds a ship positioned on the selected coordinates
 * @param x x coordinate of the field
 * @param y y coordinate of the field
 * @return Ship in this position or nullptr if there is no ship there
 */
Ship *Fleet::findShip(char x, int y) {
    for (auto &ship: this->ships) {
        if (ship.checkIfBelongs(x, y)) {
            return &ship;
        }
    }
    return nullptr;
}

/**
 * @brief Selects a ship that can be moved or rotated while setting up the fleet
 * @param x x coordinate of the field
 * @param y y coordinate of the field
 * @return true if ship was selected, false otherwise
 */
bool Fleet::selectShip(char x, int y) {
    this->selectedShip = this->findShip(x, y);
    return this->selectedShip != nullptr;
}

/**
 * @brief Sets selected ship's position to the specified coordinates.
 * @param x x coordinate of the new position
 * @param y y coordinate of the new position
 * @return true if moving the ship to a new position was successful, false otherwise
 *
 * Coordinates point to the ship's new origin. Before moving the ship, a test is
 * conducted to see if the new position is valid and doesn't collide with any
 * ships from this fleet
 */
bool Fleet::setShipPosition(char x, int y) {
    if (this->selectedShip == nullptr) {
        return false;
    }
    bool vertical = this->selectedShip->isVertical();
    int size = this->selectedShip->getSize();
    Ship newShip = Ship(std::make_pair(x, y), size, vertical);
    int oldShipIndex = this->newShipTestFit(newShip);
    if (oldShipIndex == -1) {
        return false;
    }
    this->ships[oldShipIndex] = newShip;
    this->selectedShip = &this->ships[oldShipIndex];
    return true;
}

/**
 * @brief Changes selected ship's rotation from vertical to horizontal, or the other way
 * @return true if rotation was successful, false otherwise
 *
 * Just like in setShipPosition, a test fit is conducted to see if the rotated ship
 * doesn't collide with any other ships.
 */
bool Fleet::changeShipRotation() {
    if (this->selectedShip == nullptr) {
        return false;
    }
    bool vertical = !this->selectedShip->isVertical();
    int size = this->selectedShip->getSize();
    std::pair<char, int> origin = this->selectedShip->getOrigin();
    Ship newShip = Ship(origin, size, vertical);
    int oldShipIndex = this->newShipTestFit(newShip);
    if (oldShipIndex == -1) {
        return false;
    }
    this->ships[oldShipIndex] = newShip;
    this->selectedShip = &this->ships[oldShipIndex];
    return true;
}

/**
 * @brief Checks if the whole fleet has sunk
 * @return true if there are still ships afloat, false otherwise
 *
 * The check is performed by checking if every single ship has sunk or not
 */
bool Fleet::isAlive() {
    for (auto &ship: this->ships) {
        if (!ship.sunk()) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Returns a string containing all ships in the fleet and their current states
 * @param drawAsEnemy if set to true, the ships will be drawn as a sunk or undamaged,
 * to not indicate which ship has been struck to the enemy, false by default
 * @return a string representing a fleet, similar to the example shown below
 *
 * Example:\n
 * █▒▒█ ███ ███ ▒\n
 * ██ ██ ██ ▒ █ █\n
 * represents a fleet with it's 4 segment ship with its middle segments damaged,
 * and the first and fourth small ships destroyed
 */
std::string Fleet::toString(bool drawAsEnemy) {
    std::string fleet;
    std::vector<Ship> row1(this->ships.begin(), this->ships.begin() + 3);
    row1.push_back(this->ships.back());
    std::vector<Ship> row2(this->ships.begin() + 3, this->ships.end() - 1);
    for (auto &ship: row1) {
        fleet += ship.toString(drawAsEnemy) + ' ';
    }
    fleet.pop_back();
    fleet += '\n';
    for (auto &ship: row2) {
        fleet += ship.toString(drawAsEnemy) + ' ';
    }
    fleet.pop_back();
    return fleet;
}

/**
 * @brief Creates a data fleet representing what the specified player would see
 * @param displayAsEnemy if set to true, the data will reflect what the
 * enemy would see, otherwise it'll look like what the player should see
 * @return a Fleet containing data necessary to draw this board on the screen
 */
Fleet Fleet::getDisplayFleet(bool displayAsEnemy) {
    if (displayAsEnemy) {
        std::vector<Ship> displayShips;
        for (auto &ship: this->ships) {
            if (ship.sunk()) {
                displayShips.push_back(ship);
            } else {
                std::pair<char, int> origin = ship.getOrigin();
                int size = ship.getSize();
                bool vertical = ship.isVertical();
                Ship newShip = Ship(origin, size, vertical);
                displayShips.push_back(newShip);
            }
        }
        return Fleet(displayShips);
    } else {
        return Fleet(this->ships);
    }
}


Ship *Fleet::getSelectedShip() {
    return this->selectedShip;
}

std::vector<Ship> *Fleet::getShips() {
    return &this->ships;
}
