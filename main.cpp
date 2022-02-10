#include <iostream>
#include "Fleet.h"

using namespace std;

int main() {
    Fleet fleet = Fleet();
    fleet.createRandom();
    cout << fleet.toString() << endl;
    Board testBoard = Board();
    testBoard.placeFleet(fleet);
    cout << testBoard.toString();
    return 0;
}
