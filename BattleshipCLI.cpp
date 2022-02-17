#include "BattleshipCLI.h"
#include <iostream>
#include <algorithm>

#ifdef _WIN32
std::string clsCommand = "cls";
#endif
#ifdef __linux__
std::string clsCommand = "clear";
#endif

/**
 * @brief Clears the console
 */
void cls() {
    system(clsCommand.c_str());
}

/**
 * @brief Formats the messages from FleetCreator, creating a string with all of them
 * @param messages messages from FleetCreator
 * @return string with all messages formatted
 */
std::string formatFleetCreatorMessages(std::vector<FCMessage> messages) {
    std::string helpContent = "Help:\n"
                              "sel <x> <y>: selects a ship in the given location\n"
                              "mv <x> <y>: moves the selected ship to the given location. The location points to the ship's uppermost or left segment\n"
                              "rot: rotates the selected ship from vertical to horizontal rotation, or the other way, around its uppermost or left part\n"
                              "rand: places all ships randomly\n"
                              "done: ends the setup process and accepts the current board as the board for the game\n"
                              "quit/exit: exits to main menu";
    std::map<FCMessage, std::string> messagesMap = {
            {FCMessage::SHIP_SELECTED,      "A ship has been selected"},
            {FCMessage::SHIP_MOVE_FAIL,     "The selected location is invalid"},
            {FCMessage::SHIP_ROTATION_FAIL, "You can't rotate this ship"},
            {FCMessage::SETUP_HELP,         helpContent}
    };
    std::string messagesList;
    for (auto &message: messages) {
        messagesList.append(messagesMap[message] + '\n');
    }
    return messagesList;
}

/**
 * @brief Formats the messages from Game, creating a string with all of them
 * @param messages messages from Game
 * @param extraNewline adds a newline at the end of the generated string, used by the GUI
 * version since adding text to a textbox doesn't add a newline at the end
 * @return string with all messages formatted
 */
std::string formatGameMessages(std::vector<GameMessage> messages, bool extraNewline) {
    std::string helpContent = "Help:\n"
                              "st <x> <y>: shoots at the specified field\n"
                              "mk <x> <y>: marks the specified field on the enemy's board as empty\n"
                              "unmk <x> <y>: unmarks the specified field\n"
                              "quit: quits the game";
    std::map<GameMessage, std::string> messagesMap = {
            {GameMessage::NOT_PLAYERS_TURN,         "It's not your turn!"},
            {GameMessage::INVALID_COORDS,           "Invalid field coordinates"},
            {GameMessage::ENEMY_SHIP_HIT,           "You've hit an enemy ship!"},
            {GameMessage::ENEMY_SHIP_SUNK,          "You've destroyed an enemy ship!"},
            {GameMessage::ENEMY_MISS,               "The enemy missed. It's your turn now"},
            {GameMessage::ENEMY_WIN,                "The enemy wins :("},
            {GameMessage::FIELD_MARK_FAIL,          "The field you tried to mark is not empty"},
            {GameMessage::FIELD_UNMARK_FAIL,        "The field you tried to unmark is not marked"},
            {GameMessage::GAME_HELP_MESSAGE,        helpContent},
            {GameMessage::PLAYER_SHIP_HIT,          "The enemy has hit one of your ships!"},
            {GameMessage::PLAYER_SHIP_SUNK,         "The enemy has destroyed one of your ships!"},
            {GameMessage::PLAYER_MISS,              "You missed. Press to continue to the next enemy move"},
            {GameMessage::PLAYER_WIN,               "You win!"},
            {GameMessage::FIELD_ALREADY_DISCOVERED, "This field has already been discovered"},
            {GameMessage::PLAYERS_TURN,             "It's your turn"}
    };
    if (messages.empty()) {
        return "";
    }
    std::string messagesList;
    for (auto &message: messages) {
        messagesList.append(messagesMap[message] + '\n');
    };
    if (!extraNewline) {
        messagesList.pop_back();
    }
    return messagesList;
}

/**
 * @brief Splits the input by spaces
 * @param command string to be split
 * @return vector of strings being a result of split
 *
 * Replacement for python's split()
 */
std::vector<std::string> splitCommand(std::string command) {
    std::vector<std::string> splitParts;
    command += ' ';
    std::string current;
    for (auto &letter: command) {
        if (letter != ' ') {
            current += letter;
        } else if (!current.empty()) {
            splitParts.push_back(current);
            current.clear();
        }
    }
    return splitParts;
}

/**
 * @brief Checks if the string contains a number
 * @param possiblyNumber string to check
 * @return true if it contains a number, false otherwise
 *
 * Created so I don't have to handle exceptions while converting strings to numbers
 */
bool isNumeric(std::string possiblyNumber) {
    for (auto &character: possiblyNumber) {
        if (character < '0' || character > '9') {
            return false;
        }
    }
    return true;
}

