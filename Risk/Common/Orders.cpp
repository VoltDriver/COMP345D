#include "Orders.h"
#include <iostream>
#include <vector>

using namespace std;



Order::Order(int anID) {
    id = anID;
}

Order::Order(const Order &order2){
    cout << "Copy Constructor!" << endl;
    id = order2.id;
}


Order& Order::operator=(const Order &other) {
    cout << "Assignment operator!" << endl;
    if (this != &other){
        this->id = other.id;
        delete &other;
    }
    return *this;
}

int Order:: getID(){
    return id;
}

bool Order::validate() {
    cout << "Validating..." << endl;
    return true;
}

void Order::execute() {
    cout << "Order: " << endl;
    if (validate()) {
        cout << "Executing..." << endl;
        cout << "Executed!" << endl;
    }
    else {
        cout << "Failed" << endl;
    }
}


Deploy::Deploy(int anID) : Order(anID) {

}

Deploy::Deploy(const Deploy &deploy2) : Order(deploy2) {

}

Deploy& Deploy::operator=(const Deploy &other) {
    this -> Order::operator=(other);
    return *this;
}

bool Deploy::validate() {
    cout << "Is social distancing still a thing?" << endl;
    return true;
}

void Deploy::execute() {
    cout << "Deploy: " << endl;
    if (validate()){
        cout << "Your fake troops are mobilizing" << endl;
        cout << "Your fake troops have arrived to your fake fight in your fake life. Get ready for war General!" << endl;
    }
    else{
        cout << "The rona still be out there. Wear protection!!!!";
    }
}

Advance::Advance(int anID) : Order(anID){

}

Advance::Advance(const Advance &advance2) : Order(advance2) {

}

Advance& Advance::operator=(const Advance &other) {
    this -> Order::operator=(other);
    return *this;
}

bool Advance::validate() {
    cout << "Can I advance?" << endl;
    return true;
}

void Advance::execute() {
    cout << "Advance: " << endl;
    if (validate()) {
        cout << "Proceeding to virtually move forward." << endl;
        cout << "Have successfully virtually moved forward (probably more steps than you walked today #SocialDistancing)! "<< endl;
    }
    else {
        cout << "You can't move them because they're virtual! Perhaps you can move yourself instead." << endl;
    }

}

Bomb::Bomb(int anID) : Order(anID){

}

Bomb::Bomb(const Bomb &bomb2) : Order(bomb2) {

}

Bomb& Bomb::operator=(const Bomb &other) {
    this -> Order::operator=(other);
    return *this;
}

bool Bomb::validate() {
    cout << "Can this bomb really virtually blow up?" << endl;
    return true;
}

void Bomb::execute() {
    cout << "Bomb: " << endl;
    if(validate()){
        cout << "Detonating bomb" << endl;
        cout << "*BOOM*" << endl;
    }
    else {
        cout << "Bomba failed!" << endl;
    }
}

Blockade::Blockade(int anID) : Order(anID){

}

Blockade::Blockade(const Blockade &blockade2) : Order(blockade2) {

}

Blockade & Blockade::operator=(const Blockade &other) {
    this -> Order::operator=(other);
    return *this;
}

bool Blockade::validate() {
    cout << "Do you really see a way to block this river or is that a mirage? P.S. Drink some water #HydroHomies" << endl;
    return true;
}

void Blockade::execute() {
    cout << "Blockade: " << endl;
    if (validate()) {
        cout << "Guess it wasn't a mirage. No LSD was consumed on this day" << endl;
        cout << "Blocked" << endl;
    }
    else{
        cout << "Too much LSD buddy. Stay calm, be safe!" << endl;
    }
}

Airlift::Airlift(int anID) : Order(anID){

}

Airlift::Airlift(const Airlift &airlift2) : Order(airlift2) {

}

Airlift & Airlift::operator=(const Airlift &other) {
    this -> Order::operator=(other);
    return *this;
}

bool Airlift::validate() {
    cout << "I wonder, if I attach balloons to my chair, will I fly?" << endl;
    return true;
}

void Airlift::execute() {
    cout << "Airlift: " << endl;
    if (validate()) {
        cout << "Up" << endl;
    }
    else {
        cout << "Look up..." << endl;
        cout << "Are you kidding me? You really thought that would work?" << endl;
    }
}


Negotiate::Negotiate(int anID) : Order(anID){

}

Negotiate::Negotiate(const Negotiate &negotiate2) : Order(negotiate2) {

}

Negotiate & Negotiate::operator=(const Negotiate &other) {
    this -> Order::operator=(other);
    return *this;
}

bool Negotiate::validate() {
    cout << "So do we negotiate like the Mexican cartel or..." << endl;
    return false;
}

void Negotiate::execute() {
    cout << "Negotiate: " << endl;
    if (validate()){
        cout << "You used the wrong order then buddy" << endl;
    }
    else {
        cout << "Guess you read The Art of The Deal from yours truly, Donald T." << endl;
    }
}

OrdersList::OrdersList() {
    myList = *new vector<Order*>;
}

OrdersList::OrdersList(const OrdersList &orderList2) {
    myList = orderList2.myList;
}

OrdersList& OrdersList::operator=(const OrdersList &other) {
    cout << "Assignment Operator!" << endl;
    if (this != &other){
        this->myList = other.myList;
        delete &other;
    }
    return *this;
}


int OrdersList::remove(Order *order){
    for(int i =0; i<myList.size(); i++ ){
        if ((*myList.at(i)).getID() == (*order).getID()) {
            myList.erase(myList.begin() + i);
            myList.shrink_to_fit();
            return i;
        }
    }
    return 0;
}

void OrdersList::move(Order *order, int pos){
    std::vector<Order>:: iterator i;
    Order *temp = order;
    this->remove(order);
    this->myList.insert(myList.begin()+pos, temp);
}

void OrdersList::add(Order *order){
    myList.push_back(order);
}

int ID::currentID;

ID::ID() {
    currentID = 0;
}


int ID::setID() {
    return currentID++;
}



