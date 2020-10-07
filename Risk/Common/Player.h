#pragma once
#include <vector>

#include "Player.h"
#include "Country.h"

class Card;
class Order {
private:
    string order;
};

class Player {
private:
    vector<Country*> countries;
    vector<Order*> orders;
    vector<Card*> cards;
public:
    Player(vector<Country*> countries);
    Player(const Player &p);

    vector<Country*> to_defend();
    vector<Country*> to_attack();
    void issue_order(Order* order);
};