#include <iostream>
#include "Common/Player.h"
#include "Common/Orders.h"
#include "Common/Cards.h"

int main() {

    ID id;

    // creating some arbitrary vector of territory objects
    auto *ter1 = new Territory(1, "Canada", 1);
    auto *ter2 = new Territory(2, "USA", 2);
    auto *ter3 = new Territory(3, "Brazil", 3);

    vector<Territory*> territories = {ter1, ter2, ter3};

    // creating some arbitrary vector of orders
    auto *ord1 = new Order(id.setID());
    OrdersList* orders = new OrdersList();
    orders->add(ord1);

    // creating some arbitrary hand of cards
    auto *card1 = new Card(Bomb);
    auto *hand1 = new Hand();
    hand1->addCard(*card1);

    // creating a player object
    auto *player1 = new Player(territories, orders, hand1, 0);

    // adding order to list of orders
    auto *ord2 = new Deploy(id.setID(), 2, territories.at(0), player1);
    player1->addOrder(ord2);

    // return list of territories
    vector<Territory*> terrToDef = player1->to_defend();
    vector<Territory*> terrToAtk = player1->to_attack();

    // printing out territories to defend
    cout << "\nVerifying that terrToDef is able to return a vector of Territories" << endl;
    for (int i = 0; i < terrToDef.size(); i++) {
        cout << *terrToDef[i];
    }

    // printing player object info
    cout << "\nPrinting player objects" << endl;
    cout << *player1;

    delete player1;

    return 0;
}
