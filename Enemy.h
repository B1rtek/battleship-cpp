#ifndef BATTLESHIP_CPP_ENEMY_H
#define BATTLESHIP_CPP_ENEMY_H

#include <utility>
#include <vector>

std::pair<char, int> upperField(std::pair<char, int> coords);

std::pair<char, int> lowerField(std::pair<char, int> coords);

std::pair<char, int> leftField(std::pair<char, int> coords);

std::pair<char, int> rightField(std::pair<char, int> coords);

std::vector<std::pair<char, int>> createListOfAdherent(std::pair<char, int> source);

std::vector<std::pair<char, int>> createListOfTangents(std::pair<char, int> source);

#endif //BATTLESHIP_CPP_ENEMY_H
