#pragma once

#include <iostream>
#include <list>

using namespace std;

class GameEngine;
class Player;


/**
 * The Observer class is basically an interface or abstract class since it contains at least one pure virtual function.
 * Any observer that is created will have to implement its own Update().
 */
class Observer {
public:
    ~Observer();
    virtual void Update() = 0;
protected:
    Observer();
};


/**
 * Any class that inherits Subject will be a model (Channel). Observers can then be added (subscribe) to a particular
 * channel or be removed. Observers get added to the observer list. And anytime notify is called in the model, then
 * the observers will get new information and be able to display it.
 */
class Subject {
public:
    Subject();
    ~Subject();
    virtual void add(Observer* o);
    virtual void remove(Observer* o);
    virtual void notify();
private:
    list <Observer*> *observer_list;
};


/**
 * The phase observer will be responsible for displaying new information everytime the phase of the game changes and will
 * display the turn of a player. Additional useful information will be displayed depending on the different phases.
 */
class PhaseObserver : Observer {
public:
    PhaseObserver();
    explicit PhaseObserver(GameEngine* gameEngine);
    ~PhaseObserver();
    void Update();
    void display();
private:
    GameEngine* _gameEngine;
};


/**
 *
 */
class StatsObserver : Observer {
public:
    StatsObserver();
    StatsObserver(GameEngine* gameEngine);
    ~StatsObserver();
    void Update();
    void display();
private:
    GameEngine* _gameEngine;
};
