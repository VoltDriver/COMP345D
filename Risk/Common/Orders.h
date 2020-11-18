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
private:
    int id;
protected:
    int priority;
    string description;
public:
    Order(int anID);
    Order(const Order &order2);
    Order& operator=(const Order& other);
    friend ostream& operator<<(ostream&, const Order&);
    virtual ~Order();

    friend bool compare(Order* order, Order* other);
    int getPriority();
    virtual Order* clone() const = 0;
    string getDescription();
    int getID();
    virtual bool validate() = 0;
    virtual void execute() = 0;
};

//Deploy class extends Order class
class Deploy: public Order{
private:
    int armies;
    Territory* target;
    Player* player;
public:

    Deploy(int anID, int armies, Territory* target, Player* player);
    Deploy(const Deploy &deploy2);
    Deploy& operator=(const Deploy& other);
    ~Deploy();


    Deploy* clone() const;
    bool validate();
    void execute();
};

//Advance class extends Order class
class Advance:public Order{
private:
    int armies;
    Territory* source;
    Territory* target;
    Player* player;
public:
    Advance(int anID, int armies, Territory* source, Territory* target, Player* player);
    Advance(const Advance &advance2);
    Advance& operator=(const Advance& other);
    ~Advance();

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
    ~Bomb();

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
    ~Blockade();

    Blockade* clone() const;
    bool validate();
    void execute();
};

//Airlift class extends Order class
class Airlift:public Order{
private:
    int armies;
    Territory* source;
    Territory* target;
    Player* player;
public:
    Airlift(int anID, int armies, Territory* source, Territory* target, Player* player);
    Airlift(const Airlift &airlift2);
    Airlift& operator=(const Airlift& other);
    ~Airlift();

    Airlift* clone() const;
    bool validate();
    void execute();
};

//Negotiate class extends Order class
class Negotiate:public Order{
private:
    Player* player;
    Player* target;
public:
    Negotiate(int anID, Player* player, Player* target);
    Negotiate(const Negotiate &negotiate2);
    Negotiate& operator=(const Negotiate& other);
    ~Negotiate();

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

    void sort();
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