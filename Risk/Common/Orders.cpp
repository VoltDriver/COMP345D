#include "Orders.h"
#include <iostream>
#include <vector>

using namespace std;



Order::Order(int anID) {
    id = anID;
}

int Order:: getID(){
    return id;
}

bool Order::validate() {
    cout << "Validating..." << endl;
    return true;
}

void Order::execute() {
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
bool Deploy::validate() {
    cout << "Is social distancing still a thing?" << endl;
    return true;
}

void Deploy::execute() {
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

bool Advance::validate() {
    cout << "Can I advance?" << endl;
    return true;
}

void Advance::execute() {
    validate();
    cout << "Proceeding to virtually move forward." << endl;
    cout << "Have successfully virtually moved forward (probably more steps than you walked today #SocialDistancing)! " << endl;
}

Bomb::Bomb(int anID) : Order(anID){

}

bool Bomb::validate() {
    cout << "Can this bomb really virtually blow up?" << endl;
    return true;
}

void Bomb::execute() {
    validate();
    cout << "Detonating bomb" << endl;
    cout << "*BOOM*" << endl;
}

Blockade::Blockade(int anID) : Order(anID){

}

bool Blockade::validate() {
    cout << "Do you really see a way to block this river or is that a mirage? P.S. Drink some water #HydroHomies" << endl;
    return true;
}

void Blockade::execute() {
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

bool Airlift::validate() {
    cout << "I wonder, if I attach balloons to my chair, will I fly?" << endl;
    return true;
}

void Airlift::execute() {
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

bool Negotiate::validate() {
    cout << "So do we negotiate like the Mexican cartel or..." << endl;
    return false;
}

void Negotiate::execute() {
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

OrdersList::OrdersList(vector<Order*> list){
    myList = list;

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

int ID::getID() {
    return currentID++;
}



int main(){

    vector<Order> list1;
    int i = 0;

    ID id = *new ID();
    OrdersList ol;
    Order *order = new Order(id.getID());
    Deploy *deploy = new Deploy(id.getID());
    Advance *advance = new Advance(id.getID());
    Bomb *bomb = new Bomb(id.getID());
    Blockade *blockade = new Blockade(id.getID());
    Airlift *airlift = new Airlift(id.getID());
    Negotiate *negotiate = new Negotiate(id.getID());

    ol.add(order);
    ol.add(deploy);
    ol.add(advance);
    ol.add(bomb);
    ol.add(blockade);
    ol.add(airlift);
    ol.add(negotiate);
    for (i = 0; i < ol.myList.size(); i++){
        (ol.myList.at(i))->execute();
    }
    cout << "size: " << ol.myList.size() << endl;
    for (i = 0; i < ol.myList.size(); i++){
        cout <<  (*ol.myList.at(i)).getID() << endl;
    }
    ol.move(airlift,3);
    for (i = 0; i < ol.myList.size(); i++){
        cout << "moved: " << (*ol.myList.at(i)).getID() << endl;
    }
    cout << ol.myList.size() << endl;
}