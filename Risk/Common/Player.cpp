#include <iostream>
#include "Player.h"

/* Constructors */
Order::Order(string order) {
    this->order = order;
};

Card::Card(string card) {
    this->card = card;
};


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
    // deletes all territory objects stored on heap.
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

/* Accessors & Mutators */
string Order::get_order() const {
    return order;
}

string Card::get_card() const {
    return card;
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
    return strm << "Player("
                << "Territory info: "
//                << (Territory&)player.territories
                << ")";
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