/**
 * @brief Initializes classes handling the actual game
 */
BattleshipCLI::BattleshipCLI() {
    this->fleetCreator = FleetCreator();
    this->game = Game();
    this->settings = Settings();
    this->settings.loadSettings();
    this->state = AppState::MAIN_MENU;
    this->quit = false;
    this->prompt = "> ";
}

/**
 * @brief Displays content in the console
 */
void BattleshipCLI::display() {
    cls();
    if (this->state == AppState::MAIN_MENU) {
        this->displayMainMenu();
    } else if (this->state == AppState::SETUP) {
        this->displayFleetCreator();
    } else if (this->state == AppState::GAME) {
        this->displayGame();
    } else if (this->state == AppState::HOW_TO_PLAY) {
        this->displayHelp();
    } else {
        this->displaySettings();
    }
}

/**
 * @brief Displays (prints out) the Main Menu
 */
void BattleshipCLI::displayMainMenu() {
    std::string menuContent = "Welcome to Battleship!\n"
                              "1. Play the game\n"
                              "2. Settings\n"
                              "3. How to play\n"
                              "4. Exit\n\n";
    std::cout << menuContent << std::endl;
}

/**
 * @brief Displays (prints out) the Fleet Creator
 */
void BattleshipCLI::displayFleetCreator() {
    Board displayBoard = this->fleetCreator.getBoardDisplay();
    std::cout << "Set up your fleet:" << std::endl << displayBoard.toString() << std::endl;
    std::vector<FCMessage> messages = this->fleetCreator.getDisplayMessages();
    std::cout << formatFleetCreatorMessages(messages) << std::endl;
}

/**
 * @brief Displays (prints out) the Game
 */
void BattleshipCLI::displayGame() {
    Fleet enemyFleet = this->game.getEnemyFleetDisplay();
    std::string enemyFleetStr = enemyFleet.toString(true);
    Board enemyBoard = this->game.getEnemyBoardDisplay();
    std::string enemyBoardStr = enemyBoard.toString();
    std::string splitter = "---------------\n";
    Board playerBoard = this->game.getPlayerBoardDisplay();
    std::string playerBoardStr = playerBoard.toString();
    Fleet playerFleet = this->game.getPlayerFleetDisplay();
    std::string playerFleetStr = playerFleet.toString(true);
    std::vector<GameMessage> messages = this->game.getDisplayMessages();
    std::cout << enemyFleetStr << std::endl << enemyBoardStr << std::endl << splitter;
    std::cout << playerBoardStr << std::endl << playerFleetStr << std::endl;
    std::cout << formatGameMessages(messages) << std::endl;
}

/**
 * @brief Displays (prints out) the Help screen
 */
void BattleshipCLI::displayHelp() {
    std::string helpContent = "How to play:\n"
                              "The goal of this game is to destroy the enemy fleet. You and your opponent shoot at "
                              "selected fields on the board and get information whether you hit or sunk the enemy ship. "
                              "If there was a hit, the player's next move is made, otherwise the enemy moves.";
    std::cout << helpContent << std::endl;
}

/**
 * @brief Displays (prints out) the Settings page
 */
void BattleshipCLI::displaySettings() {
    std::map<Setting, bool> settingsMap = this->settings.getSettings();
    std::cout << "1. Mark fields around sunken ships: " << (settingsMap[Setting::MARK_MISSES_AROUND] ? "Yes" : "No")
              << std::endl;
    std::cout << "2. Harder enemy: " << (settingsMap[Setting::HARD_ENEMY] ? "Yes" : "No") << std::endl;
}

/**
 * @brief Handles user input and interprets it, creating a command pair
 * @return a pair containing the Command enum and arguments
 */
std::pair<Command, std::pair<char, int>> BattleshipCLI::playerInput() {
    std::cout << this->prompt;
    std::string command;
    std::getline(std::cin, command);
    std::transform(command.begin(), command.end(), command.begin(), ::tolower);
    std::vector<std::string> commandParts = splitCommand(command);
    if (this->state == AppState::MAIN_MENU) {
        return this->playerInputMainMenu(commandParts);
    } else if (this->state == AppState::SETUP) {
        return this->playerInputFleetCreator(commandParts);
    } else if (this->state == AppState::GAME) {
        return this->playerInputGame(commandParts);
    } else if (this->state == AppState::HOW_TO_PLAY) {
        return std::make_pair(Command::EXIT_TO_MAIN, std::make_pair(' ', 0));
    } else {
        return this->playerInputSettings(commandParts);
    }
}

/**
 * @brief Interprets the Main Menu commands
 * @param commandParts split user input
 * @return formatted command in a pair of command and arguments
 */
