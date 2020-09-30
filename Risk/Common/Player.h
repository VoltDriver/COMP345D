#pragma once
#include <vector>

#include "Player.h"
#include "Country.h"

class Card;
class Order;

class Player {
private:
    vector<Country*> owned_countries;
    vector<Order*> orders;
public:
    vector<Country*> to_defend();
    vector<Country*> to_attack();
    void issue_order(Order* order);
};