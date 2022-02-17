#include "BoardButton.h"
#include <QMouseEvent>

/**
 * @brief Translates coordinates from array indices to game field coordinates
 * @param x x index of a field
 * @param y y index of a field
 * @return pair containing translated field coordinates
 */
std::pair<char, int> arrayToGameCoords(int x, int y) {
    return std::make_pair(char(x + 97), y + 1);
}

/**
 * @brief Creates a square UI button with an icon
 * @param parent Qt5 stuff idk
 *
 * used in board and fleet displays
 */
BoardButton::BoardButton(QWidget *parent) : QToolButton(parent) {
    QSizePolicy policy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    policy.setHeightForWidth(true);
    this->setSizePolicy(policy);
    this->setMaximumSize(40, 40);
    this->x = ' ';
    this->y = 0;
    this->leftClickAction = nullptr;
    this->rightClickAction = nullptr;
}

/**
 * @brief Ensures that the button is (almost) always square
 * @param width Qt5 stuff idk
 * @return Qt5 stuff idk, this function is overriden
 */
int BoardButton::heightForWidth(int width) const {
    return width;
}

/**
 * @brief Ensures that the fields don't become too small when resizing the window
 * @param event Qt5 stuff idk
 */
void BoardButton::resizeEvent(QResizeEvent *event) {
    this->setMinimumWidth(this->height());
}

/**
 * @brief Calls functions assigned to the left and right clicks in this button
 * @param event QMouseEvent carrying a mouse press
 */
void BoardButton::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        if (this->leftClickAction != nullptr) {
            (*leftClickAction)(this->x, this->y);
        }
    } else if (event->button() == Qt::RightButton) {
        if (this->rightClickAction != nullptr) {
            (*rightClickAction)(this->x, this->y);
        }
    }
}

/**
 * @brief assigns this button's function that will be called when it's pressed with a left mouse button
 * @param function function to be assigned
 */
void BoardButton::setLeftClickAction(std::function<void(char, int)> *function) {
    this->leftClickAction = function;
}

/**
 * @brief assigns this button's function that will be called when it's pressed with a right mouse button
 * @param function function to be assigned
 */
void BoardButton::setRightClickAction(std::function<void(char, int)> *function) {
    this->rightClickAction = function;
}

/**
 * @brief Sets this button's in game coordinates
 * @param x x coordinate of a field
 * @param y y coordinate of a field
 */
void BoardButton::setGameCoordinates(char newX, int newY) {
    this->x = newX;
    this->y = newY;
}
