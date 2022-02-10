#include "Enemy.h"

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






