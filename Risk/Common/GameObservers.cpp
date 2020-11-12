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

Subject::~Subject() {
    delete observer_list;
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
PhaseObserver::~PhaseObserver() {
    _gameEngine->remove(this);
}
PhaseObserver::PhaseObserver(GameEngine* gameEngine) {
    _gameEngine = gameEngine;
    _gameEngine->add(this);   // When a PhaseObserver is created, it will be added to the observers list of the subject.
}

void PhaseObserver::Update() {
    display();
}

void PhaseObserver::display() {

    if (_gameEngine->getPhase() == "Reinforcement Phase") {
        cout << "" << endl;
        cout << "-------------------------------------------------------------" << endl;
        cout << "Phase Observer displaying: " << _gameEngine->getPhase() << " " << _gameEngine->getCurrentPlayer()->name <<endl;
        cout << "Number of armies to Deploy: " << _gameEngine->getCurrentPlayer()->getReinforcementPool();
        cout << "\n-------------------------------------------------------------" << endl;
    }

    if (_gameEngine->getPhase() == "Issue Orders Phase") {
        cout << "" << endl;
        cout << "-------------------------------------------------------------" << endl;

        cout << "\n-------------------------------------------------------------" << endl;
    }

    if (_gameEngine->getPhase() == "Execute Orders Phase") {
        cout << "" << endl;
        cout << "-------------------------------------------------------------" << endl;

        cout << "\n-------------------------------------------------------------" << endl;
    }
}


/* StatsObserver Class */
//StatsObserver::StatsObserver() {}
//StatsObserver::~StatsObserver() {
//    _map->remove(this);
//}