#pragma once
#include <vector>

using namespace std;

#include "Map.h"

/**
 * Place holder class for cards.
 */
class Card{
private:
    string card = "card";
public:
    Card();
};


/**
 * Place holder class for orders.
 */
class Order {
private:
    string order = "order";
public:
    Order();
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
    void display_territories(vector<Territory*> &t);

    Player& operator=(const Player &p);
};