#include "Game.h"

/**
 * @brief Initializes game objects and variables needed to run the game
 */
Game::Game() {
    this->playersTurn = true;
    this->won = false;
    this->applyDefaultSettings();
}

/**
 * @brief Applies default settings for the game
 *
 * Split from original apply_settings() from the python version since
 * C++ doesn't have a None value replacement
 */
void Game::applyDefaultSettings() {
    Settings defaultSettings = Settings();
    this->settings = defaultSettings.getSettings();
}

/**
 * @brief Creates enemy's fleet and board
 */
void Game::createEnemyFleet() {
    this->enemyFleet = Fleet();
    this->enemyFleet.createRandom();
    Board enemySetupBoard = Board();
    enemySetupBoard.placeFleet(this->enemyFleet);
    this->enemyBoard = GameBoard(enemySetupBoard);
}

/**
 * @brief Adds the message about player turning while the enemy should
 * to the messages vector
 */
void Game::messageNotPlayersTurn() {
    this->messages.push_back(GameMessage::NOT_PLAYERS_TURN);
}

/**
 * @brief Adds the message about invalid field coordinates chosen
 * to the messages vector
 */
void Game::messageInvalidCoordinates() {
    this->messages.push_back(GameMessage::INVALID_COORDS);
}

/**
 * @brief Adds the message about hitting enemy's ship
 * to the messages vector
 */
void Game::messageEnemyShipHit() {
    this->messages.push_back(GameMessage::ENEMY_SHIP_HIT);
}

/**
 * @brief Adds the message about sinking enemy's ship
 * to the messages vector
 */
void Game::messageEnemyShipSunk() {
    this->messages.push_back(GameMessage::ENEMY_SHIP_SUNK);
}

/**
 * @brief Adds the message about enemy missing their shot
 * to the messages vector
 */
void Game::messageEnemyMiss() {
    this->messages.push_back(GameMessage::ENEMY_MISS);
}

/**
 * @brief Adds the message about enemy winning the game
 * to the messages vector
 */
void Game::messageEnemyWin() {
    this->messages.push_back(GameMessage::ENEMY_WIN);
}

/**
 * @brief Adds the message about trying to mark a field that cannot be marked
 * to the messages vector
 */
void Game::messageFieldMarkFail() {
    this->messages.push_back(GameMessage::FIELD_MARK_FAIL);
}

/**
 * @brief Adds the message about trying to unmark a field without a marker
 * to the messages vector
 */
void Game::messageFieldUnmarkFail() {
    this->messages.push_back(GameMessage::FIELD_UNMARK_FAIL);
}

/**
 * @brief Adds the game help content to the messages vector
 */
void Game::messageGameHelp() {
    this->messages.push_back(GameMessage::GAME_HELP);
}

/**
 * @brief Adds the message about enemy hitting player's ship
 * to the messages vector
 */
void Game::messagePlayerShipHit() {
    this->messages.push_back(GameMessage::PLAYER_SHIP_HIT);
}

/**
 * @brief Adds the message about enemy sinking player's ship
 * to the messages vector
 */
void Game::messagePlayerShipSunk() {
    this->messages.push_back(GameMessage::PLAYER_SHIP_SUNK);
}

/**
 * @brief Adds the message about player missing their shot
 * to the messages vector
 */
void Game::messagePlayerMiss() {
    this->messages.push_back(GameMessage::PLAYER_MISS);
}

/**
 * @brief Adds the message about player winning the game
 * to the messages vector
 */
void Game::messagePlayerWin() {
    this->messages.push_back(GameMessage::PLAYER_WIN);
}

/**
 * @brief Adds the message about player trying to discover a discovered field
 * to the messages vector
 */
void Game::messageFieldAlreadyDiscovered() {
    this->messages.push_back(GameMessage::FIELD_ALREADY_DISCOVERED);
}

/**
 * @brief Adds the message about player's turn
 * to the messages vector
 */
void Game::messagePlayersTurn() {
    this->messages.push_back(GameMessage::PLAYERS_TURN);
}

/**
 * @brief Applies new settings to the game
 * @param settings settings to apply
 */
void Game::applySettings(std::map<Setting, bool> newSettings) {
    this->settings = newSettings;
}

/**
 * Starts the game
 * @param playerBoard player's board with ships
 * @param playerFleet player's fleet that's placed on the board
 *
 * Assigns boards and fleets to both players
 */
