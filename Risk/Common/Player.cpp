#include "Player.h"


/* Constructors */
Player::Player() = default;

/* Accessors & Mutators */


/* Methods */
void Player::issue_order(Order* order) {
    orders.push_back(order);
}

vector<Country *> Player::to_defend() {
    return countries_toDefend;
}

vector<Country *> Player::to_attack() {
    return countries_toAttack;
}



/* Overloaders */
