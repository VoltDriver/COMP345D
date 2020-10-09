#include <iostream>
#include "Player.h"

/* Constructors */
Order::Order(string order) {
    this->order = order;
}

Card::Card(string card) {
    this->card = card;
}

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


/* Destructor */
Player::~Player() {
    for (Territory *territory: territories) {
        delete territory;
    }
    for (Order *order: orders) {
        delete order;
    }
    for (Card *card: cards) {
        delete card;
    }
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
        strm << order->order << "\n";
    }
    strm << "Cards \n";
    for (Card *card: player.cards) {
        strm << card->card << "\n";
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
    for (Card *card: cards) {
        delete card;
    }
    this->territories = p.territories;
    this->orders = p.orders;
    this->cards = p.cards;

    return *this;
}