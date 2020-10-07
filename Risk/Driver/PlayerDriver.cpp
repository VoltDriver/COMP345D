#include <iostream>
#include "Common/Player.h"
#include "Common/Territory.h"

int main() {
    Territory *a = new Territory(1, "Canada", 1);
    Territory *b = new Territory(2, "USA", 2);
    Territory *c = new Territory(3, "Brazil", 3);

    vector<Territory*> countries = {a, b, c};

    Player *player1 = new Player(countries);

    player1->to_defend();
    player1->to_attack();

    return 0;
}