std::pair<Command, std::pair<char, int>> BattleshipCLI::playerInputMainMenu(std::vector<std::string> commandParts) {
    if (commandParts.empty()) {
        return std::make_pair(Command::NOP, std::make_pair(' ', 0));
    } else {
        if (commandParts[0][0] == '1') {
            return std::make_pair(Command::MAIN_START_SETUP, std::make_pair(' ', 0));
        } else if (commandParts[0][0] == '2') {
            return std::make_pair(Command::MAIN_SETTINGS, std::make_pair(' ', 0));
        } else if (commandParts[0][0] == '3') {
            return std::make_pair(Command::MAIN_START_HTP, std::make_pair(' ', 0));
        } else if (commandParts[0][0] == '4') {
            return std::make_pair(Command::MAIN_EXIT, std::make_pair(' ', 0));
        } else {
            return std::make_pair(Command::NOP, std::make_pair(' ', 0));
        }
    }
}

/**
 * @brief Interprets the Fleet Creator commands
 * @param commandParts split user input
 * @return formatted command in a pair of command and arguments
 */
std::pair<Command, std::pair<char, int>> BattleshipCLI::playerInputFleetCreator(std::vector<std::string> commandParts) {
    if (commandParts.empty()) {
        return std::make_pair(Command::NOP, std::make_pair(' ', 0));
    }
    if (commandParts[0] == "rot") {
        return std::make_pair(Command::CREATOR_SHIP_ROTATE, std::make_pair(' ', 0));
    } else if (commandParts[0] == "rand") {
        return std::make_pair(Command::CREATOR_FLEET_RAND, std::make_pair(' ', 0));
    } else if (commandParts[0] == "done") {
        return std::make_pair(Command::CREATOR_DONE, std::make_pair(' ', 0));
    } else if (commandParts[0] == "quit" || commandParts[0] == "exit") {
        return std::make_pair(Command::EXIT_TO_MAIN, std::make_pair(' ', 0));
    } else if (commandParts[0] == "help") {
        return std::make_pair(Command::CREATOR_HELP, std::make_pair(' ', 0));
    } else if (commandParts.size() >= 3) {
        if (commandParts[1].size() == 1 && isNumeric(commandParts[2])) {
            char x = commandParts[1][0];
            int y = std::stoi(commandParts[2]);
            if (commandParts[0] == "sel") {
                return std::make_pair(Command::CREATOR_SHIP_SELECT, std::make_pair(x, y));
            } else if (commandParts[0] == "mv") {
                return std::make_pair(Command::CREATOR_SHIP_MOVE, std::make_pair(x, y));
            } else {
                return std::make_pair(Command::NOP, std::make_pair(' ', 0));
            }
        } else {
            return std::make_pair(Command::NOP, std::make_pair(' ', 0));
        }
    } else {
        return std::make_pair(Command::NOP, std::make_pair(' ', 0));
    }
}

/**
 * @brief Interprets the Game commands
 * @param commandParts split user input
 * @return formatted command in a pair of command and arguments
 */
std::pair<Command, std::pair<char, int>> BattleshipCLI::playerInputGame(std::vector<std::string> commandParts) {
    if (commandParts.empty()) {
        return std::make_pair(Command::NOP, std::make_pair(' ', 0));
    }
    if (commandParts[0] == "help") {
        return std::make_pair(Command::GAME_HELP, std::make_pair(' ', 0));
    } else if (commandParts[0] == "quit" || commandParts[0] == "exit") {
        return std::make_pair(Command::EXIT_TO_MAIN, std::make_pair(' ', 0));
    } else if (commandParts.size() >= 3) {
        if (commandParts[1].size() == 1 && isNumeric(commandParts[2])) {
            char x = commandParts[1][0];
            int y = std::stoi(commandParts[2]);
            if (commandParts[0] == "st") {
                return std::make_pair(Command::GAME_SHOOT, std::make_pair(x, y));
            } else if (commandParts[0] == "mk") {
                return std::make_pair(Command::GAME_MARK_FIELD, std::make_pair(x, y));
            } else if (commandParts[0] == "unmk") {
                return std::make_pair(Command::GAME_UNMARK_FIELD, std::make_pair(x, y));
            } else {
                return std::make_pair(Command::NOP, std::make_pair(' ', 0));
            }
        } else {
            return std::make_pair(Command::NOP, std::make_pair(' ', 0));
        }
    } else {
        return std::make_pair(Command::NOP, std::make_pair(' ', 0));
    }
}

/**
 * @brief Interprets the Settings input
 * @param commandParts split user input
 * @return formatted command in a pair of command and arguments
 */
std::pair<Command, std::pair<char, int>> BattleshipCLI::playerInputSettings(std::vector<std::string> commandParts) {
    if (commandParts.empty()) {
        return std::make_pair(Command::NOP, std::make_pair(' ', 0));
    } else {
        if (commandParts[0][0] == '1') {
            return std::make_pair(Command::SETTINGS_MMA, std::make_pair(' ', 0));
        } else if (commandParts[0][0] == '2') {
            return std::make_pair(Command::SETTINGS_HARD_ENEMY, std::make_pair(' ', 0));
        } else {
            return std::make_pair(Command::EXIT_TO_MAIN, std::make_pair(' ', 0));
        }
    }
}

