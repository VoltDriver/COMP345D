#include <iostream>
#include "Common/Player.h"

int main() {
    auto *a = new Territory(1, "Canada", 1);
    auto *b = new Territory(2, "USA", 2);
    auto *c = new Territory(3, "Brazil", 3);

    vector<Territory*> countries = {a, b, c};

    auto *player1 = new Player(countries);

    player1->to_defend();
    player1->to_attack();

    return 0;
}
