#ifndef BATTLESHIP_CPP_UIBOARD_H
#define BATTLESHIP_CPP_UIBOARD_H

#include "Board.h"
#include "BoardButton.h"
#include <map>
#include <QIcon>
#include <QGridLayout>

/**
 * @brief Representation of Board in the UI
 */
class UIBoard {
    Board cachedBoard;
    std::map<FieldStatus, QIcon> icons;
    BoardButton *buttonArray[10][10]{};

    void createButtonArray();

    void initializeCachedBoard();

public:
    UIBoard();

    void updateBoard(Board displayBoard, Ship *selectedShip = nullptr);

    void placeButtonArray(QGridLayout *parentGridLayout);

    void defineLeftClickAction(std::function<void(char x, int y)> *leftClickAction);

    void defineRightClickAction(std::function<void(char x, int y)> *rightClickAction);

    void setIcons(std::map<FieldStatus, QIcon> iconsMap);
};

#endif //BATTLESHIP_CPP_UIBOARD_H
