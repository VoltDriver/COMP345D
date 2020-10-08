#pragma once
#include <vector>

using namespace std;

#include "Map.h"


/**
 * Place holder class for orders.
 */
class Order {
private:
    string order;
public:
    Order(string order);

    string get_order() const;
};


/**
 * Place holder class for cards.
 */
class Card{
private:
    string card = "card";
public:
    Card(string card);

    string get_card() const;
};


/**
 * Represents a player.
 */
class Player {
private:
    vector<Territory*> territories;
    vector<Order*> orders;
    vector<Card*> cards;

public:
    explicit Player(vector<Territory*> territories, vector<Order*> orders, vector<Card*> cards);
    Player(const Player &p);

    vector<Territory*> to_defend();
    vector<Territory*> to_attack();
    void issue_order(Order* order);


    Player& operator=(const Player &p);
};