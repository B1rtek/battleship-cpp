#ifndef BATTLESHIP_CPP_UIFLEET_H
#define BATTLESHIP_CPP_UIFLEET_H

#include <QIcon>
#include "Fleet.h"
#include "BoardButton.h"
#include <map>
#include <QGridLayout>

/**
 * @brief Representation of Fleet in the UI
 */
class UIFleet {
    Fleet cachedFleet;
    std::map<FieldStatus, QIcon> icons;
    BoardButton *buttonArray[10][4];
    std::vector<std::pair<int, int>> positionsArray[10];

    void createButtonArray();

    void initializeCachedFleet();

public:
    UIFleet();

    void updateFleetDisplay(Fleet displayFleet);

    void placeButtonArray(QGridLayout *parentGridLayout);

    void defineLeftClickAction(std::function<void(char x, int y)> leftClickAction);

    void defineRightClickAction(std::function<void(char x, int y)> rightClickAction);

    void setIcons(std::map<FieldStatus, QIcon> iconsMap);
};

#endif //BATTLESHIP_CPP_UIFLEET_H
