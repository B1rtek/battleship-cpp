#include "../include/Field.h"

/**
 * @brief Initializes a field, assigning it a status of FieldStatus::NOTHING
 */
Field::Field() {
    this->status = NOTHING;
}

/**
 * @brief Used to print out the fields in the console
 * @returns A character representing a field's status
 */
char Field::toString() {
    char representations[5] = {' ', '.', char(219), char(177), '#'};
    return representations[this->status];
}

FieldStatus Field::getStatus() {
    return this->status;
}

void Field::setStatus(FieldStatus newStatus) {
    this->status = newStatus;
}