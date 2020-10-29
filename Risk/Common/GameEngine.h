#ifndef COMP345RISK_GAMEENGINE_H
#define COMP345RISK_GAMEENGINE_H
#include <list>
#include <array>
#include <map>
#include <iostream>
#include "Player.h"
#include "Orders.h"
#include "Map.h"

class ContinentOwnership_DataObject {
    public:
        Continent* continent;
        int armyBonus;
        int ownedTerritories;

        ContinentOwnership_DataObject();
        ContinentOwnership_DataObject(Continent*, int, int);
};

class GameEngine {
    private:
        list<Player> players;
        Map map;
    public:
    // TODO: STUB METHOD. To be implemented.
        void mainGameLoop();
    // TODO: STUB METHOD. To be implemented.
        void startupPhase();
    // TODO: STUB METHOD. To be implemented.
        void gameStart();
    // TODO: STUB METHOD. To be implemented.
        void reinforcementPhase();
    // TODO: STUB METHOD. To be implemented.
        void issueOrdersPhase();
    // TODO: STUB METHOD. To be implemented.
        void executeOrdersPhase();

        Order queryOrderFromUser();
};


#endif //COMP345RISK_GAMEENGINE_H
