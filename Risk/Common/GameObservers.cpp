#include "GameObservers.h"
#include "GameEngine.h"
#include <iostream>
#include <string>


/* Observer Class */
// default constructor
Observer::Observer() {}

// destructor
Observer::~Observer() {}



/* Subject Class */
// default constructor
Subject::Subject() {
    observer_list = new list<Observer*>;
}

// copy constructor
Subject::Subject(const Subject &subject) {
    for (int i = 0; i < subject.observer_list->size(); i++) {
        this->observer_list[i] = subject.observer_list[i];
    }
}

// destructor
Subject::~Subject() {
    delete observer_list;
}

// assignment operator
Subject& Subject::operator=(const Subject& s) {
    for (Observer* observer: *observer_list) {
        delete observer;
    }
    this->observer_list = s.observer_list;

    return *this;
}

// stream insertion operator
ostream &operator<<(std::ostream& strm, const Subject &subject) {
    return strm << "Subject insertion stream operator" << endl;
}

void Subject::add(Observer* o) {
    observer_list->push_back(o);
}

void Subject::remove(Observer* o) {
    observer_list->remove(o);
}

void Subject::notify() {
    list <Observer*>::iterator i = observer_list->begin();
    for (; i != observer_list->end(); ++i)
        (*i)->Update();
}



/* PhaseObserver Class */
// default constructor
PhaseObserver::PhaseObserver() {}

// parameterized constructor
PhaseObserver::PhaseObserver(GameEngine* gameEngine) {
    _gameEngine = gameEngine;
    _gameEngine->add(this);   // When a PhaseObserver is created, it will be added to the observers list of the subject.
}

// copy constructor
PhaseObserver::PhaseObserver(const PhaseObserver *phaseObserver) {
    this->_gameEngine = phaseObserver->_gameEngine;
}

// destructor
PhaseObserver::~PhaseObserver() {
    _gameEngine->remove(this);
}

// assignment operator
PhaseObserver& PhaseObserver::operator=(const PhaseObserver& p) {
    this->_gameEngine = p._gameEngine;
    return *this;
}

ostream &operator<<(std::ostream& strm, const PhaseObserver &phaseObserver) {
    return strm << "PhaseObserver insertion stream operator" << endl;
}

void PhaseObserver::Update() {
    display();
}

/**
 * Displays information of the different phases of the game.
 */
void PhaseObserver::display() {
    string phase = _gameEngine->getPhase();
    string player_name = _gameEngine->getCurrentPlayer()->name;

    /* Startup Phase */
    if (phase == "Startup Phase") {
        cout << "\n--------------------------------------------------------------------------------------------" << endl;
        cout << "\t\t\t***** STARTUP PHASE *****" << endl;
        cout << "--------------------------------------------------------------------------------------------" << endl;
    }


    /* New Turn Phase */
    if (phase == "New Turn") {
        int turnCounter = _gameEngine->getTurnCounter();
        cout << "\n--------------------------------------------------------------------------------------------" << endl;
        cout << "\t\t\t\t***** TURN " << turnCounter << " *****" << endl;
        cout << "--------------------------------------------------------------------------------------------" << endl;
    }


    /* Reinforcement Phase */
    if (phase == "Reinforcement Phase") {
        cout << "\n--------------------------------------------------------------------------------------------" << endl;
        cout << "\t\t\t***** REINFORCEMENT PHASE *****" << endl;
        cout << "--------------------------------------------------------------------------------------------" << endl;
    }

    if (phase == "Reinforcement Phase::Deploy") {
        int armiesToDeploy = _gameEngine->getCurrentPlayer()->getReinforcementPool();
        cout << "\n--------------------------------------------------------------------------------------------" << endl;
        cout << "-" << player_name << " Reinforcement Phase-" << endl;
        cout << "Number of armies to Deploy: " << armiesToDeploy;
        cout << "\n--------------------------------------------------------------------------------------------" << endl;
    }


    /* Issue Orders Phase */
    if (phase == "Issue Orders Phase") {
        cout << "\n--------------------------------------------------------------------------------------------" << endl;
        cout << "\t\t\t***** ISSUE ORDERS PHASE *****" << endl;
        cout << "--------------------------------------------------------------------------------------------" << endl;
    }

    if (phase == "Issue Orders Phase::Pre-issuance") {
        vector<Territory*> terrToDef = _gameEngine->getCurrentPlayer()->to_defend();
        vector<Territory*> terrToAtk = _gameEngine->getCurrentPlayer()->to_attack();
        int armiesToDeploy = _gameEngine->getCurrentPlayer()->getUncommittedReinforcementPool();

        cout << "\n--------------------------------------------------------------------------------------------" << endl;
        cout << "-" << player_name << " Pre-Issue Order Phase-\n" << endl;

        cout << "Armies left to deploy: " << armiesToDeploy << "\n" << endl;
        cout << "Territories owned: " << endl;
        for (int i = 0; i < terrToDef.size(); i++) {
            cout << *terrToDef[i];
        }
        cout << "\nEnemy Territories: " << endl;
        for (int i = 0; i < terrToAtk.size(); i++) {
            cout << *terrToAtk[i];
        }
        cout << "--------------------------------------------------------------------------------------------\n" << endl;
    }

    if (phase == "Issue Orders Phase::Post-issuance") {
        string order = _gameEngine->getCurrentPlayer()->getOrdersList()->myList.back()->getDescription();

        cout << "\n--------------------------------------------------------------------------------------------" << endl;
        cout << "-" << player_name << " Post-Issue Order Phase-\n" << endl;

        cout << player_name << " issued " << order << " order\n" <<endl;
        cout << "Current list of orders issued: " << endl;
        for (Order* order : _gameEngine->getCurrentPlayer()->getOrdersList()->myList) {
            cout << "-" << order->getDescription() << endl;
        }

        cout << "--------------------------------------------------------------------------------------------\n" << endl;
    }

    if (phase == "Issue Orders Phase::Turn end") {
        cout << "--------------------------------------------------------------------------------------------" << endl;
        cout << player_name << " has no more orders to issue." << endl;
        cout << "--------------------------------------------------------------------------------------------" << endl;
    }


    /* Execute Orders Phase */
    if (phase == "Execute Orders Phase") {
        cout << "\n--------------------------------------------------------------------------------------------" << endl;
        cout << "\t\t\t***** EXECUTE ORDERS PHASE *****" << endl;
        cout << "--------------------------------------------------------------------------------------------" << endl;
    }

    if (phase == "Execute Orders Phase::Execute") {
        string order = _gameEngine->getCurrentPlayer()->getOrdersList()->myList[0]->getDescription();

        cout << "\n--------------------------------------------------------------------------------------------" << endl;
        cout << "-" << player_name << " Execute Order Phase-\n" << endl;
        cout << "Remaining orders to execute: " << endl;
        for (Order* order : _gameEngine->getCurrentPlayer()->getOrdersList()->myList) {
            cout << "-" << order->getDescription() << endl;
        }
        cout << "\nNow executing " << order << " order" << endl;
        cout << "--------------------------------------------------------------------------------------------\n" << endl;
    }

    if (phase == "Execute Orders Phase::Done") {
        cout << "\n--------------------------------------------------------------------------------------------" << endl;
        cout << player_name << " is done executing orders." << endl;
        cout << "--------------------------------------------------------------------------------------------" << endl;
    }

}



