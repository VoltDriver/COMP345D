#include <iostream>
#include "Common/Player.h"
#include "Common/Country.h"

int main() {
    Country *a = new Country(1, "Canada", 1);
    Country *b = new Country(2, "USA", 2);
    Country *c = new Country(3, "Brazil", 3);

    vector<Country*> countries = {a, b, c};

    Player *player1 = new Player(countries);

    player1->to_defend();
    player1->to_attack();

    return 0;
}
