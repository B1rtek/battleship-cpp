#include "include/BattleshipGUI.h"
#include <argparse.hpp>
#include <QApplication>
#include <QStyleFactory>

using namespace std;
using namespace argparse;

/**
 * @brief The main function, parses the command line arguments and starts the correct
 * version of the game according to those arguments
 * @return 0 if the whole thing somehow doesn't crash
 */
int main(int argc, char *argv[]) {
    ArgumentParser parser("Battleship");
    parser.add_argument("--no-ui").default_value(false).implicit_value(true).help("launches the game in console");
    parser.parse_args(argc, argv);
    if(parser["--no-ui"] == true) {
        BattleshipCLI battleship = BattleshipCLI();
        battleship.start();
        return 0;
    } else {
        QApplication app(argc, argv);
#ifdef _WIN32
        QApplication::setStyle("windowsvista");
#elif __linux__
        QApplication::setStyle("fusion");
#endif
        BattleshipGUI battleshipWindow = BattleshipGUI();
        battleshipWindow.show();
        return QApplication::exec();
    }
}
