#ifndef BATTLESHIP_CPP_GAME_H
#define BATTLESHIP_CPP_GAME_H

#include "GameBoard.h"
#include "Enemy.h"
#include "Settings.h"
#include <map>

enum GameMessage {
    NOT_PLAYERS_TURN,
    INVALID_COORDS,
    ENEMY_SHIP_HIT,
    ENEMY_SHIP_SUNK,
    ENEMY_MISS,
    ENEMY_WIN,
    FIELD_MARK_FAIL,
    FIELD_UNMARK_FAIL,
    GAME_HELP_MESSAGE,
    PLAYER_SHIP_HIT,
    PLAYER_SHIP_SUNK,
    PLAYER_MISS,
    PLAYER_WIN,
    FIELD_ALREADY_DISCOVERED,
    PLAYERS_TURN
};

/**
 * @brief Handles the game events and moves from both players
 */
class Game {
    GameBoard playerBoard;
    GameBoard enemyBoard;
    Fleet playerFleet;
    Fleet enemyFleet;
    Enemy enemy;
    bool playersTurn;
    bool won;
    std::vector<GameMessage> messages;
    std::map<Setting, bool> settings;

    void applyDefaultSettings();

    void createEnemyFleet();

    void messageNotPlayersTurn();

    void messageInvalidCoordinates();

    void messageEnemyShipHit();

    void messageEnemyShipSunk();

    void messageEnemyMiss();

    void messageEnemyWin();

    void messageFieldMarkFail();

    void messageFieldUnmarkFail();

    void messageGameHelp();

    void messagePlayerShipHit();

    void messagePlayerShipSunk();

    void messagePlayerMiss();

    void messagePlayerWin();

    void messageFieldAlreadyDiscovered();

    void messagePlayersTurn();

public:
    Game();

    void applySettings(std::map<Setting, bool> settings);

    void startGame(Board playerBoard, Fleet playerFleet);

    bool discoverField(char x, int y);

    void markField(char x, int y);

    void unmarkField(char x, int y);

    void gameHelp();

    bool enemyMove();

    void checkWin();

    Board getPlayerBoardDisplay();

    Board getEnemyBoardDisplay();

    Fleet getPlayerFleetDisplay();

    Fleet getEnemyFleetDisplay();

    std::vector<GameMessage> getDisplayMessages();

    bool isPlayersTurn() const;

    bool isWon() const;
};

#endif //BATTLESHIP_CPP_GAME_H
