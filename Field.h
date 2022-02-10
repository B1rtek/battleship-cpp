#ifndef BATTLESHIP_CPP_FIELD_H
#define BATTLESHIP_CPP_FIELD_H

enum FieldStatus {
    NOTHING, MISS, SHIP, SUNK, SELECTED
};

/**
 * @brief Class that stores information about a field on a game board.
 */
class Field {

    FieldStatus status;

public:
    Field();

    char toString();

    FieldStatus getStatus();

    void setStatus(FieldStatus newStatus);
};

#endif //BATTLESHIP_CPP_FIELD_H
