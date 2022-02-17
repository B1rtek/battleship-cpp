#include <QScrollBar>
#include "BattleshipGUI.h"

#ifdef _WIN32
QSize windowSize = QSize(700, 540);
#endif
#ifdef __linux__
QSize windowSize = QSize(730, 560);
#endif

/**
 * @brief Creates icon objects and returns them in a map
 * @return map with all icons needed to display boards
 */
std::map<FieldStatus, QIcon> loadIcons() {
    return std::map<FieldStatus, QIcon>{
            {FieldStatus::NOTHING,  QIcon(QPixmap("res/nothing.png"))},
            {FieldStatus::MISS,     QIcon(QPixmap("res/miss.png"))},
            {FieldStatus::SHIP,     QIcon(QPixmap("res/ship.png"))},
            {FieldStatus::SUNK,     QIcon(QPixmap("res/sunk.png"))},
            {FieldStatus::SELECTED, QIcon(QPixmap("res/sel.png"))}
    };
}

/**
 * @brief Initializes all elements of the game and all additional widgets created
 * in code rather than in the designer like UIBoards and UIFleets
 * @param parent Qt5 stuff, unused
 */
BattleshipGUI::BattleshipGUI(QWidget *parent) {
    this->ui = Ui_Battleship();
    this->ui.setupUi(this);
    this->fleetCreator = FleetCreator();
    this->game = Game();
    this->fleetCreatorBoard = UIBoard();
    this->gamePlayerBoard = UIBoard();
    this->gameEnemyBoard = UIBoard();
    this->gamePlayerFleet = UIFleet();
    this->gameEnemyFleet = UIFleet();
    this->settings = Settings();
    this->settings.loadSettings();
    this->setupBoards();
    this->setupFleetDisplays();
    this->linkButtons();
    this->applySettings();
    this->resizeWindow();
    this->fixPySide2UICBug();
    this->ui.stackedWidget->setCurrentIndex(0);
}

/**
 * @brief Creates the Game and Fleet Creator boards in the UI
 *
 * Initializes them, assigns actions to their buttons and places them in
 * their target Grid Layouts
 */
void BattleshipGUI::setupBoards() {
    std::map<FieldStatus, QIcon> icons = loadIcons();
    this->fleetCreatorBoard.setIcons(icons);
    this->gamePlayerBoard.setIcons(icons);
    this->gameEnemyBoard.setIcons(icons);
    auto *fleetCreatorLeftClickFunctionPointer = new std::function<void(char, int)>(
            std::bind(&BattleshipGUI::fleetCreatorLeftClick, this, std::placeholders::_1, std::placeholders::_2));
    this->fleetCreatorBoard.defineLeftClickAction(fleetCreatorLeftClickFunctionPointer);
    auto *gameLeftClickFunctionPointer = new std::function<void(char, int)>(
            std::bind(&BattleshipGUI::gameLeftClick, this, std::placeholders::_1, std::placeholders::_2));
    this->gameEnemyBoard.defineLeftClickAction(gameLeftClickFunctionPointer);
    auto *gameRightClickFunctionPointer = new std::function<void(char, int)>(
            std::bind(&BattleshipGUI::gameRightClick, this, std::placeholders::_1, std::placeholders::_2));
    this->gameEnemyBoard.defineRightClickAction(gameRightClickFunctionPointer);
    this->fleetCreatorBoard.placeButtonArray(this->ui.grid_setup_board);
    this->gamePlayerBoard.placeButtonArray(this->ui.grid_game_player_board);
    this->gameEnemyBoard.placeButtonArray(this->ui.grid_game_enemy_board);
}

/**
 * @brief Creates the UIFleets in the UI
 *
 * Initializes them, assigns actions to their buttons and places them in
 * their target Grid Layouts
 */
void BattleshipGUI::setupFleetDisplays() {
    std::map<FieldStatus, QIcon> icons = loadIcons();
    this->gamePlayerFleet.setIcons(icons);
    this->gameEnemyFleet.setIcons(icons);
    auto *gameLeftClickFunctionPointer = new std::function<void(char, int)>(
            std::bind(&BattleshipGUI::gameLeftClick, this, std::placeholders::_1, std::placeholders::_2));
    this->gamePlayerFleet.defineLeftClickAction(gameLeftClickFunctionPointer);
    this->gamePlayerFleet.defineRightClickAction(gameLeftClickFunctionPointer);
    this->gameEnemyFleet.defineLeftClickAction(gameLeftClickFunctionPointer);
    this->gameEnemyFleet.defineRightClickAction(gameLeftClickFunctionPointer);
    this->gamePlayerFleet.placeButtonArray(this->ui.grid_game_player_fleet);
    this->gameEnemyFleet.placeButtonArray(this->ui.grid_game_enemy_fleet);
}

/**
 * @brief Assigns functions to all UI buttons' clicked and stateChanged signals
 */
