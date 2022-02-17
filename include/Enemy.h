#ifndef BATTLESHIP_CPP_ENEMY_H
#define BATTLESHIP_CPP_ENEMY_H

#include <utility>
#include <vector>
#include <set>

std::pair<char, int> upperField(std::pair<char, int> coords);

std::pair<char, int> lowerField(std::pair<char, int> coords);

std::pair<char, int> leftField(std::pair<char, int> coords);

std::pair<char, int> rightField(std::pair<char, int> coords);

std::vector<std::pair<char, int>> createListOfAdherent(std::pair<char, int> source);

std::vector<std::pair<char, int>> createListOfTangents(std::pair<char, int> source);

/**
 * @brief Class representing the computer opponent
 */
class Enemy {
    std::vector<std::pair<char, int>> undiscovered;
    std::set<std::pair<char, int>> undiscoveredSet;
    std::vector<std::pair<char, int>> toShoot;
    std::vector<std::pair<char, int>> toMarkAsEmpty;
    std::pair<char, int> lastTarget;
    bool hardMode;

    std::pair<char, int> rankFieldsAndChoose();

    void undiscoveredRemove(std::pair<char, int> value);

public:
    explicit Enemy(bool hardMode = false);

    std::pair<char, int> shoot();

    void reactToHit();

    void reactToSink();

    std::vector<std::pair<char, int>> markAsEmpty();
};

#endif //BATTLESHIP_CPP_ENEMY_H
