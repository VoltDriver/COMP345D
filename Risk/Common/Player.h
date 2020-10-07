#pragma once
#include <vector>

#include "Player.h"
#include "Territory.h"

class Card;
class Order {
private:
    string order;
};

class Player {
private:
    vector<Territory*> territories;
    vector<Order*> orders;
    vector<Card*> cards;
public:
    Player(vector<Territory*> territories);
    Player(const Player &p);

    vector<Territory*> to_defend();
    vector<Territory*> to_attack();
    void issue_order(Order* order);
};