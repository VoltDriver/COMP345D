#pragma once
#include <list>
#include <vector>
#include <string>
#include "Player.h"
#include "Map.h"

using namespace std;
class Player;
class Territory;

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

    virtual Order* clone() const;
    int getID();
    virtual bool validate();
    virtual void execute();


};

//Deploy class extends Order class
class Deploy: public Order{
    int armies;
    Territory* target;
    Player* player;
public:
    Deploy(int anID, int armies, Territory* target, Player* player);
    Deploy(const Deploy &deploy2);
    Deploy& operator=(const Deploy& other);

    Deploy* clone() const;
    bool validate();
    void execute();
};

//Advance class extends Order class
class Advance:public Order{
public:
    Advance(int anID);
    Advance(const Advance &advance2);
    Advance& operator=(const Advance& other);

    Advance* clone() const;
    bool validate();
    void execute();
};

//Bomb class extends Order class
class Bomb:public Order{
    Territory* target;
    Player* player;
public:
    Bomb(int anID, Territory* target, Player* player);
    Bomb(const Bomb &bomb2);
    Bomb& operator=(const Bomb& other);

    Bomb* clone() const;
    bool validate();
    void execute();
};

//Blockade class extends Order class
class Blockade:public Order{
private:
    Territory* target;
    Player* player;
public:
    Blockade(int anID, Territory* target, Player* player);
    Blockade(const Blockade &blockade2);
    Blockade& operator=(const Blockade& other);

    Blockade* clone() const;
    bool validate();
    void execute();
};

//Airlift class extends Order class
class Airlift:public Order{
    int armies;
    Territory* source;
    Territory* target;
    Player* player;
public:
    Airlift(int anID, int armies, Territory* source, Territory* target, Player* player);
    Airlift(const Airlift &airlift2);
    Airlift& operator=(const Airlift& other);

    Airlift* clone() const;;
    bool validate();
    void execute();
};

//Negotiate class extends Order class
class Negotiate:public Order{
public:
    Negotiate(int anID);
    Negotiate(const Negotiate &negotiate2);
    Negotiate& operator=(const Negotiate& other);

    Negotiate* clone() const;
    bool validate();
    void execute();
};

//Orderslist class
class OrdersList{
public:
    OrdersList();
    OrdersList(const OrdersList &orderList2);
    OrdersList& operator=(const OrdersList& other);
    friend ostream& operator<<(ostream&, const OrdersList&);
    ~OrdersList();

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