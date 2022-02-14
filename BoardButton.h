#ifndef BATTLESHIP_CPP_BOARDBUTTON_H
#define BATTLESHIP_CPP_BOARDBUTTON_H

#include <utility>
#include <QtWidgets/QToolButton>

std::pair<char, int> arrayToGameCoords(int x, int y);

/**
 * @brief Represents a single button on the board and a segment displaying a ship
 * in the Fleet displays under boards on the Game screen
 *
 * Code that makes the button square was made by Oleh Prypin,
 * distributed under terms of the CC BY-SA 4.0 license
 * Source: https://stackoverflow.com/questions/11008140/pyqt-custom-widget-fixed-as-square
 */
class BoardButton : public QToolButton {
    char x;
    int y;
    std::function<void(char x, int y)> leftClickAction;
    std::function<void(char x, int y)> rightClickAction;

public:
    explicit BoardButton(QWidget *parent = nullptr);

    int heightForWidth(int width);

    void resizeEvent(QResizeEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void setLeftClickAction(std::function<void(char x, int y)> function);

    void setRightClickAction(std::function<void(char x, int y)> function);

    void setGameCoordinates(char newX, int newY);
};

#endif //BATTLESHIP_CPP_BOARDBUTTON_H
