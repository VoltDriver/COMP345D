#ifndef COMP345RISK_PLAYER_H
#define COMP345RISK_PLAYER_H

#include <vector>
#include "Map.h"
#include "Orders.h"
#include "GameEngine.h"

class Card;
class Hand;
class Order;

using namespace std;

/**
 * Represents a player. A player hold territories, orders and cards.
 */
class Player {
private:
    vector<Territory*> territories;
    vector<Order*> orders;
    int reinforcementPool;
    friend ostream& operator<<(ostream&, const Player&);
    bool conquered;
    vector<Player*> friendlyPlayers;
    int orderOfPlay;

public:
    string name;
    Hand* hand;

    /* Constructors */
    Player();
    explicit Player(vector<Territory*> territories, vector<Order*> orders, Hand* hand, int orderOfPlay);
    explicit Player(vector<Territory*> territories, vector<Order*> orders, Hand* hand, string name, int orderOfPlay);
    Player(const Player &p);
    /* Destructor */
    ~Player();

    /* Methods */
    int getReinforcementPool();
    void setReinforcementPool(int reinforcementPool);
    vector<Territory*> to_defend();
    vector<Territory*> to_attack();
    void addOrder(Order* order);
    void addTerritory(Territory* territory);
    void removeTerritory(Territory* territory);
    bool issueOrder(Deck* deck);


    /* Overloaders */
    Player& operator=(const Player &p);

    /* Friend classes */
    friend class GameEngine;
    friend class Card;
};

#endif //COMP345RISK_PLAYER_H
