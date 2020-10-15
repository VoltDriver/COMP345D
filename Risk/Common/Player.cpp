#include <iostream>
#include "Player.h"
#include "Cards.h"
#include "Orders.h"

// default constructor
Player::Player() {
    this->territories = vector<Territory*>();
    this->orders = vector<Order*>();
    this->hand = new Hand();
}

// parameterized constructor
Player::Player(vector<Territory*> territories, vector<Order*> orders, Hand* hand) {
    this->territories = territories;
    this->orders = orders;
    this->hand = hand;
}

// copy constructor
Player::Player(const Player &p) {
    this->territories = p.territories;
    this->orders = p.orders;
    this->hand = p.hand;
}


/* Destructor */
Player::~Player() {
    for (Territory *territory: territories) {
        delete territory;
    }
    for (Order *order: orders) {
        delete order;
    }
    delete hand;
}


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
ostream &operator<<(std::ostream &strm, const Player &player) {
    strm << "Player Object Data:\n";
    strm << "Territories \n";
    for (Territory *territory: player.territories) {
        strm << *territory;
    }
    strm << "Orders \n";
    for (Order *order: player.orders) {
        strm << order->description << "\n";
    }
    strm << "Cards \n";
    for (const Card& card: *player.hand->cards) {
        strm << card << "\n";
    }

    return strm;
}

// assignment operator
Player& Player::operator=(const Player& p) {
    for (Territory *territory: territories) {
        delete territory;
    }
    for (Order *order: orders) {
        delete order;
    }
    delete hand;
    this->territories = p.territories;
    this->orders = p.orders;
    this->hand = p.hand;

    return *this;
}