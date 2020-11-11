#include "Orders.h"
#include <iostream>
#include <vector>

using namespace std;


//Order class constructor
Order::Order(int anID) {
    id = anID;
    description = "This is a generic order. It does nothing but encapsulates all other orders.";
}

//Copy constructor for Order class
Order::Order(const Order &order2){
    cout << "Copy Constructor!" << endl;
    this->id = order2.id;
    this->description = order2.description;
}

//Assignment operator for Order class
Order& Order::operator=(const Order &other) {
    cout << "Assignment operator!" << endl;
    if (this != &other){
        this->id = other.id;
    }
    return *this;
}

// Stream insertion operator for all Order classes
ostream &operator<<(ostream &strm, const Order &order) {
    strm << order.description;
    return strm;
}

//getID() method that returns the id of an Order
int Order:: getID(){
    return id;
}

//validate() method for Order that prints out a string and returns true
bool Order::validate() {
    cout << "Validating..." << endl;
    return true;
}

//execute() method for Order that prints out a different string depending on the boolean returned by validate()
void Order::execute() {
    cout << *this << endl;
    if (validate()) {
        cout << "Executing..." << endl;
        cout << "Executed!" << endl;
    }
    else {
        cout << "Failed" << endl;
    }
}

//Constructor for Deploy class
Deploy::Deploy(int anID, int armies, Territory* target, Player* player) : Order(anID) {
    description = "This is a deploy order. It allows you to mobilize an army to attack another.";
    this->armies = armies;
    this->target = target;
    this->player = player;
}

//Copy constructor for Deploy class
Deploy::Deploy(const Deploy &deploy2) : Order(deploy2) {

}

//Assignment operator for Deploy class
Deploy& Deploy::operator=(const Deploy &other) {
    this -> Order::operator=(other);
    return *this;
}

//validate() method for Deploy that prints out a string and returns true
bool Deploy::validate() {
    if (target->getPlayerName().compare(player->name) == 0 && armies > 0)
            return true;
    else
        return false;
}

//execute() method for Deploy that prints out a different string depending on the boolean returned by validate()
void Deploy::execute() {
    cout << *this << endl;
    if (validate()){
        target->set_armies(target->get_armies()+armies);
    }
    else{
        cout << "This deploy order is not valid";
    }
}

//Constructor for Advance class
Advance::Advance(int anID) : Order(anID){
    description = "This is an advance order. It allows you to mobilize an army to a vacant territory.";
}

//Copy constructor for Advance class
Advance::Advance(const Advance &advance2) : Order(advance2) {

}

//Assignment operator for Advance class
Advance& Advance::operator=(const Advance &other) {
    this -> Order::operator=(other);
    return *this;
}

//validate() method for Advance that prints out a string and returns true
bool Advance::validate() {
    cout << "Can I advance?" << endl;
    return true;
}

//execute() method for Advance that prints out a different string depending on the boolean returned by validate()
void Advance::execute() {
    cout << *this << endl;
    if (validate()) {
        cout << "Proceeding to virtually move forward." << endl;
        cout << "Have successfully virtually moved forward (probably more steps than you walked today #SocialDistancing)! "<< endl;
    }
    else {
        cout << "You can't move them because they're virtual! Perhaps you can move yourself instead." << endl;
    }

}

//Constructor for Bomb class
Bomb::Bomb(int anID, Territory* target, Player* player) : Order(anID){
    description =  "This is a bomb order. It allows you to drop a bomb on another player's army.";
    this->target = target;
    this->player = player;
}

//Copy constructor for Bomb class
Bomb::Bomb(const Bomb &bomb2) : Order(bomb2) {

}

//Assignment operator for Bomb class
class Bomb& Bomb::operator=(const Bomb &other) {
    this -> Order::operator=(other);
    return *this;
}

//validate() method for Bomb that prints out a string and returns true
bool Bomb::validate() {
    if (target->getPlayer() != nullptr) {
        if (target->getPlayerName().compare(player->name) != 0)
            return true;
        else
            return false;
    }
    else
        return false;
}

//execute() method for Bomb that prints out a different string depending on the boolean returned by validate()
void Bomb::execute() {
    cout << *this << endl;
    if(validate()){
        if (target->get_armies() > 1)
            target->set_armies((target->get_armies()/2));
        else
            target->set_armies(0);
    }
    else {
        cout << "This bomb order is invalid!" << endl;
    }
}

//Constructor for Blockade class
Blockade::Blockade(int anID, Territory* target, Player* player) : Order(anID){
    description = "This is a blockade order. It allows you to form a blockade and defend a particular territory.";
    this->target = target;
    this->player = player;
}

//Copy constructor for Blockade class
Blockade::Blockade(const Blockade &blockade2) : Order(blockade2) {

}

