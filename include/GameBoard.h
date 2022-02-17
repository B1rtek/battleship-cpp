#ifndef BATTLESHIP_CPP_GAMEBOARD_H
#define BATTLESHIP_CPP_GAMEBOARD_H

#include "Board.h"

/**
 * @brief Board used in game, consists of two Boards, one of them being the data
 * board, visible for the player, and one of them being the visible board,
 * seen by the enemy, based on the data board.
 */
class GameBoard {
    Board dataBoard, visibleBoard;

public:
    GameBoard();

    explicit GameBoard(Board dataBoard);

    bool discoverField(char x, int y);

    bool markAsEmpty(char x, int y);

    bool unmarkAsEmpty(char x, int y);

    void sinkShip(const Ship& shipToSink);

    Board getDisplayBoard(bool displayAsEnemy = false);

    bool fieldUndiscovered(char x, int y);

    void markMissesAround(const Ship& shipToMarkAround);
};

#endif //BATTLESHIP_CPP_GAMEBOARD_H