void BattleshipGUI::linkButtons() {
    connect(this->ui.button_main_play, &QPushButton::clicked, this, &BattleshipGUI::fleetCreatorStart);
    connect(this->ui.button_main_htp, &QPushButton::clicked, this, &BattleshipGUI::HTPShow);
    connect(this->ui.button_main_settings, &QPushButton::clicked, this, &BattleshipGUI::settingsShow);
    connect(this->ui.button_main_quit, &QPushButton::clicked, this, &BattleshipGUI::quit);
    connect(this->ui.button_setup_exit, &QPushButton::clicked, this, &BattleshipGUI::returnToMain);
    connect(this->ui.button_setup_rand, &QPushButton::clicked, this, &BattleshipGUI::fleetCreatorRand);
    connect(this->ui.button_setup_rot, &QPushButton::clicked, this, &BattleshipGUI::fleetCreatorRot);
    connect(this->ui.button_setup_done, &QPushButton::clicked, this, &BattleshipGUI::fleetCreatorDone);
    connect(this->ui.button_game_main, &QPushButton::clicked, this, &BattleshipGUI::returnToMain);
    connect(this->ui.button_htp_back, &QPushButton::clicked, this, &BattleshipGUI::returnToMain);
    connect(this->ui.button_settings_back, &QPushButton::clicked, this, &BattleshipGUI::settingsSaveAndBack);
    connect(this->ui.checkbox_settings_mma, &QCheckBox::stateChanged, this, &BattleshipGUI::settingsToggleMMA);
    connect(this->ui.checkbox_settings_hard_enemy, &QCheckBox::stateChanged, this,
            &BattleshipGUI::settingsToggleHardEnemy);
}

/**
 * @brief Applies saved settings to the checkboxes and Game
 */
void BattleshipGUI::applySettings() {
    std::map<Setting, bool> settingsToApply = this->settings.getSettings();
    this->ui.checkbox_settings_mma->setChecked(settingsToApply[Setting::MARK_MISSES_AROUND]);
    this->ui.checkbox_settings_hard_enemy->setChecked(settingsToApply[Setting::HARD_ENEMY]);
    this->game.applySettings(settingsToApply);
}

/**
 * @brief Sets text to Qt.AlignJustify
 *
 * Only here because in the python version this didn't compile in the layout
 */
void BattleshipGUI::fixPySide2UICBug() {
    this->ui.label_htp_help->setAlignment(Qt::AlignJustify);
}

/**
 * @brief Resizes the window to the smallest size in which the game screen looks good
 *
 * The window can be resized afterwards, but the buttons which represent the boards
 * might be a bit squished
 */
void BattleshipGUI::resizeWindow() {
    this->resize(windowSize);
}

/**
 * @brief Starts the Fleet Creator, starting the setup stage of the game
 */
void BattleshipGUI::fleetCreatorStart() {
    this->fleetCreator.start();
    this->fleetCreatorRefresh();
    this->ui.stackedWidget->setCurrentIndex(1);
}

/**
 * @brief Shows the How To Play page
 */
void BattleshipGUI::HTPShow() {
    this->ui.stackedWidget->setCurrentIndex(3);
}

/**
 * @brief Returns to the Main Menu
 */
void BattleshipGUI::returnToMain() {
    this->ui.stackedWidget->setCurrentIndex(0);
}

/**
 * @brief Performs the left click operations in the Fleet Creator, and refreshes
 * the Fleet Creator board afterwards
 * @param x x argument of a command called by a button that this function
 * was assigned to, most likely x coordinate of a field
 * @param y y argument of a command called by a button that this function
 * was assigned to, most likely y coordinate of a field
 */
void BattleshipGUI::fleetCreatorLeftClick(char x, int y) {
    if (this->fleetCreator.containsNotSelectedShip(x, y)) {
        this->fleetCreator.selectShip(x, y);
    } else {
        this->fleetCreator.setShipPosition(x, y);
    }
    this->fleetCreatorRefresh();
}

/**
 * @brief Calls the function in the Fleet Creator which creates a new random
 * fleet, and refreshes the Fleet Creator board afterwards
 */
void BattleshipGUI::fleetCreatorRand() {
    this->fleetCreator.randomFleet();
    this->fleetCreatorRefresh();
}

/**
 * @brief Calls the function in the Fleet Creator which rotates the selected
 * ship, and refreshes the Fleet Creator board afterwards
 */
void BattleshipGUI::fleetCreatorRot() {
    this->fleetCreator.changeShipRotation();
    this->fleetCreatorRefresh();
}

/**
 * @brief Ends the setup stage of the game and starts the Game itself, passing
 * the created fleet from the Fleet Creator to the Game as the player's fleet
 */
