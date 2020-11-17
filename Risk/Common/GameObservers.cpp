#include "GameObservers.h"
#include "GameEngine.h"
#include "Player.h"
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


    /* Startup Phase */
    if (phase == "Startup Phase") {
        cout << "" << endl;
        cout << "-------------------------------------------------------------" << endl;
        cout << "Phase Observer displaying: " << phase <<endl;
        cout << "-------------------------------------------------------------" << endl;
    }


    /* Reinforcement Phase */
    if (phase == "Reinforcement Phase") {
        cout << "" << endl;
        cout << "-------------------------------------------------------------" << endl;
        cout << "Phase Observer displaying: " << phase << " " << player_name << endl;
        cout << "Number of armies to Deploy: " << _gameEngine->getCurrentPlayer()->getReinforcementPool();
        cout << "\n-------------------------------------------------------------" << endl;
    }


    /* Issue Orders Phase */
    if (phase == "Issue Orders Phase") {
        cout << "" << endl;
        cout << "-------------------------------------------------------------" << endl;
        cout << "Phase Observer displaying: " << phase << endl;
        cout << "-------------------------------------------------------------" << endl;
    }

    if (phase == "Issue Orders Phase::Player turn") {
        cout << "" << endl;
        cout << "-------------------------------------------------------------" << endl;
        cout << "Phase Observer displaying: " << player_name << " issuing order." << endl;
        cout << "-------------------------------------------------------------" << endl;
    }

    if (phase == "Issue Orders Phase::Turn end") {
        cout << "" << endl;
        cout << "-------------------------------------------------------------" << endl;
        cout << "Phase Observer displaying: " << player_name << " has no more orders to issue." << endl;
        cout << "-------------------------------------------------------------" << endl;
    }


    /* Execute Orders Phase */
    if (phase == "Execute Orders Phase") {
        cout << "" << endl;
        cout << "-------------------------------------------------------------" << endl;
        cout << "Phase Observer displaying: " << phase << endl;
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