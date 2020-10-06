#pragma once
#include <vector>

#include "Player.h"
#include "Country.h"

class Card;
class Order;

class Player {
private:
    vector<Country*> countries_toDefend;
    vector<Country*> countries_toAttack;
    vector<Order*> orders;
    vector<Card*> cards;
public:
    Player();

    vector<Country*> to_defend();
    vector<Country*> to_attack();
    void issue_order(Order* order);
};