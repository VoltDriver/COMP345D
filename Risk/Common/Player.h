#ifndef COMP345RISK_PLAYER_H
#define COMP345RISK_PLAYER_H

#include <vector>
#include "Map.h"
#include "Orders.h"
#include "GameEngine.h"

class Card;
class Hand;

using namespace std;

/**
 * Represents a player. A player hold territories, orders and cards.
 */
class Player {
private:
    vector<Territory*> territories;
    vector<Order*> orders;
    friend ostream& operator<<(ostream&, const Player&);

public:
    string name;
    Hand* hand;

    /* Constructors */
    Player();
    explicit Player(vector<Territory*> territories, vector<Order*> orders, Hand* hand);
    explicit Player(vector<Territory*> territories, vector<Order*> orders, Hand* hand, string name);
    Player(const Player &p);
    /* Destructor */
    ~Player();

    /* Methods */
    vector<Territory*> to_defend();
    vector<Territory*> to_attack();
    void addOrder(Order* order);
    void issueOrder();


    /* Overloaders */
    Player& operator=(const Player &p);

    /* Friend classes */
    friend class GameEngine;
};

#endif //COMP345RISK_PLAYER_H
