#include "Orders.h"
#include <iostream>
#include <vector>
#include <random>
#include <ctime>

using namespace std;


//Order class constructor
Order::Order(int anID) {
    id = anID;
    description = "Order";
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

string Order::getDescription() {
    return description;
}

//getID() method that returns the id of an Order
int Order:: getID(){
    return id;
}

int Order::getPriority() {
    return priority;
}

bool compare(Order* order, Order* other) {
    return order->priority < other->priority;
}

//Constructor for Deploy class
Deploy::Deploy(int anID, int armies, Territory* target, Player* player) : Order(anID) {
    this->priority = 1;
    this->description = "Deploy";
    this->armies = armies;
    this->target = target;
    this->player = player;
}

//Copy constructor for Deploy class
Deploy::Deploy(const Deploy &deploy2) : Order(deploy2) {
    this->priority = 1;
    this->description = deploy2.description;
    this->armies = deploy2.armies;
    this->target = deploy2.target;
    this->player = deploy2.player;
}

//Assignment operator for Deploy class
Deploy& Deploy::operator=(const Deploy &other) {
    this -> Order::operator=(other);
    this->priority = 1;
    this->armies = other.armies;
    this->target = other.target;
    this->player = other.player;
    return *this;
}

//validate() method for Deploy that prints out a string and returns true
bool Deploy::validate() {
    if (player != nullptr && target != nullptr && target->getPlayer() != nullptr && target->getPlayerName().compare(player->name) == 0 &&
        armies > 0 && armies <= player->getReinforcementPool()){
        return true;
    }
    return false;
}

//execute() method for Deploy that prints out a different string depending on the boolean returned by validate()
void Deploy::execute() {
    cout << *this << endl;
    if (validate()){
        target->set_armies(target->get_armies()+armies);
        player->setReinforcementPool(player->getReinforcementPool()-armies);
    }
    else{
        cout << "This deploy order is not valid" << endl;
    }
    player->getOrdersList()->remove(this);
}

Deploy* Deploy::clone() const {
    return new Deploy(*this);
}

//Constructor for Advance class
Advance::Advance(int anID, int armies, Territory* source, Territory* target, Player* player) : Order(anID){
    description = "Advance";
    this -> priority = 4;
    this->armies = armies;
    this->source = source;
    this->target = target;
    this->player = player;
}

//Copy constructor for Advance class
Advance::Advance(const Advance &advance2) : Order(advance2) {
    this -> priority = 4;
    this->description = advance2.description;
    this->armies = advance2.armies;
    this->source = advance2.source;
    this->player = advance2.player;
}

//Assignment operator for Advance class
Advance& Advance::operator=(const Advance &other) {
    this -> Order::operator=(other);
    this -> priority = 4;
    this->armies = other.armies;
    this->source = other.source;
    this->player = other.player;
    return *this;
}

//validate() method for Advance that prints out a string and returns true
bool Advance::validate() {
    if(player != nullptr && source != nullptr && target != nullptr && source->borders_territory(target) && source->getPlayer() !=
        nullptr && source->getPlayerName().compare(player->name) && source->get_armies() >= armies > 0) {
        if (target->getPlayer() != nullptr && player->name.compare(target->getPlayerName()) != 0 && player->isFriendly(target->getPlayer()))
            return false;
        else
            return true;
    }
    return false;
}

//execute() method for Advance that prints out a different string depending on the boolean returned by validate()
void Advance::execute() {
    cout << *this << endl;
    if (validate()) {
        if (target->getPlayer() == nullptr || target->getPlayerName().compare(player->name) != 0) {
            source->set_armies(source->get_armies()-armies);
            int startingDefendingArmies = target->get_armies();
            int startingArmies = armies;
            int attackingUnitsKilled = 0;
            int defendingUnitsKilled = 0;
            srand((unsigned int)time(NULL));

            for (int i = 0; i < armies; i++) {
                cout << i << "   " << armies << endl;
                int attackingKillChance = rand() % 10 + 1;
                cout << "Chance to kill defending: " << attackingKillChance << endl << endl << endl;
                if (attackingKillChance > 4) {
                    defendingUnitsKilled++;
                    if (defendingUnitsKilled == target->get_armies())
                        break;
                }
            }
            for (int i = 0; i < target->get_armies(); i++) {
                cout << i << "   " << target->get_armies() << endl;
                int defendingKillChance = rand() % 10 + 1;
                cout << "Chance to kill attacking: " << defendingKillChance << endl << endl << endl;
                if (defendingKillChance > 3) {
                    attackingUnitsKilled++;
                    if (attackingUnitsKilled == armies)
                        break;
                }
            }
            armies -= attackingUnitsKilled;
            target->set_armies(target->get_armies() - defendingUnitsKilled);
            if (armies > 0 && target->get_armies() == 0) {
                cout << "I have conquered with an army of " << startingArmies << " by killing " << defendingUnitsKilled
                     << " of the " << startingDefendingArmies << " units and losing " << attackingUnitsKilled
                     << " units and being left with " << armies << " remaining!" << endl;
                target->set_armies(armies);
                Player* p = target->getPlayer();
                if (p != nullptr) {
                    p->removeTerritory(target);
                    target->setPlayer(nullptr);
                    p = nullptr;
                }
                target->setPlayer(player);
                player->addTerritory(target);
                if (!(player->hasConquered())){
                    player->setConquered(true);
                }
            }
            else if (armies == 0) {
                cout << "I have defended with an army of " << startingDefendingArmies << " by killing "
                     << attackingUnitsKilled << " of the " << startingArmies << " units and losing "
                     << defendingUnitsKilled << " units and being left with " << target->get_armies() << " remaining!"
                     << endl;
                source->set_armies(source->get_armies() + armies);
            }
            else {
                //
            }
        }
        else
            target->set_armies(target->get_armies() + armies);
    }
    else {
        cout << "This airlift order is not valid" << endl;
    }
    player->getOrdersList()->remove(this);
}

Advance* Advance::clone() const {
    return new Advance(*this);
}

//Constructor for Bomb class
Bomb::Bomb(int anID, Territory* target, Player* player) : Order(anID){
    description =  "Bomb";
    this->priority = 4;
    this->target = target;
    this->player = player;
}

//Copy constructor for Bomb class
Bomb::Bomb(const Bomb &bomb2) : Order(bomb2) {
    this->priority = 4;
    this->description = bomb2.description;
    this->target = bomb2.target;
    this->player = bomb2.player;
}

//Assignment operator for Bomb class
class Bomb& Bomb::operator=(const Bomb &other) {
    this -> Order::operator=(other);
    this->priority = 4;
    this->description = other.description;
    this->target = other.target;
    this->player = other.player;
    return *this;
}

//validate() method for Bomb that prints out a string and returns true
bool Bomb::validate() {
    if (target != nullptr && player != nullptr && target->getPlayer() != nullptr && target->getPlayerName().compare(player->name) == 0) {
        return false;
    }
    else
        return true;
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
    player->getOrdersList()->remove(this);
}

class Bomb* Bomb::clone() const {
    return new Bomb(*this);
}

//Constructor for Blockade class
Blockade::Blockade(int anID, Territory* target, Player* player) : Order(anID){
    description = "Blockade";
    this->priority = 3;
    this->target = target;
    this->player = player;
}

//Copy constructor for Blockade class
Blockade::Blockade(const Blockade &blockade2) : Order(blockade2) {
    this->description = blockade2.description;
    this->priority = 3;
    this->target = blockade2.target;
    this->player = blockade2.player;
}

//Assignment operator for Blockade class
class Blockade & Blockade::operator=(const Blockade &other) {
    this -> Order::operator=(other);
    this->priority = 3;
    this->target = other.target;
    this->player = other.player;
    return *this;
}

//validate() method for Blockade that prints out a string and returns true
bool Blockade::validate() {
    if (target->getPlayer() != nullptr && target->getPlayerName().compare(player->name) == 0)
        return true;
    else
        return false;
}

//execute() method for Blockade that prints out a different string depending on the boolean returned by validate()
void Blockade::execute() {
    cout << *this << endl;
    if (validate()) {
        target->set_armies(2*target->get_armies());
        player->removeTerritory(target);
        target->setPlayer(nullptr);
    }
    else{
        cout << "Not a valid order" << endl;
    }
    player->getOrdersList()->remove(this);
}

class Blockade* Blockade::clone() const {
    return new Blockade(*this);
}

//Constructor for Airlift class
Airlift::Airlift(int anID, int armies, Territory* source, Territory* target, Player* player) : Order(anID){
    this->priority = 2;
    description = "Airlift";
    this->armies = armies;
    this->source = source;
    this->target = target;
    this->player = player;
}

//Copy constructor for Airlift class
Airlift::Airlift(const Airlift &airlift2) : Order(airlift2) {
    this->description = airlift2.description;
    this->priority = 2;
    this->armies = airlift2.armies;
    this->source = airlift2.source;
    this->target = airlift2.target;
    this->player = airlift2.player;
}

//Assignment Operator for Airlift class
class Airlift & Airlift::operator=(const Airlift &other) {
    this -> Order::operator=(other);
    this->priority = 2;
    this->armies = other.armies;
    this->source = other.source;
    this->target = other.target;
    this->player = other.player;
    return *this;
}

//validate() method for Airlift that prints out a string and returns true
bool Airlift::validate() {
    if (source != nullptr && player != nullptr && target != nullptr && source->getPlayer() != nullptr && source->getPlayerName().compare(player->name) == 0 && source->get_armies() >= armies && armies > 0) {
        if (target->getPlayer() != nullptr && player->name.compare(target->getPlayerName()) != 0 &&
            player->isFriendly(target->getPlayer()))
            return false;
        else
            return true;
    }
    else
        return false;
}

//execute() method for Airlift that prints out a different string depending on the boolean returned by validate()
void Airlift::execute() {
    cout << *this << endl;
    if (validate()) {
        if (target->getPlayer() == nullptr || target->getPlayerName().compare(player->name) != 0) {
            source->set_armies(source->get_armies()-armies);
            int startingDefendingArmies = target->get_armies();
            int startingArmies = armies;
            int attackingUnitsKilled = 0;
            int defendingUnitsKilled = 0;
            srand((unsigned int)time(NULL));

            for (int i = 0; i < armies; i++) {
                cout << i << "   " << armies << endl;
                int attackingKillChance = rand() % 10 + 1;
                cout << "Chance to kill defending: " << attackingKillChance << endl << endl << endl;
                if (attackingKillChance > 4) {
                    defendingUnitsKilled++;
                    if (defendingUnitsKilled == target->get_armies())
                        break;
                }
            }
            for (int i = 0; i < target->get_armies(); i++) {
                cout << i << "   " << target->get_armies() << endl;
                int defendingKillChance = rand() % 10 + 1;
                cout << "Chance to kill attacking: " << defendingKillChance << endl << endl << endl;
                if (defendingKillChance > 3) {
                    attackingUnitsKilled++;
                    if (attackingUnitsKilled == armies)
                        break;
                    }
            }
            armies -= attackingUnitsKilled;
            target->set_armies(target->get_armies() - defendingUnitsKilled);
            if (armies > 0 && target->get_armies() == 0) {
                cout << "I have conquered with an army of " << startingArmies << " by killing " << defendingUnitsKilled
                     << " of the " << startingDefendingArmies << " units and losing " << attackingUnitsKilled
                     << " units and being left with " << armies << " remaining!" << endl;
                target->set_armies(armies);
                Player* p = target->getPlayer();
                if (p != nullptr) {
                    p->removeTerritory(target);
                    target->setPlayer(nullptr);
                    p = nullptr;
                }
                target->setPlayer(player);
                player->addTerritory(target);
                if (!(player->hasConquered())){
                    player->setConquered(true);
                }
            }
            else if (armies == 0) {
                cout << "I have defended with an army of " << startingDefendingArmies << " by killing "
                     << attackingUnitsKilled << " of the " << startingArmies << " units and losing "
                     << defendingUnitsKilled << " units and being left with " << target->get_armies() << " remaining!"
                     << endl;
                source->set_armies(source->get_armies() + armies);
            }
            else {
                //
            }
        }
        else
            target->set_armies(target->get_armies() + armies);
    }
    else {
        cout << "This airlift order is not valid" << endl;
    }
    player->getOrdersList()->remove(this);
}

class Airlift* Airlift::clone() const {
    return new Airlift(*this);
}

//Constructor for Negotiate class
Negotiate::Negotiate(int anID, Player* player, Player* target) : Order(anID){
    this->description = "Negotiate";
    this->priority = 4;
    this->player = player;
    this->target = target;
}

//copy constructor for Negotiate class
Negotiate::Negotiate(const Negotiate &negotiate2) : Order(negotiate2) {
    this->priority = 4;
    this->player = negotiate2.player;
    this->target = negotiate2.target;
}

//Assignment operator for Negotiate class
Negotiate & Negotiate::operator=(const Negotiate &other) {
    this -> Order::operator=(other);
    this->priority = 4;
    this->player = other.player;
    this->target = other.target;
    return *this;
}

//validate() method for Negotiate that prints out a string and returns true
bool Negotiate::validate() {
    if (player != nullptr && target != nullptr && player->name.compare(target->name) != 0)
        return true;
    else
        return false;
}

//execute() method for Negotiate that prints out a different string depending on the boolean returned by validate()
void Negotiate::execute() {
    cout << *this << endl;
    if (validate()){
        player->addFriendlyPlayer(target);
        target->addFriendlyPlayer(player);
    }
    else {
        cout << "Guess you read The Art of The Deal from yours truly, Donald T." << endl;
    }
//    player->getOrdersList()->remove(this);
}

Negotiate* Negotiate::clone() const {
    return new Negotiate(*this);
}

//OrdersList constructor
OrdersList::OrdersList() {
    myList = vector<Order*>();
}

//Copy constructor for OrderList class
OrdersList::OrdersList(const OrdersList &orderList2) {
    for (int i = 0; i < orderList2.myList.size(); i++){
        this->myList.push_back(myList.at(i)->clone());
    }
}

//Assignment operator for OrderList class
OrdersList& OrdersList::operator=(const OrdersList &other) {
    cout << "Assignment Operator!" << endl;
    if (this != &other){
        for (Order* order: myList) {
            delete order;
        }
        for (int i = 0; i < other.myList.size(); i++){
            this->myList.push_back(other.myList.at(i)->clone());
        }
    }
    return *this;
}

//Stream insertion for OrdersList
ostream &operator<<(ostream &strm, const OrdersList &ordersList) {
    for (int i = 0; i < ordersList.myList.size(); i++){
        strm << ordersList.myList.at(i)->getDescription() << " ID: " << ordersList.myList.at(i)->getID() << endl;

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
    return -1;
}

void OrdersList::sort() {
    std::sort(this->myList.begin(), this->myList.end(), compare);
}

//move() method that takes an Order and a position as parameters
//The Order in the specified position is removed and the Order specified as parameter is then inserted to the position that has now been freed
void OrdersList::move(Order *order, int pos){
    if (this->myList.at(pos-1)->getPriority() <= order->getPriority()) {
        std::vector<Order>::iterator i;
        Order *temp = order;
        this->remove(order);
        this->myList.insert(myList.begin() + pos, temp);
    }
}

//add() method that pushes the Order specified in the parameter to the vector
void OrdersList::add(Order *order){
    myList.push_back(order);
    this->sort();
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
