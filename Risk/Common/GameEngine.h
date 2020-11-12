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
#include "GameObservers.h"

class Player;

class Deck;

class Map;


class ContinentOwnership_DataObject {
    private:
        friend ostream& operator<<(ostream&, const ContinentOwnership_DataObject&);
    public:
        Continent *continent;
        int armyBonus;
        int ownedTerritories;

        ContinentOwnership_DataObject();
        ContinentOwnership_DataObject(Continent *, int, int);
        ContinentOwnership_DataObject(const ContinentOwnership_DataObject &c);

        ContinentOwnership_DataObject& operator=(const ContinentOwnership_DataObject &c);
};

class GameEngine: public Subject {
    private:
        list <Player> players;
        Map *map;
        Deck *deck;
        bool phase_observer_flag;
        bool stat_observer_flag;
        friend ostream& operator<<(ostream&, const GameEngine&);

    public:
        void mainGameLoop();

        void issueOrdersPhase();

        // TODO: STUB METHOD. To be implemented.
        void startupPhase();

        void gameStart();

        void reinforcementPhase();

        void executeOrdersPhase();

        GameEngine& operator=(const GameEngine &g);

        GameEngine();
        GameEngine(const GameEngine &g);

//        void add(Observer* o);
};