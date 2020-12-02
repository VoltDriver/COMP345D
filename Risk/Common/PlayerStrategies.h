#pragma once

#include "Map.h"
#include "Cards.h"

class Player;

/**
 * PlayerStrategy is an abstract class. All concrete Strategy classes that inherit this class must
 * provide function definition for issueOrder(), toAttack() and toDefend().
 */
class PlayerStrategy {
private:
    string strategy_name;
public:
    PlayerStrategy();
    virtual ~PlayerStrategy();

    virtual vector<Territory*> to_defend(Player *player) = 0;
    virtual vector<Territory*> to_attack(Player *player) = 0;
    virtual bool issueOrder(Player *player, Deck* deck, Map* territoriesMap, const list<Player*> gamePlayers) = 0;

    void setStrategyName(string name);
    string getStrategyName();
};


/**
 * Default Strategy (the original AI from A2)
 */
class DefaultPlayerStrategy : public PlayerStrategy {
public:
    DefaultPlayerStrategy();
    ~DefaultPlayerStrategy();

    vector<Territory*> to_defend(Player *player);
    vector<Territory*> to_attack(Player *player);
    bool issueOrder(Player *player, Deck* deck, Map* territoriesMap,const list<Player*> gamePlayers);
};


/**
 * The strategy that requires user interaction.
 */
class HumanPlayerStrategy : public PlayerStrategy {
public:
    HumanPlayerStrategy();
    ~HumanPlayerStrategy();

    vector<Territory*> to_defend(Player *player);
    vector<Territory*> to_attack(Player *player);
    bool issueOrder(Player *player, Deck* deck, Map* territoriesMap,const list<Player*> gamePlayers);
};


/**
 * The aggressive strategy focuses on attack orders. All reinforcements will be deployed to the
 * territory with most units and then attack with that army until it cannot attack anymore, then
 * fortifies in order to maximize aggregation of force in one territory.
 */
class AggressivePlayerStrategy : public PlayerStrategy {
protected:
    Territory* strongestTerritory;
    bool advanceAllowed;
public:
    AggressivePlayerStrategy();
    ~AggressivePlayerStrategy();

    Territory* getStrongestTerritory();
    void setStrongestTerritory(Player* player);
    vector<Territory*> to_defend(Player *player);
    vector<Territory*> to_attack(Player *player);
    bool issueOrder(Player *player, Deck* deck, Map* territoriesMap,const list<Player*> gamePlayers);
};


/**
 * The benevolent strategy focuses on reinforcing its weakest territories and makes no attack orders, then
 * fortifies in order to move armies to weaker countries.
 *
 */
class BenevolentPlayerStrategy : public PlayerStrategy {
protected:
    Territory* weakestTerritory;
    vector<Territory*> weakestTerritories;
public:
    BenevolentPlayerStrategy();
    ~BenevolentPlayerStrategy();

    vector<Territory*> getWeakestTerritories(Player* player);
    Territory* getWeakestTerritory();
    vector<Territory*> to_defend(Player *player);
    vector<Territory*> to_attack(Player *player);
    bool issueOrder(Player *player, Deck* deck, Map* territoriesMap,const list<Player*> gamePlayers);
};


/**
 * This strategy will make sure the player never issues any order.
 */
class NeutralPlayerStrategy : public PlayerStrategy {
public:
    NeutralPlayerStrategy();
    ~NeutralPlayerStrategy();

    vector<Territory*> to_defend(Player *player);
    vector<Territory*> to_attack(Player *player);
    bool issueOrder(Player *player, Deck* deck, Map* territoriesMap,const list<Player*> gamePlayers);
};