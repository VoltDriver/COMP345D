#ifndef COMP345RISK_PLAYER_H
#define COMP345RISK_PLAYER_H

#include <vector>
#include "Map.h"
#include "Orders.h"
#include "GameEngine.h"
#include "PlayerStrategies.h"

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
    bool wonFight;
    PlayerStrategy *strategy;
    vector<Territory*> territories;
    OrdersList* orders;
    int reinforcementPool;
    int uncommittedReinforcementPool;
    friend ostream& operator<<(ostream&, const Player&);
    bool conquered;
    vector<Player*> friendlyPlayers;
    int orderOfPlay;
    int numOfConquers;

public:
    string name;
    Hand* hand;

    /* Constructors */
    Player();
    explicit Player(string name);
    explicit Player(vector<Territory*> territories, OrdersList* orders, Hand* hand, int orderOfPlay);
    explicit Player(vector<Territory*> territories, OrdersList* orders, Hand* hand, string name, int orderOfPlay);
    Player(const Player &p);

    /* Destructor */
    ~Player();

    /* Methods */
    bool hasWonFight();
    void setWonFight(bool wonFight);
    void incrementNumOfConquers();
    int getReinforcementPool() const;
    void setReinforcementPool(int newPool);
    int getUncommittedReinforcementPool() const;
    void setUncommittedReinforcementPool(int newPool);
    vector<Territory*> to_defend();
    vector<Territory*> to_attack();
    bool issueOrder(Deck* deck, Map* territoriesMap,const list<Player*> gamePlayers);
    bool issueOrderHuman(Deck* deck, Map* territoriesMap,const list<Player*> gamePlayers);
    void addOrder(Order* order);
    void addFriendlyPlayer(Player* player);
    void addTerritory(Territory* territory);
    void removeTerritory(Territory* territory);
    bool hasConquered();
    void setConquered(bool conquered);
    bool isFriendly(Player* player);
    OrdersList* getOrdersList();
    Hand* getHand();
    int getNumOfConquers();
    vector<Territory*> getTerritories();
    void setStrategy(PlayerStrategy *newStrategy);
    PlayerStrategy* getPlayerStrategy();

    /* Overloaders */
    Player& operator=(const Player &p);
    bool operator< (const Player &other) const;

    /* Friend classes */
    friend class GameEngine;
    friend class Card;
};

#endif //COMP345RISK_PLAYER_H
