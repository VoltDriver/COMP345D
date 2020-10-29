#include <iostream>
#include "Player.h"
#include "Cards.h"
#include "Orders.h"

// default constructor
Player::Player() {
    this->territories = vector<Territory*>();
    this->orders = vector<Order*>();
    this->hand = new Hand();
    this->name = "";
}

// parameterized constructors
Player::Player(vector<Territory*> territories, vector<Order*> orders, Hand* hand) {
    this->territories = territories;
    this->orders = orders;
    this->hand = hand;
    this->name = "";
}

Player::Player(vector<Territory*> territories, vector<Order*> orders, Hand* hand, string name) {
    this->territories = territories;
    this->orders = orders;
    this->hand = hand;
    this->name = name;
}

// copy constructor
Player::Player(const Player &p) {
    this->territories = p.territories;
    this->orders = p.orders;
    this->hand = p.hand;
    this->name = p.name;
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
void Player::addOrder(Order* order) {
    orders.push_back(order);
    cout << "order has been added to list of orders" << endl;
}

void Player::issueOrder() {
    cout << this->name << ", which order would you like to issue?";
    
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