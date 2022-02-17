#include "Enemy.h"
#include "Board.h"
#include <algorithm>
#include <ctime>
#include <random>

std::pair<char, int> upperField(std::pair<char, int> coords) {
    return std::make_pair(coords.first, coords.second - 1);
}

std::pair<char, int> lowerField(std::pair<char, int> coords) {
    return std::make_pair(coords.first, coords.second + 1);
}

std::pair<char, int> leftField(std::pair<char, int> coords) {
    return std::make_pair(char(int(coords.first) - 1), coords.second);
}

std::pair<char, int> rightField(std::pair<char, int> coords) {
    return std::make_pair(char(int(coords.first) + 1), coords.second);
}

/**
 * @brief Creates a vector of pairs representing coordinates of fields that would be
 * adherent to a field with coordinates provided in the source pair
 * @param source coordinates of a field
 * @returns vector of pairs containing coordinates of fields that would be adherent
 * to the given one
 */
std::vector<std::pair<char, int>> createListOfAdherent(std::pair<char, int> source) {
    std::vector<std::pair<char, int>> adherent = {leftField(source), rightField(source), upperField(source),
                                                  lowerField(source)};
    return adherent;
}

/**
 * @brief Creates a vector of pairs representing coordinates of fields that would be
 * adherent to a field with coordinates provided in the source pair
 * @param source coordinates of a field
 * @returns vector of pairs containing coordinates of fields that would be adherent
 * to the given one
 */
std::vector<std::pair<char, int>> createListOfTangents(std::pair<char, int> source) {
    std::vector<std::pair<char, int>> tangents = {leftField(upperField(source)), rightField(upperField(source)),
                                                  leftField(lowerField(source)), rightField(lowerField(source))};
    return tangents;
}

/**
 * Creates an Enemy object and initializes all its fields
 * @param hardMode makes enemy use field ranking when choosing a field to shoot at
 *
 * Initializes 3 vectors - a vector of undiscovered fields which Enemy will shoot
 * randomly at, a vector of toShoot fields, which have higher priority than random
 * targets and are set once a ship is hit, and toMarkAsEmpty vector, which gets \
 * populated by fields to mark as empty once a ship is hit
 */
Enemy::Enemy(bool hardMode) {
    for (auto &field: returnAllFieldCoordinates()) {
        this->undiscovered.push_back(field);
        this->undiscoveredSet.insert(field);
    }
    this->hardMode = hardMode;
}

/**
 * @brief Chooses a field based on the probability of it having a ship
 * @return coordinates of a chosen field
 *
 * Creates a vector of fields sorted by the maximum length of a ship that can be
 * located there, and then returns coordinates of one with the highest score
 */
std::pair<char, int> Enemy::rankFieldsAndChoose() {
    std::vector<std::pair<int, std::pair<char, int>>> rankList;
    for (auto &field: this->undiscovered) {
        int scoreVert = 1, scoreHoriz = 1;
        std::pair<char, int> current = field;
        current = upperField(current);
        while (this->undiscoveredSet.count(current)) {
            scoreVert++;
            current = upperField(current);
        }
        current = field;
        current = lowerField(current);
        while (this->undiscoveredSet.count(current)) {
            scoreVert++;
            current = lowerField(current);
        }
        current = field;
        current = rightField(current);
        while (this->undiscoveredSet.count(current)) {
            scoreHoriz++;
            current = rightField(current);
        }
        current = field;
        current = leftField(current);
        while (this->undiscoveredSet.count(current)) {
            scoreHoriz++;
            current = leftField(current);
        }
        rankList.emplace_back(std::max(scoreVert, scoreHoriz), field);
    }
    int maxScore = -1;
    for (auto &field: rankList) {
        maxScore = std::max(maxScore, field.first);
    }
    std::vector<std::pair<char, int>> bestFields;
    for (auto &field: rankList) {
        if (field.first == maxScore) {
            bestFields.push_back(field.second);
        }
    }
    srand(time(nullptr)); // NOLINT(cert-msc51-cpp)
    return bestFields[rand() % bestFields.size()]; // NOLINT(cert-msc50-cpp)
}

/**
 * @brief Removes the given value from the vector-set undiscovered combo.
 * @param value value to remove
 */
void Enemy::undiscoveredRemove(std::pair<char, int> value) {
    this->undiscovered.erase(std::remove(this->undiscovered.begin(), this->undiscovered.end(), value),
                             this->undiscovered.end());
    this->undiscoveredSet.erase(value);
}

/**
 * @brief Chooses a field that will be shot at
 * @return field coordinates of a chosen field
 */
std::pair<char, int> Enemy::shoot() {
    while (!this->toShoot.empty()) {
        std::pair<char, int> chosen = this->toShoot[0];
        this->toShoot.erase(std::remove(this->toShoot.begin(), this->toShoot.end(), chosen), this->toShoot.end());
        if (this->undiscoveredSet.count(chosen)) {
            this->undiscoveredRemove(chosen);
            this->lastTarget = chosen;
            return chosen;
        }
    }
    std::pair<char, int> chosen;
    if (this->hardMode) {
        chosen = this->rankFieldsAndChoose();
    } else {
        srand(time(nullptr)); // NOLINT(cert-msc51-cpp)
        chosen = this->undiscovered[rand() % this->undiscovered.size()]; // NOLINT(cert-msc50-cpp)
    }
    this->undiscoveredRemove(chosen);
    this->lastTarget = chosen;
    return chosen;
}

/**
 * @brief Appends coordinates of fields that can't have any ships to the
 * toMarkAsEmpty vector and puts new targets on the toShoot vector
 */
void Enemy::reactToHit() {
    std::vector<std::pair<char, int>> toMarkAsEmptyList = createListOfTangents(this->lastTarget);
    for (auto &target: toMarkAsEmptyList) {
        if (this->undiscoveredSet.count(target)) {
            this->undiscoveredRemove(target);
            this->toMarkAsEmpty.push_back(target);
        }
    }
    std::vector<std::pair<char, int>> toShootList = createListOfAdherent(this->lastTarget);
    std::mt19937 gen(time(nullptr)); // NOLINT(cert-msc51-cpp)
    std::shuffle(toShootList.begin(), toShootList.end(), gen);
    for (auto &target: toShootList) {
        if (this->undiscoveredSet.count(target)) {
            this->toShoot.push_back(target);
        }
    }
}

/**
 * @brief Appends all the remaining unmarked fields around a sunken ship to the
 * toMarkAsEmpty vector
 */
void Enemy::reactToSink() {
    std::vector<std::pair<char, int>> toMarkAsEmptyList = createListOfAdherent(this->lastTarget);
    for (auto &target: toMarkAsEmptyList) {
        if (this->undiscoveredSet.count(target)) {
            this->undiscoveredRemove(target);
            this->toMarkAsEmpty.push_back(target);
        }
    }
    for (auto &target: this->toShoot) {
        this->toMarkAsEmpty.push_back(target);
    }
    this->toShoot.clear();
}

/**
 * @return a vector of fields to mark as empty after a move
 */
std::vector<std::pair<char, int>> Enemy::markAsEmpty() {
    std::vector<std::pair<char, int>> toMarkAsEmptyList = this->toMarkAsEmpty;
    this->toMarkAsEmpty.clear();
    return toMarkAsEmptyList;
}