/* StatsObserver Class */
// default constructor
StatsObserver::StatsObserver() {}

// parameterized constructor
StatsObserver::StatsObserver(GameEngine* gameEngine) {
    _gameEngine = gameEngine;
    _gameEngine->add(this);
}

// copy constructor
StatsObserver::StatsObserver(const StatsObserver *statsObserver) {
    this->_gameEngine = statsObserver->_gameEngine;
}

// destructor
StatsObserver::~StatsObserver() {
    _gameEngine->remove(this);
}

// assignment operator
StatsObserver& StatsObserver::operator=(const StatsObserver& s) {
    this->_gameEngine = s._gameEngine;
    return *this;
}

// stream insertion operator
ostream &operator<<(std::ostream& strm, const StatsObserver &statsObserver) {
    return strm << "StatsObserver insertion stream operator" << endl;
}

void StatsObserver::Update() {
    display();
}

void StatsObserver::displayWorldDomination(GameEngine* _gameEngine) {
    float totalTerritories = _gameEngine->getMap()->get_territories().size();

    cout << "Player Stats" << endl;

    for (Player* player : _gameEngine->getPlayers()) {
        float percentageOwned = (player->to_defend().size()/totalTerritories)*100;

        cout << player->name << ": owns " << player->to_defend().size() << " territories of " << totalTerritories << " | "
            << "Conquered: " << player->getNumOfConquers() << " | "
            << "World domination progress: " << percentageOwned << "% [";

        int progressBars = percentageOwned/10;
        for (int i = 0; i < 10; i++) {
            if (i < progressBars) cout << "#";
            else cout << "-";
        }
        cout << "]" << endl;

    }
}

/**
 * Displays world domination map when player gets conquered, player gets eliminated and when the game is over.
 */
void StatsObserver::display() {
    string phase = _gameEngine->getPhase();
    string player_name = _gameEngine->getCurrentPlayer()->name;

    /* Player was Conquered */
    if (phase == "Conquered") {
        cout << "********************************************************************************************" << endl;
        cout << player_name << " has won the battle!\n" << endl;
        displayWorldDomination(_gameEngine);
        cout << "********************************************************************************************" << endl;
    }

    /* A Player was Eliminated */
    if (phase == "Eliminated") {
        cout << "\n********************************************************************************************" << endl;
        cout << player_name << " has been eliminated!\n" << endl;
        displayWorldDomination(_gameEngine);
        cout << "********************************************************************************************\n" << endl;
    }

    /* A Player has won */
    if (phase == "Game Over") {
        cout << "\n********************************************************************************************" << endl;
        cout << "\t\t\t***** GAME OVER *****" << endl;
        cout << "\t\t\t    " << player_name << " wins!\n" << endl;
        displayWorldDomination(_gameEngine);
        cout << "********************************************************************************************\n" << endl;
    }

}

