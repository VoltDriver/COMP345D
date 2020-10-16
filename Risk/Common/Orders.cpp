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
Deploy::Deploy(int anID) : Order(anID) {
    description = "This is a deploy order. It allows you to mobilize an army to attack another.";
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
    cout << "Is social distancing still a thing?" << endl;
    return true;
}

//execute() method for Deploy that prints out a different string depending on the boolean returned by validate()
void Deploy::execute() {
    cout << *this << endl;
    if (validate()){
        cout << "Your fake troops are mobilizing" << endl;
        cout << "Your fake troops have arrived to your fake fight in your fake life. Get ready for war General!" << endl;
    }
    else{
        cout << "The rona still be out there. Wear protection!!!!";
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
Bomb::Bomb(int anID) : Order(anID){
    description =  "This is a bomb order. It allows you to drop a bomb on another player's army.";
}

//Copy constructor for Bomb class
Bomb::Bomb(const Bomb &bomb2) : Order(bomb2) {

}

//Assignment operator for Bomb class
Bomb& Bomb::operator=(const Bomb &other) {
    this -> Order::operator=(other);
    return *this;
}

//validate() method for Bomb that prints out a string and returns true
bool Bomb::validate() {
    cout << "Can this bomb really virtually blow up?" << endl;
    return true;
}

//execute() method for Bomb that prints out a different string depending on the boolean returned by validate()
void Bomb::execute() {
    cout << *this << endl;
    if(validate()){
        cout << "Detonating bomb" << endl;
        cout << "*BOOM*" << endl;
    }
    else {
        cout << "Bomba failed!" << endl;
    }
}

//Constructor for Blockade class
Blockade::Blockade(int anID) : Order(anID){
    description = "This is a blockade order. It allows you to form a blockade and defend a particular territory.";
}

//Copy constructor for Blockade class
Blockade::Blockade(const Blockade &blockade2) : Order(blockade2) {

}

//Assignment operator for Blockade class
Blockade & Blockade::operator=(const Blockade &other) {
    this -> Order::operator=(other);
    return *this;
}

//validate() method for Blockade that prints out a string and returns true
bool Blockade::validate() {
    cout << "Do you really see a way to block this river or is that a mirage? P.S. Drink some water #HydroHomies" << endl;
    return true;
}

//execute() method for Blockade that prints out a different string depending on the boolean returned by validate()
void Blockade::execute() {
    cout << *this << endl;
    if (validate()) {
        cout << "Guess it wasn't a mirage. No LSD was consumed on this day" << endl;
        cout << "Blocked" << endl;
    }
    else{
        cout << "Too much LSD buddy. Stay calm, be safe!" << endl;
    }
}

//Constructor for Airlift class
Airlift::Airlift(int anID) : Order(anID){
    description = "This is an airlift order. This allows you to fly your army over a larger distance.";
}

//Copy constructor for Airlift class
Airlift::Airlift(const Airlift &airlift2) : Order(airlift2) {

}

//Assignment Operator for Airlift class
Airlift & Airlift::operator=(const Airlift &other) {
    this -> Order::operator=(other);
    return *this;
}

//validate() method for Airlift that prints out a string and returns true
bool Airlift::validate() {
    cout << "I wonder, if I attach balloons to my chair, will I fly?" << endl;
    return true;
}

//execute() method for Airlift that prints out a different string depending on the boolean returned by validate()
void Airlift::execute() {
    cout << *this << endl;
    if (validate()) {
        cout << "Up" << endl;
    }
    else {
        cout << "Look up..." << endl;
        cout << "Are you kidding me? You really thought that would work?" << endl;
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
