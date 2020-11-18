#include "GameObservers.h"
#include "GameEngine.h"
#include <iostream>
#include <string>


/* Observer Class */
Observer::Observer() {}
Observer::~Observer() {}



/* Subject Class */
Subject::Subject() {
    observer_list = new list<Observer*>;
}

Subject::Subject(const Subject &subject) {
    for (int i = 0; i < subject.observer_list->size(); i++) {
        this->observer_list[i] = subject.observer_list[i];
    }
}

Subject::~Subject() {
    delete observer_list;
}

Subject& Subject::operator=(const Subject& s) {
    for (Observer* observer: *observer_list) {
        delete observer;
    }
    this->observer_list = s.observer_list;

    return *this;
}

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
PhaseObserver::PhaseObserver() {}

PhaseObserver::PhaseObserver(GameEngine* gameEngine) {
    _gameEngine = gameEngine;
    _gameEngine->add(this);   // When a PhaseObserver is created, it will be added to the observers list of the subject.
}

PhaseObserver::PhaseObserver(const PhaseObserver *phaseObserver) {
    this->_gameEngine = phaseObserver->_gameEngine;
}

PhaseObserver::~PhaseObserver() {
    _gameEngine->remove(this);
}

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

void PhaseObserver::display() {
    string phase = _gameEngine->getPhase();
    string player_name = _gameEngine->getCurrentPlayer()->name;
    int turnCounter = _gameEngine->getTurnCounter();

    /* Startup Phase */
    if (phase == "Startup Phase") {
        cout << "\n--------------------------------------------------------------------------------------------" << endl;
        cout << "\t\t\t***** STARTUP PHASE *****" << endl;
        cout << "--------------------------------------------------------------------------------------------" << endl;
    }


    /* New Turn Phase */
    if (phase == "New Turn") {
        cout << "\n--------------------------------------------------------------------------------------------" << endl;
        cout << "\t\t\t***** TURN " << turnCounter << " *****" << endl;
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

    if (phase == "Issue Orders Phase::Player turn") {
        vector<Territory*> terrToDef = _gameEngine->getCurrentPlayer()->to_defend();
        vector<Territory*> terrToAtk = _gameEngine->getCurrentPlayer()->to_attack();
        int armiesToDeploy = _gameEngine->getCurrentPlayer()->getUncommittedReinforcementPool();

        cout << "\n--------------------------------------------------------------------------------------------" << endl;
        cout << "-" << player_name << " Issue Order Phase-\n" << endl;

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
        int remainingOrders = _gameEngine->getCurrentPlayer()->getOrdersList()->myList.size();

        cout << "\n--------------------------------------------------------------------------------------------" << endl;
        cout << "-" << player_name << " Execute Order Phase-" << endl;
        cout << "Remaining orders to execute: " << remainingOrders << endl;
        cout << "Executing order..." << endl;
        cout << "--------------------------------------------------------------------------------------------\n" << endl;
    }

    if (phase == "Execute Orders Phase::Done") {
        cout << "\n--------------------------------------------------------------------------------------------" << endl;
        cout << player_name << " is done executing orders." << endl;
        cout << "--------------------------------------------------------------------------------------------" << endl;
    }

}



/* StatsObserver Class */
StatsObserver::StatsObserver() {}

StatsObserver::StatsObserver(GameEngine* gameEngine) {
    _gameEngine = gameEngine;
    _gameEngine->add(this);
}

StatsObserver::StatsObserver(const StatsObserver *statsObserver) {
    this->_gameEngine = statsObserver->_gameEngine;
}

StatsObserver::~StatsObserver() {
    _gameEngine->remove(this);
}

StatsObserver& StatsObserver::operator=(const StatsObserver& s) {
    this->_gameEngine = s._gameEngine;
    return *this;
}

ostream &operator<<(std::ostream& strm, const StatsObserver &statsObserver) {
    return strm << "StatsObserver insertion stream operator" << endl;
}

void StatsObserver::Update() {
    display();
}

void displayWorldDomination(GameEngine* _gameEngine, float totalTerritories) {
    for (Player* player : _gameEngine->getPlayers()) {
        cout << player->name << ": owns " << player->to_defend().size() << " territories | " << (player->to_defend().size()/totalTerritories)*100
            << "% world domination" << endl;
    }
}

void StatsObserver::display() {
    string phase = _gameEngine->getPhase();
    string player_name = _gameEngine->getCurrentPlayer()->name;
    int totalTerritories = _gameEngine->getMap()->get_territories().size();

    /* Player was Conquered */
    if (phase == "Conquered") {
        cout << "********************************************************************************************" << endl;
        cout << player_name << " has won the battle!\n" << endl;
        displayWorldDomination(_gameEngine, totalTerritories);
        cout << "********************************************************************************************" << endl;
    }

    /* A Player was Eliminated */
    if (phase == "Eliminated") {
        cout << "\n********************************************************************************************" << endl;
        cout << player_name << " has been eliminated!\n" << endl;
        displayWorldDomination(_gameEngine, totalTerritories);
        cout << "********************************************************************************************\n" << endl;
    }

    /* A Player has won */
    if (phase == "Game Over") {
        cout << "\n********************************************************************************************" << endl;
        cout << "\t\t\t***** GAME OVER *****" << endl;
        cout << player_name << " wins!\n" << endl;
        displayWorldDomination(_gameEngine, totalTerritories);
        cout << "********************************************************************************************\n" << endl;
    }


//    std::list <Player*>::iterator it;

//    for (it = _gameEngine->getPlayers().begin(); it != _gameEngine->getPlayers().end(); ++it){
//        cout << (*it)->to_defend().size();
//    }
//    for (Player* player : _gameEngine->getPlayers()) {
//        cout << player->to_defend().size() << endl;
//    }


}

