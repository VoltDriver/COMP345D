#include <list>
#include <vector>
using namespace std;

#ifndef UNTITLED_ORDERS_H
#define UNTITLED_ORDERS_H


class Orders {
public:
    Orders();

    int id;
    bool validate();
    void execute();


};

class Deploy: public Orders{
public:
    Deploy();

};

class Advance:public Orders{
public:
    Advance();
};

class Bomb:public Orders{
public:
    Bomb();
};

class Blockade:public Orders{
public:
    Blockade();
};


class Airlift:public Orders{
public:
    Airlift();
};

class Negotiate:public Orders{
public:
    Negotiate();
};


class OrdersList{
public:
    OrdersList(vector<Orders> &list);
    int id;

    void remove(Orders order);
    void move(Orders order);
    void add(Orders order);

    vector<Orders> *myList;



};


#endif //UNTITLED_ORDERS_H