/**
 * @brief Executes user's command
 * @param command Command enum representing command
 * @param x x argument of a command
 * @param y y argument of a command
 */
void BattleshipCLI::execute(Command command, char x, int y) {
    if (this->state == AppState::MAIN_MENU) {
        this->executeMainMenu(command);
    } else if (this->state == AppState::SETUP) {
        this->executeFleetCreator(command, x, y);
    } else if (this->state == AppState::GAME) {
        this->executeGame(command, x, y);
    } else if (this->state == AppState::HOW_TO_PLAY) {
        this->state = AppState::MAIN_MENU;
    } else {
        this->executeSettings(command);
    }
}

/**
 * @brief Executes Main Menu commands
 * @param command Command enum representing command
 */
void BattleshipCLI::executeMainMenu(Command command) {
    if (command == Command::MAIN_START_SETUP) {
        this->fleetCreator.start();
        this->state = AppState::SETUP;
    } else if (command == Command::MAIN_SETTINGS) {
        this->state = AppState::SETTINGS;
    } else if (command == Command::MAIN_START_HTP) {
        this->state = AppState::HOW_TO_PLAY;
    } else if (command == Command::MAIN_EXIT) {
        this->quit = true;
    }
}

/**
 * @brief Executes Main Menu commands
 * @param command Command enum representing command
 * @param x x argument of a command
 * @param y y argument of a command
 */
void BattleshipCLI::executeFleetCreator(Command command, char x, int y) {
    if (command == Command::CREATOR_SHIP_SELECT) {
        this->fleetCreator.selectShip(x, y);
    } else if (command == Command::CREATOR_SHIP_MOVE) {
        this->fleetCreator.setShipPosition(x, y);
    } else if (command == Command::CREATOR_SHIP_ROTATE) {
        this->fleetCreator.changeShipRotation();
    } else if (command == Command::CREATOR_FLEET_RAND) {
        this->fleetCreator.randomFleet();
    } else if (command == Command::CREATOR_DONE) {
        std::pair<Board, Fleet> setup = this->fleetCreator.getSetup();
        this->game.startGame(setup.first, setup.second);
        this->state = AppState::GAME;
    } else if (command == Command::CREATOR_HELP) {
        this->fleetCreator.setupHelp();
    } else if (command == Command::EXIT_TO_MAIN) {
        this->state = AppState::MAIN_MENU;
    }
}

/**
 * @brief Executes Game commands
 * @param command Command enum representing command
 * @param x x argument of a command
 * @param y y argument of a command
 */
void BattleshipCLI::executeGame(Command command, char x, int y) {
    if (this->game.isWon()) {
        this->state = AppState::MAIN_MENU;
    } else {
        if (!this->game.isPlayersTurn()) {
            this->game.enemyMove();
        } else {
            if (command == Command::GAME_SHOOT) {
                this->game.discoverField(x, y);
            } else if (command == Command::GAME_MARK_FIELD) {
                this->game.markField(x, y);
            } else if (command == Command::GAME_UNMARK_FIELD) {
                this->game.unmarkField(x, y);
            } else if (command == Command::GAME_HELP) {
                this->game.gameHelp();
            } else if (command == Command::EXIT_TO_MAIN) {
                this->state = AppState::MAIN_MENU;
            }
        }
    }
}

/**
 * @brief Executes Settings commands
 * @param command Command enum representing command
 */
void BattleshipCLI::executeSettings(Command command) {
    if (command == Command::SETTINGS_MMA) {
        bool settingMMA = this->settings.getSettings()[Setting::MARK_MISSES_AROUND];
        this->settings.setMarkMissesAround(!settingMMA);
    } else if (command == Command::SETTINGS_HARD_ENEMY) {
        bool settingHardEnemy = this->settings.getSettings()[Setting::HARD_ENEMY];
        this->settings.setHardEnemy(!settingHardEnemy);
    } else {
        this->game.applySettings(this->settings.getSettings());
        this->state = AppState::MAIN_MENU;
    }
}

/**
 * @brief Starts the main game loop
 *
 * Begins the "fetch-execute" loop, which displays the current contents,
 * fetches the command from the user, interprets it and executes it
 */
void BattleshipCLI::start() {
    while (!this->quit) {
        this->display();
        std::pair<Command, std::pair<char, int>> parsedPlayerInput = this->playerInput();
        this->execute(parsedPlayerInput.first, parsedPlayerInput.second.first, parsedPlayerInput.second.second);
    }
    this->settings.saveSettings();
}