void Game::startGame(Board playerDataBoard, Fleet playerDataFleet) {
    this->playerBoard = GameBoard(playerDataBoard);
    this->enemy = Enemy(this->settings[Setting::HARD_ENEMY]);
    this->playerFleet = playerDataFleet;
    this->createEnemyFleet();
    this->playersTurn = true;
    this->won = false;
    this->messagePlayersTurn();
}

/**
 * @brief Handles the field discovery process for the player
 * @param x x coordinate of a discovered field
 * @param y y coordinate of a discovered field
 * @return true if the player hit enemy's ship, otherwise false, true is
 * also returned when the move failed because of discovering fields on
 * coordinates outside the board or fields already discovered, to
 * prevent the player from losing their turn
 */
bool Game::discoverField(char x, int y) {
    if(!this->playersTurn) {
        this->messageNotPlayersTurn();
        return false;
    }
    if(!fieldOnBoard(std::make_pair(x, y))) {
        this->messageInvalidCoordinates();
        return true;
    }
    if(!this->enemyBoard.fieldUndiscovered(x, y)) {
        this->messageFieldAlreadyDiscovered();
        return true;
    }
    this->playersTurn = false;
    bool hit = this->enemyBoard.discoverField(x, y);
    if(hit) {
        this->playersTurn = true;
        this->messageEnemyShipHit();
        bool sunk = this->enemyFleet.hit(x, y);
        if(sunk) {
            this->messageEnemyShipSunk();
            Ship *shipToSink = this->enemyFleet.findShip(x, y);
            this->enemyBoard.sinkShip(*shipToSink);
            if(this->settings[Setting::MARK_MISSES_AROUND]) {
                this->enemyBoard.markMissesAround(*shipToSink);
            }
            this->checkWin();
        }
    } else {
        this->messagePlayerMiss();
    }
    return hit;
}

/**
 * @brief Handles the field marking process for the player
 * @param x x coordinate of a field to mark
 * @param y y coordinate of a field to mark
 */
void Game::markField(char x, int y) {
    if(!fieldOnBoard(std::make_pair(x, y))) {
        this->messageInvalidCoordinates();
        return;
    }
    bool marked = this->enemyBoard.markAsEmpty(x, y);
    if(!marked) {
        this->messageFieldMarkFail();
    }
}

/**
 * @brief Handles the field unmarking process for the player
 * @param x x coordinate of a field to unmark
 * @param y y coordinate of a field to unmark
 */
void Game::unmarkField(char x, int y) {
    if(!fieldOnBoard(std::make_pair(x, y))) {
        this->messageInvalidCoordinates();
        return;
    }
    bool unmarked = this->enemyBoard.unmarkAsEmpty(x, y);
    if(!unmarked) {
        this->messageFieldUnmarkFail();
    }
}

/**
 * @brief Handles the help command output
 */
void Game::gameHelp() {
    this->messageGameHelp();
}

/**
 * @brief Handles the computer enemy's move
 * @return true if the enemy hit player's ship, false otherwise
 */
bool Game::enemyMove() {
    if(this->playersTurn) {
        return false;
    }
    std::pair<char, int> target = this->enemy.shoot();
    bool hit = this->playerBoard.discoverField(target.first, target.second);
    if(hit) {
        this->playersTurn = false;
        this->messagePlayerShipHit();
        bool sunk = this->playerFleet.hit(target.first, target.second);
        this->enemy.reactToHit();
        if(sunk) {
            this->messagePlayerShipSunk();
            Ship *shipToSink = this->playerFleet.findShip(target.first, target.second);
            this->playerBoard.sinkShip(*shipToSink);
            this->enemy.reactToSink();
            this->checkWin();
        }
    } else {
        this->playersTurn = true;
        this->messageEnemyMiss();
    }
    std::vector<std::pair<char, int>> toMarkAsEmpty = this->enemy.markAsEmpty();
    if(!toMarkAsEmpty.empty()) {
        for(auto &field:toMarkAsEmpty) {
            this->playerBoard.markAsEmpty(field.first, field.second);
        }
    }
    return hit;
}

/**
 * @brief Checks if one of the players won the game
 * @return true if the player won, false if the computer enemy won
 */
bool Game::checkWin() {
    return false;
}
