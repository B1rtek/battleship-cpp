#ifndef BATTLESHIP_CPP_FLEET_H
#define BATTLESHIP_CPP_FLEET_H

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


class Fleet {
    std::vector<Ship> ships;
public:
    std::vector<Ship> getShips();
};

void markMissesAround(Ship ship, Board &placementBoard);


#endif //BATTLESHIP_CPP_FLEET_H
