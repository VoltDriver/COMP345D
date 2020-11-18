#include <iostream>
#include <vector>
#include "Common/Orders.h"
#include "Common/GameEngine.h"

int main(){
//    GameEngine ge = *new GameEngine();
//    ge.gameStart_Auto();
//    ge.startupPhase();
//    ge.executeOrdersPhase();
// initializing an ID object
//    ID id = *new ID();
//    //creating an OrdersList
//    OrdersList *ol = new OrdersList();
//    Player* player = new Player();
//    Player* player2 = new Player();
//    player2->name = "Tayyab";
//    Territory* source = new Territory(0, "hello", 0);
//    Territory* target = new Territory(1, "hilo", 0);
//    player->setReinforcementPool(10);
//    source->set_armies(10);
//    target->set_armies(1);
//    player->addTerritory(source);
//    player2->addTerritory(target);
//    int armies = 9;
//
//    //Creating an object of each class and assigning an ID to them using setID() which increments by one everytime it is called
//    Deploy *deploy = new Deploy(id.setID(), armies, source, player);
//    Advance *advance = new Advance(id.setID(), armies, source, target, player);
//    class Bomb *bomb = new class Bomb(id.setID(), target, player);
//    class Blockade *blockade = new class Blockade(id.setID(), target, player);
//    cout << "hello" << endl;
//    class Airlift *airlift = new class Airlift(id.setID(), armies, source, target, player);
//    Negotiate *negotiate = new Negotiate(id.setID(), player, player2);
//    Negotiate *negotiate1 = new Negotiate(id.setID(), player, player);
//    negotiate->execute();
//    cout << player->isFriendly(player2) << endl;
//    cout << player2->isFriendly(player) << endl;
//    negotiate1->execute();
////    Adding each of the Orders created to the OrdersList
//    ol->add(advance);
//    ol->add(bomb);
//    ol->add(blockade);
//    ol->add(airlift);
//    ol->add(negotiate);
//    ol->add(deploy);
//    ol->sort();
//    for(Order* order: ol->myList)
//        cout << order->getDescription() << endl;
//
//    //creating a copy of the OrdersList ol called ol2 using the assignment operator
//    OrdersList ol2;
//    ol2 = *ol;
//
//    //printing out the copied OrdersList
//    cout << "Copied: \n" << ol2;
//
//
//    //printing out the stream insertion operators for each of the Orders in ol2
//    cout<< "Printing out the stream insertion operators for each Order type" << endl;
//    cout << endl;
//    for (int i = 0; i < ol2.myList.size(); i++){
//        cout << target->get_armies() << endl;
//        (ol2.myList.at(i))->execute();
//        cout << target->get_armies() << endl;
//        cout << endl;
//    }
//
//    //printing out the Orders ids before using the move() method
//    cout << "Before move(): \n" << ol2;
//
//
//    //Moving the Order airlift of id 5 to position 3
//    ol2.move(airlift,3);
//
//    //printing out the OrdersList after the use of the move() method
//    cout << "After move(): \n" << ol2;
//
//
//    //removing the Deploy Order of id 1 from the OrdersList
//    ol2.remove(deploy);
//
//    //Printing out the OrdersList after the use of remove() method
//    cout << "After remove(): \n" << ol2;
//
//
//    //Using the copy constructor to create a copy of order called order2 which takes the same id=0 of order
//    //showing that order and order2 indeed have the same id
//
//
//    cout << endl;
//
//    //Using the assignment Operator to create a copy of deploy called deploy2 which takes the same id = 1 of deploy
//    Deploy *deploy2 = new Deploy(id.setID(), armies, target, player);
//    *deploy2 = *deploy;
//
//    //Showing that deploy has successfully been copied to deploy2
}
