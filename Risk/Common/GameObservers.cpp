#include "GameObservers.h"


/* Observer Class */
Observer::Observer(){}
Observer::~Observer(){}


/* Subject Class */
Subject::Subject(){
    observer_list = new list<Observer*>;
}

Subject::~Subject(){
    delete observer_list;
}

void Subject::add(Observer* o){
    observer_list->push_back(o);
}

void Subject::remove(Observer* o){
    observer_list->remove(o);
}

void Subject::notify(){
    list <Observer*>::iterator i = observer_list->begin();
    for (; i != observer_list->end(); ++i)
        (*i)->Update();
}