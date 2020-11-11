#pragma once

#include <vector>
#include <list>
#include <array>
#include <map>
#include <iostream>
#include "Player.h"
#include "Orders.h"
#include "Map.h"
#include "Cards.h"

class Player;

class Deck;

class Map;

class ContinentOwnership_DataObject {
public:
    Continent *continent;
    int armyBonus;
    int ownedTerritories;

    ContinentOwnership_DataObject();

    ContinentOwnership_DataObject(Continent *, int, int);
};

class GameEngine {
private:
    list <Player> players;
    Map *map;
    Deck *deck;
    bool phase_observer_flag;
    bool stat_observer_flag;

public:
    void mainGameLoop();

    // TODO: STUB METHOD. To be implemented.
    void issueOrdersPhase();

    // TODO: STUB METHOD. To be implemented.
    void startupPhase();

    // TODO: STUB METHOD. To be implemented.
    void gameStart();

    // TODO: STUB METHOD. To be implemented.
    void reinforcementPhase();

    // TODO: STUB METHOD. To be implemented.
    void executeOrdersPhase();
};