#include "BattleshipCLI.h"

using namespace std;

/**
 * @brief The main function, parses the command line arguments and starts the correct
 * version of the game according to those arguments
 * @return 0 if the whole thing somehow doesn't crash
 */
int main() {
    BattleshipCLI battleship = BattleshipCLI();
    battleship.start();
    return 0;
}
