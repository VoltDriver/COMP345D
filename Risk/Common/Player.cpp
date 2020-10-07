#include <iostream>
#include "Player.h"

/* Constructors */
//Player::Player() = default;

Player::Player(vector<Country*> countries) {
    this->countries = countries;
}

Player::Player(const Player &p) {
    this->countries = p.countries;
}

/* Accessors & Mutators */


/* Methods */
void Player::issue_order(Order* order) {
    orders.push_back(order);
    cout << "order has been added to list of orders" << endl;
}

vector<Country *> Player::to_defend() {
    return countries;
}

vector<Country *> Player::to_attack() {
    return countries;
}



/* Overloaders */

