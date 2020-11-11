#pragma once

#include <iostream>
#include <list>

using namespace std;


/**
 * The Observer class is basically an interface or abstract class since it contains at least one pure virtual function.
 * Any observer that is created will have to implement its own Update().
 */
class Observer {
public:
	virtual void Update() = 0;   // pure virtual function. This forces any subclass to implement Update()
    ~Observer();
protected:
    Observer();
};


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

