#include "include/BattleshipCLI.h"
#include <argparse.hpp>

using namespace std;
using namespace argparse;

/**
 * @brief The console version only file, doesn't need any Qt5 dlls and other weird stuff
 */
int main() {
    BattleshipCLI battleship = BattleshipCLI();
    battleship.start();
    return 0;
}