//Assignment operator for Blockade class
class Blockade & Blockade::operator=(const Blockade &other) {
    this -> Order::operator=(other);
    return *this;
}

//validate() method for Blockade that prints out a string and returns true
bool Blockade::validate() {
    if (target->getPlayerName().compare(player->name) == 0)
        return true;
    else
        return false;
}

//execute() method for Blockade that prints out a different string depending on the boolean returned by validate()
void Blockade::execute() {
    cout << *this << endl;
    if (validate()) {
        target->set_armies(2*target->get_armies());
        target->setPlayer(nullptr);
// Remember to remove territory from player vector
    }
    else{
        cout << "Not a valid order" << endl;
    }
}

//Constructor for Airlift class
Airlift::Airlift(int anID, int armies, Territory* source, Territory* target, Player* player) : Order(anID){
    description = "This is an airlift order. This allows you to fly your army over a larger distance.";
    this->armies = armies;
    this->source = source;
    this->target = target;
    this->player = player;
}

//Copy constructor for Airlift class
Airlift::Airlift(const Airlift &airlift2) : Order(airlift2) {
    this->armies = airlift2.armies;
    this->source = airlift2.source;
    this->target = airlift2.target;
    this->player = airlift2.player;
}

//Assignment Operator for Airlift class
class Airlift & Airlift::operator=(const Airlift &other) {
    this -> Order::operator=(other);
    return *this;
}

//validate() method for Airlift that prints out a string and returns true
bool Airlift::validate() {
    if (source->getPlayerName().compare(player->name) == 0 && source->get_armies() >= armies && armies > 0)
        return true;
    else
        return false;
}

//execute() method for Airlift that prints out a different string depending on the boolean returned by validate()
void Airlift::execute() {
    cout << *this << endl;
    if (validate()) {
        if (target->getPlayerName().compare(player->name) == 0)
            target->set_armies(target->get_armies()+armies);
        else{
            cout << "Need to code attack" << endl;
        }
    }
    else {
        cout << "This airlift order is not valid" << endl;
    }
}

//Constructor for Negotiate class
Negotiate::Negotiate(int anID) : Order(anID){
    description = "This is a negotiate order. It allows you to make a deal with an opposing player.";
}

//copy constructor for Negotiate class
Negotiate::Negotiate(const Negotiate &negotiate2) : Order(negotiate2) {

}

//Assignment operator for Negotiate class
Negotiate & Negotiate::operator=(const Negotiate &other) {
    this -> Order::operator=(other);
    return *this;
}

//validate() method for Negotiate that prints out a string and returns true
bool Negotiate::validate() {
    cout << "So do we negotiate like the Mexican cartel or..." << endl;
    return false;
}

//execute() method for Negotiate that prints out a different string depending on the boolean returned by validate()
void Negotiate::execute() {
    cout << *this << endl;
    if (validate()){
        cout << "You used the wrong order then buddy" << endl;
    }
    else {
        cout << "Guess you read The Art of The Deal from yours truly, Donald T." << endl;
    }
}

//OrdersList constructor
OrdersList::OrdersList() {
    myList = *new vector<Order*>;
}

//Copy constructor for OrderList class
OrdersList::OrdersList(const OrdersList &orderList2) {
    myList = orderList2.myList;
}

//Assignment operator for OrderList class
OrdersList& OrdersList::operator=(const OrdersList &other) {
    cout << "Assignment Operator!" << endl;
    if (this != &other){
        for (Order* order: myList) {
            delete order;
        }
        this->myList = other.myList;
    }
    return *this;
}

//Stream insertion for OrdersList
ostream &operator<<(ostream &strm, const OrdersList &ordersList) {
    for (int i = 0; i < ordersList.myList.size(); i++){
        strm << (*ordersList.myList.at(i)).getID() << endl;
    }
    strm << endl;
    return strm;
}

// Destructor for OrdersList
OrdersList::~OrdersList() {
    for (Order* order: myList) {
        delete order;
    }
}

// remove() method that removes the Order specified in the parameter from the vector and shrinks the vector to fit the remaining Orders in it
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

//move() method that takes an Order and a position as parameters
//The Order in the specified position is removed and the Order specified as parameter is then inserted to the position that has now been freed
void OrdersList::move(Order *order, int pos){
    std::vector<Order>:: iterator i;
    Order *temp = order;
    this->remove(order);
    this->myList.insert(myList.begin()+pos, temp);
}

//add() method that pushes the Order specified in the parameter to the vector
void OrdersList::add(Order *order){
    myList.push_back(order);
}

int ID::currentID;

//ID class constructor
ID::ID() {
    currentID = 0;
}

//setID() method that creates a new ID for a new Order
int ID::setID() {
    return currentID++;
}
