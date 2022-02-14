#ifndef BATTLESHIP_CPP_FLEET_H
#define BATTLESHIP_CPP_FLEET_H

/// Needed because linker gets angry
class Board;

#include <string>
#include <vector>
#include <set>
#include "Board.h"
#include "Ship.h"

bool fieldAvailable(Ship tempShip, Board tempBoard);

std::vector<std::pair<char, int>> fieldsAroundField(std::pair<char, int> source);

std::vector<std::pair<char, int>> fieldsAroundShip(Ship ship);

std::set<std::pair<char, int>> setFromVector(std::vector<std::pair<char, int>> baseVector);

void markMissesAround(Ship ship, Board &placementBoard);

/**
 * @brief Class containing information about a fleet of ships
 */
class Fleet {
    std::vector<Ship> ships;
    Ship *selectedShip;

    int getSelectedShipIndex();

    int newShipTestFit(Ship newShip);

public:
    Fleet();

    Fleet(std::vector<Ship> ships);

    void createRandom();

    bool hit(char x, int y);

    Ship *findShip(char x, int y);

    bool selectShip(char x, int y);

    bool setShipPosition(char x, int y);

    bool changeShipRotation();

    bool isAlive();

    std::string toString(bool drawAsEnemy = false);

    Fleet getDisplayFleet(bool displayAsEnemy = false);

    std::vector<Ship> *getShips();

    Ship *getSelectedShip();
};

#endif //BATTLESHIP_CPP_FLEET_H
