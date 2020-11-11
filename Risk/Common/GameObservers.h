#pragma once

#include <iostream>
#include <list>

using namespace std;

class Observer;

/**
 *
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
 * The Observer class is basically an interface or abstract class since it contains at least one pure virtual function.
 * Any observer that is created will have to implement its own Update().
 */
class Observer {
public:
    ~Observer();
	virtual void Update() = 0;   // pure virtual function. This forces any subclass to implement Update()
protected:
    Observer();
};



class PhaseDisplay : Observer {

};


class StatsDisplay : Observer {

};
