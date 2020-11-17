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
    int armiesToDeploy = _gameEngine->getCurrentPlayer()->getReinforcementPool();

    /* Startup Phase */
    if (phase == "Startup Phase") {
        cout << "\n-------------------------------------------------------------" << endl;
        cout << "\t\t***** STARTUP PHASE *****" << endl;
        cout << "-------------------------------------------------------------" << endl;
    }

    /* Reinforcement Phase */
    if (phase == "Reinforcement Phase") {
        cout << "\n-------------------------------------------------------------" << endl;
        cout << "\t\t***** REINFORCEMENT PHASE *****" << endl;
        cout << "-------------------------------------------------------------" << endl;
    }

    if (phase == "Reinforcement Phase::Deploy") {
        cout << "\n-------------------------------------------------------------" << endl;
        cout << "Reinforcement Phase " << player_name << endl;
        cout << "Number of armies to Deploy: " << armiesToDeploy;
        cout << "\n-------------------------------------------------------------" << endl;
    }


    /* Issue Orders Phase */
    if (phase == "Issue Orders Phase") {
        cout << "\n-------------------------------------------------------------" << endl;
        cout << "\t\t***** ISSUE ORDERS PHASE *****" << endl;
        cout << "-------------------------------------------------------------" << endl;
    }

    if (phase == "Issue Orders Phase::Player turn") {
        cout << "\n-------------------------------------------------------------" << endl;
        cout << player_name << " issuing an order." << endl;
        cout << "-------------------------------------------------------------" << endl;
    }

    if (phase == "Issue Orders Phase::Turn end") {
        cout << "\n-------------------------------------------------------------" << endl;
        cout << player_name << " has no more orders to issue." << endl;
        cout << "-------------------------------------------------------------" << endl;
    }


    /* Execute Orders Phase */
    if (phase == "Execute Orders Phase") {
        cout << "\n-------------------------------------------------------------" << endl;
        cout << "\t\t***** EXECUTE ORDERS PHASE *****" << endl;
        cout << "-------------------------------------------------------------" << endl;
    }

    if (phase == "Execute Orders Phase::Execute") {
        cout << "\n-------------------------------------------------------------" << endl;
        cout << player_name << " is executing an order." << endl;
        cout << "-------------------------------------------------------------" << endl;
    }

    if (phase == "Execute Orders Phase::Done") {
        cout << "\n-------------------------------------------------------------" << endl;
        cout << player_name << " is done executing orders." << endl;
        cout << "-------------------------------------------------------------" << endl;
    }


    /* Game Over Phase */
    if (phase == "Game Over") {
        cout << "\n-------------------------------------------------------------" << endl;
        cout << "\t\t***** GAME OVER *****" << endl;
        cout << player_name << " wins!" << endl;
        cout << "-------------------------------------------------------------" << endl;
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

void StatsObserver::display() {


}