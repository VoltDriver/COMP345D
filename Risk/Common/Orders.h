#include <list>
#include <vector>
using namespace std;

#ifndef UNTITLED_ORDERS_H
#define UNTITLED_ORDERS_H


class Order {

public:
    int id;
    Order(int anID);


    int getID();
    virtual bool validate();
    virtual void execute();


};

class Deploy: public Order{
public:
    Deploy(int anID);

    bool validate();
    void execute();
};

class Advance:public Order{
public:
    Advance(int anID);

    bool validate();
    void execute();
};

class Bomb:public Order{
public:
    Bomb(int anID);

    bool validate();
    void execute();
};

class Blockade:public Order{
public:
    Blockade(int anID);

    bool validate();
    void execute();
};


class Airlift:public Order{
public:
    Airlift(int anID);

    bool validate();
    void execute();
};

class Negotiate:public Order{
public:
    Negotiate(int anID);

    bool validate();
    void execute();
};


class OrdersList{
public:
    OrdersList();
    OrdersList(vector<Order*> list);


    int remove(Order *order);
    void move(Order *order, int pos);
    void add(Order *order);

    vector<Order*> myList;



};

class ID{
private:
    static int currentID;
public:
    int getID();
    ID();
};


#endif //UNTITLED_ORDERS_H