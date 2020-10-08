#include <iostream>
#include "Common/Player.h"

int main() {
    // creating some arbitrary vector of territory objects
    auto *ter1 = new Territory(1, "Canada", 1);
    auto *ter2 = new Territory(2, "USA", 2);
    auto *ter3 = new Territory(3, "Brazil", 3);

    vector<Territory*> territories = {ter1, ter2, ter3};

    // creating some arbitrary vector of orders
    auto *ord = new Order();
    vector<Order*> orders = {ord};

    // creating some arbitrary vector of cards
    auto *card = new Card();
    vector<Card*> cards = {card};

    auto *player1 = new Player(territories, orders, cards);


    player1->to_defend();
    player1->to_attack();

    return 0;
}
