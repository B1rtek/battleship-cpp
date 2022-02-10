#include <iostream>
#include "Fleet.h"
#include "Field.h"
#include "Board.h"

using namespace std;

int main() {
    Field field;
    cout << field.getStatus() << endl;
    cout << field.toString();
    field.setStatus(FieldStatus::SHIP);
    cout << field.toString();
    pair<int, int> koordy = gameToArrayCoords('a', 1);
    cout << koordy.first << ' ' << koordy.second << endl;
    koordy = gameToArrayCoords('d', 10);
    cout << koordy.first << ' ' << koordy.second << endl;
    for (auto i: returnAllFieldCoordinates()) {
        cout << i.first << ' ' << i.second << endl;
    }
    cout << fieldOnBoard(make_pair('a', 1)) << endl;
    cout << fieldOnBoard(make_pair('j', 10)) << endl;
    cout << fieldOnBoard(make_pair('j', 11)) << endl;
    cout << fieldOnBoard(make_pair('a', 0)) << endl;
    cout << fieldOnBoard(make_pair('$', 69)) << endl;
    return 0;
}
