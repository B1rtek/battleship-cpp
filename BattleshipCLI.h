#ifndef BATTLESHIP_CPP_BATTLESHIPCLI_H
#define BATTLESHIP_CPP_BATTLESHIPCLI_H

#include "FleetCreator.h"
#include "Game.h"

enum AppState {
    MAIN_MENU, SETUP, GAME, HOW_TO_PLAY, SETTINGS
};

enum Command {
    NOP,
    MAIN_START_SETUP,
    MAIN_SETTINGS,
    MAIN_START_HTP,
    MAIN_EXIT,
    EXIT_TO_MAIN,
    CREATOR_SHIP_SELECT,
    CREATOR_SHIP_MOVE,
    CREATOR_SHIP_ROTATE,
    CREATOR_FLEET_RAND,
    CREATOR_DONE,
    CREATOR_HELP,
    GAME_SHOOT,
    GAME_MARK_FIELD,
    GAME_UNMARK_FIELD,
    GAME_HELP,
    SETTINGS_MMA,
    SETTINGS_HARD_ENEMY
};

void cls();

std::string formatFleetCreatorMessages(std::vector<FCMessage> messages);

std::string formatGameMessages(std::vector<GameMessage> messages, bool extraNewline = false);

std::vector<std::string> splitCommand(std::string command);

bool isNumeric(std::string possiblyNumber);

/**
 * @brief Class operating the game in the command line
 */
class BattleshipCLI {
    FleetCreator fleetCreator;
    Game game;
    Settings settings;
    AppState state;
    bool quit;
    std::string prompt;

    void display();

    void displayMainMenu();

    void displayFleetCreator();

    void displayGame();

    void displayHelp();

    void displaySettings();

    std::pair<Command, std::pair<char, int>> playerInput();

    std::pair<Command, std::pair<char, int>> playerInputMainMenu(std::vector<std::string> commandParts);

    std::pair<Command, std::pair<char, int>> playerInputFleetCreator(std::vector<std::string> commandParts);

    std::pair<Command, std::pair<char, int>> playerInputGame(std::vector<std::string> commandParts);

    std::pair<Command, std::pair<char, int>> playerInputSettings(std::vector<std::string> commandParts);

    void execute(Command command, char x, int y);

    void executeMainMenu(Command command);

    void executeFleetCreator(Command command, char x, int y);

    void executeGame(Command command, char x, int y);

    void executeSettings(Command command);

public:
    BattleshipCLI();

    void start();
};

#endif //BATTLESHIP_CPP_BATTLESHIPCLI_H