void BattleshipGUI::fleetCreatorDone() {
    std::pair<Board, Fleet> setup = this->fleetCreator.getSetup();
    this->game.startGame(setup.first, setup.second);
    this->ui.game_plain_text_edit_log->clear();
    this->gameRefresh();
    this->ui.stackedWidget->setCurrentIndex(2);
}

/**
 * @brief Refreshes the Fleet Creator UIBoard after performing an action
 */
void BattleshipGUI::fleetCreatorRefresh() {
    Board board = this->fleetCreator.getBoardDisplay();
    Ship *ship = this->fleetCreator.getSelectedShip();
    this->fleetCreatorBoard.updateBoard(board, ship);
}

/**
 * @brief Performs the left click operations in the Game, and refreshes all Game
 * UI elements afterwards
 * @param x x argument of a command called by a button that this function
 * was assigned to, most likely x coordinate of a field
 * @param y y argument of a command called by a button that this function
 * was assigned to, most likely y coordinate of a field
 */
void BattleshipGUI::gameLeftClick(char x, int y) {
    if (this->game.isWon()) {
        this->ui.stackedWidget->setCurrentIndex(0);
    }
    if (this->game.isPlayersTurn()) {
        this->game.discoverField(x, y);
    } else {
        this->game.enemyMove();
    }
    this->gameRefresh();
}

/**
 * @brief Performs the right click operations in the Game, and refreshes all Game
 * UI elements afterwards
 * @param x x argument of a command called by a button that this function
 * was assigned to, most likely x coordinate of a field
 * @param y y argument of a command called by a button that this function
 * was assigned to, most likely y coordinate of a field
 */
void BattleshipGUI::gameRightClick(char x, int y) {
    FieldStatus status = this->game.getEnemyBoardDisplay().getFieldStatus(x, y);
    if (status != FieldStatus::MISS) {
        this->game.markField(x, y);
    } else {
        this->game.unmarkField(x, y);
    }
    this->gameRefresh();
}

/**
 * @brief Refreshes all Game UI elements after player or the enemy performs a move
 */
void BattleshipGUI::gameRefresh() {
    Board playerBoard = this->game.getPlayerBoardDisplay();
    Board enemyBoard = this->game.getEnemyBoardDisplay();
    this->gamePlayerBoard.updateBoard(playerBoard, nullptr);
    this->gameEnemyBoard.updateBoard(enemyBoard, nullptr);
    Fleet playerFleet = this->game.getPlayerFleetDisplay();
    Fleet enemyFleet = this->game.getEnemyFleetDisplay();
    this->gamePlayerFleet.updateFleetDisplay(playerFleet);
    this->gameEnemyFleet.updateFleetDisplay(enemyFleet);
    std::vector<GameMessage> messages = this->game.getDisplayMessages();
    std::string formatted = formatGameMessages(messages, true);
    this->ui.game_plain_text_edit_log->insertPlainText(QString(formatted.c_str()));
    QScrollBar *scrollbar = this->ui.game_plain_text_edit_log->verticalScrollBar();
    scrollbar->setValue(scrollbar->maximum() - 2);
}

/**
 * @brief Shows the settings page
 */
void BattleshipGUI::settingsShow() {
    this->ui.stackedWidget->setCurrentIndex(4);
}

/**
 * @brief Toggles the Setting::MARK_MISSES_AROUND setting
 *
 * Called by checkbox assigned to this setting after it changes its state
 */
void BattleshipGUI::settingsToggleMMA() {
    bool newState = this->ui.checkbox_settings_mma->isChecked();
    this->settings.setMarkMissesAround(newState);
}

/**
 * @brief Toggles the Setting::HARD_ENEMY setting
 *
 * Called by checkbox assigned to this setting after it changes its state
 */
void BattleshipGUI::settingsToggleHardEnemy() {
    bool newState = this->ui.checkbox_settings_hard_enemy->isChecked();
    this->settings.setHardEnemy(newState);
}

/**
 * @brief Applies the settings set on the settings page and returns to the main menu
 */
void BattleshipGUI::settingsSaveAndBack() {
    this->game.applySettings(this->settings.getSettings());
    this->returnToMain();
}

/**
 * @brief Quits the game by calling exit(0) after saving settings
 */
void BattleshipGUI::quit() {
    this->settings.saveSettings();
    exit(0);
}

/**
 * @brief Registers left mouse clicks on the window outside of buttons
 * @param event QMouseEvent generated with the mouse click
 *
 * Used to advance the game to the next enemy move without the need for a player
 * to click a dedicated button, makes interaction with the game easier and more intuitive
 */
void BattleshipGUI::mousePressEvent(QMouseEvent *event) {
    /// check if the click happened on the game page
    if (this->ui.stackedWidget->currentIndex() == 2) {
        if (!this->game.isPlayersTurn()) {
            this->game.enemyMove();
            this->gameRefresh();
        }
        if (this->game.isWon()) {
            this->ui.stackedWidget->setCurrentIndex(0);
        }
    }
}
