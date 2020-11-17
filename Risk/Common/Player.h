#ifndef COMP345RISK_PLAYER_H
#define COMP345RISK_PLAYER_H

#include <vector>
#include "Map.h"
#include "Orders.h"
#include "GameEngine.h"

class Card;
class Hand;
class Order;
class Deck;
class OrdersList;

using namespace std;

/**
 * Represents a player. A player hold territories, orders and cards.
 */
class Player {
private:
    vector<Territory*> territories;
    OrdersList* orders;
    int reinforcementPool;
    int uncommittedReinforcementPool;
    friend ostream& operator<<(ostream&, const Player&);
    bool conquered;
    vector<Player*> friendlyPlayers;
    int orderOfPlay;

public:
    string name;
    Hand* hand;

    /* Constructors */
    Player();
    Player(string name);
    explicit Player(vector<Territory*> territories, OrdersList* orders, Hand* hand, int orderOfPlay);
    explicit Player(vector<Territory*> territories, OrdersList* orders, Hand* hand, string name, int orderOfPlay);
    Player(const Player &p);

    /* Destructor */
    ~Player();

    /* Methods */
    int getReinforcementPool() const;
    void setReinforcementPool(int newPool);
    int getUncommittedReinforcementPool() const;
    void setUncommittedReinforcementPool(int newPool);
    vector<Territory*> to_defend();
    vector<Territory*> to_attack();
    void addOrder(Order* order);
    bool issueOrder(Deck* deck, Map* territoriesMap, list<Player> gamePlayers);
    bool issueOrderHuman(Deck* deck, Map* territoriesMap, list<Player> gamePlayers);
    bool operator< (const Player &other) const;
    void addTerritory(Territory* territory);
    void removeTerritory(Territory* territory);
    OrdersList* getOrdersList();

    /* Overloaders */
    Player& operator=(const Player &p);

    /* Friend classes */
    friend class GameEngine;
    friend class Card;
};

#endif //COMP345RISK_PLAYER_H
