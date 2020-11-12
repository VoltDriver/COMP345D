#pragma once

#include <vector>
#include <list>
#include <array>
#include <map>
#include <string>
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
        Player *currentPlayer;
        Map *map;
        Deck *deck;
        string phase;
        bool phase_observer_flag;
        bool stat_observer_flag;
        friend ostream& operator<<(ostream&, const GameEngine&);

    public:
        void mainGameLoop();
        void issueOrdersPhase();
        // TODO: STUB METHOD. To be implemented.
        void startupPhase();
        void gameStart(bool verbose = false);
        void reinforcementPhase();
        void executeOrdersPhase();

        GameEngine& operator=(const GameEngine &g);
        GameEngine();
        ~GameEngine();
        GameEngine(const GameEngine &g);


        bool getPhase_observer_flag();

        bool getStat_observer_flag();

        Player* getCurrentPlayer();

        string getPhase();

};