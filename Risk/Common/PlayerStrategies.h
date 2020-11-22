#pragma once


#include "Map.h"

/**
 * PlayerStrategy is an abstract class. All concrete Strategy classes that inherit this class must
 * provide function definition for issueOrder(), toAttack() and toDefend().
 */
class PlayerStrategy {
public:
    virtual vector<Territory*> to_defend() = 0;
    virtual vector<Territory*> to_attack() = 0;
    virtual bool issueOrder(Deck* deck, Map* territoriesMap,const list<Player*> gamePlayers) = 0;
};


/**
 * The strategy that requires user interaction.
 */
class HumanPlayerStrategy : public PlayerStrategy {
public:
    vector<Territory*> to_defend();
    vector<Territory*> to_attack();
    bool issueOrder(Deck* deck, Map* territoriesMap,const list<Player*> gamePlayers);
};


/**
 * The aggressive strategy focuses on attack orders. All reinforcements will be deployed to the
 * territory with most units and then attack with that army until it cannot attack anymore, then
 * fortifies in order to maximize aggregation of force in one territory.
 */
class AggressivePlayerStrategy : public PlayerStrategy {
public:
    vector<Territory*> to_defend();
    vector<Territory*> to_attack();
    bool issueOrder(Deck* deck, Map* territoriesMap,const list<Player*> gamePlayers);
};


/**
 * The benevolent strategy focuses on reinforcing its weakest territories and makes no attack orders, then
 * fortifies in order to move armies to weaker countries.
 *
 */
class BenevolentPlayerStrategy : public PlayerStrategy {
public:
    vector<Territory*> to_defend();
    vector<Territory*> to_attack();
    bool issueOrder(Deck* deck, Map* territoriesMap,const list<Player*> gamePlayers);
};


/**
 * This strategy will make sure the player never issues any order.
 */
class NeutralPlayerStrategy : public PlayerStrategy {
public:
    vector<Territory*> to_defend();
    vector<Territory*> to_attack();
    bool issueOrder(Deck* deck, Map* territoriesMap,const list<Player*> gamePlayers);
};