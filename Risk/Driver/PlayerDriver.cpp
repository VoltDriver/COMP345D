#include <iostream>
#include "Common/Player.h"

int main() {
    // creating some arbitrary vector of territory objects
    auto *ter1 = new Territory(1, "Canada", 1);
    auto *ter2 = new Territory(2, "USA", 2);
    auto *ter3 = new Territory(3, "Brazil", 3);

    vector<Territory*> territories = {ter1, ter2, ter3};

    // creating some arbitrary vector of orders
    auto *ord1 = new Order("this is an order");
    vector<Order*> orders = {ord1};

    // creating some arbitrary vector of cards
    auto *card1 = new Card("this is a card");
    vector<Card*> cards = {card1};

    // creating a player object
    auto *player1 = new Player(territories, orders, cards);

    // adding order to list of orders
    auto *ord2 = new Order("this is another order");
    player1->issue_order(ord2);

    // return list of territories
    player1->to_defend();
    player1->to_attack();

    return 0;
}
