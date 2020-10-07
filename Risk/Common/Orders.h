#include <list>
#include <vector>
using namespace std;

#ifndef UNTITLED_ORDERS_H
#define UNTITLED_ORDERS_H


class Orders {
public:
    int id;
    Orders();
    Orders(int id);


    int getID();
    bool validate();
    void execute();


};

class Deploy: public Orders{
public:
    Deploy();

    bool validate();
    void execute();
};

class Advance:public Orders{
public:
    Advance();

    bool validate();
    void execute();
};

class Bomb:public Orders{
public:
    Bomb();

    bool validate();
    void execute();
};

class Blockade:public Orders{
public:
    Blockade();

    bool validate();
    void execute();
};


class Airlift:public Orders{
public:
    Airlift();

    bool validate();
    void execute();
};

class Negotiate:public Orders{
public:
    Negotiate();

    bool validate();
    void execute();
};


class OrdersList{
public:
    OrdersList(vector<Orders> &list);


    int remove(Orders order);
    void move(Orders order, int pos);
    void add(Orders order);

    vector<Orders> *myList;



};


#endif //UNTITLED_ORDERS_H