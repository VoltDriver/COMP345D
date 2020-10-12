#include <list>
#include <vector>
#include <string>
using namespace std;

#ifndef UNTITLED_ORDERS_H
#define UNTITLED_ORDERS_H

//Order class
class Order {

public:
    int id;
    string description;
    Order(int anID);
    Order(const Order &order2);
    Order& operator=(const Order& other);
    friend ostream& operator<<(ostream&, const Order&);


    int getID();
    virtual bool validate();
    virtual void execute();


};

//Deploy class extends Order class
class Deploy: public Order{
public:
    Deploy(int anID);
    Deploy(const Deploy &deploy2);
    Deploy& operator=(const Deploy& other);


    bool validate();
    void execute();
};

//Advance class extends Order class
class Advance:public Order{
public:
    Advance(int anID);
    Advance(const Advance &advance2);
    Advance& operator=(const Advance& other);


    bool validate();
    void execute();
};

//Bomb class extends Order class
class Bomb:public Order{
public:
    Bomb(int anID);
    Bomb(const Bomb &bomb2);
    Bomb& operator=(const Bomb& other);


    bool validate();
    void execute();
};

//Blockade class extends Order class
class Blockade:public Order{
public:
    Blockade(int anID);
    Blockade(const Blockade &blockade2);
    Blockade& operator=(const Blockade& other);


    bool validate();
    void execute();
};

//Airlift class extends Order class
class Airlift:public Order{
public:
    Airlift(int anID);
    Airlift(const Airlift &airlift2);
    Airlift& operator=(const Airlift& other);


    bool validate();
    void execute();
};

//Negotiate class extends Order class
class Negotiate:public Order{
public:
    Negotiate(int anID);
    Negotiate(const Negotiate &negotiate2);
    Negotiate& operator=(const Negotiate& other);

    bool validate();
    void execute();
};

//Orderslist class
class OrdersList{
public:
    OrdersList();
    OrdersList(const OrdersList &orderList2);
    OrdersList& operator=(const OrdersList& other);

    int remove(Order *order);
    void move(Order *order, int pos);
    void add(Order *order);

    vector<Order*> myList;



};

//ID class
class ID{
private:
    static int currentID;
public:
    int setID();
    ID();
};


#endif //UNTITLED_ORDERS_H