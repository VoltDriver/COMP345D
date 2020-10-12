#pragma once
#include <vector>

using namespace std;

#include "Map.h"


/**
 * Place holder class for orders.
 */
class Order {
public:
    Order(string order);
    string order;

};


/**
 * Place holder class for cards.
 */
class Card{
public:
    Card(string card);
    string card = "card";
};


/**
 * Represents a player. A player hold territories, orders and cards.
 */
class Player {
private:
    vector<Territory*> territories;
    vector<Order*> orders;
    vector<Card*> cards;

    friend ostream& operator<<(ostream&, const Player&);

public:
    /* Constructors */
    explicit Player(vector<Territory*> territories, vector<Order*> orders, vector<Card*> cards);
    Player(const Player &p);

    /* Destructor */
    ~Player();

    /* Methods */
    vector<Territory*> to_defend();
    vector<Territory*> to_attack();
    void issue_order(Order* order);

    /* Overloaders */
    Player& operator=(const Player &p);
};