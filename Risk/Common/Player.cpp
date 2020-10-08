#include <iostream>
#include "Player.h"

/* Constructors */
Order::Order() = default;
Card::Card() = default;

// parameterized constructor
Player::Player(vector<Territory*> territories, vector<Order*> orders, vector<Card*> cards) {
    this->territories = territories;
    this->orders = orders;
    this->cards = cards;
}

// copy constructor
Player::Player(const Player &p) {
    this->territories = p.territories;
    this->orders = p.orders;
    this->cards = p.cards;
}

/* Accessors & Mutators */


/* Methods */
void Player::issue_order(Order* order) {
    orders.push_back(order);
    cout << "order has been added to list of orders" << endl;
}

vector<Territory *> Player::to_defend() {
    return territories;
}

vector<Territory *> Player::to_attack() {
    return territories;
}



/* Overloaders */
//stream insertion operator

// assignment operator
Player& Player::operator=(const Player& p) {
    for (Territory *territory: territories) {
        delete territory;
    }
    for (Order *order: orders) {
        delete order;
    }
    for (Card *card: cards) {
        delete card;
    }
    this->territories = p.territories;
    this->orders = p.orders;
    this->cards = p.cards;

    return *this;
}