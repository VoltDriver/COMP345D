#include <iostream>
#include "Player.h"

/* Constructors */
//Player::Player() = default;

Player::Player(vector<Territory*> territories) {
    this->territories = territories;
}

Player::Player(const Player &p) {
    this->territories = p.territories;
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

