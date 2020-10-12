#include <iostream>
#include <vector>
#include "Common/Orders.h"

int main(){

    ID id = *new ID();
    OrdersList *ol = new OrdersList();
    OrdersList ol2;
    Order *order = new Order(id.setID());
    Order order2 = *order;
    Deploy *deploy = new Deploy(id.setID());
    Advance *advance = new Advance(id.setID());
    Bomb *bomb = new Bomb(id.setID());
    Blockade *blockade = new Blockade(id.setID());
    Airlift *airlift = new Airlift(id.setID());
    Negotiate *negotiate = new Negotiate(id.setID());
    Deploy *deploy2 = new Deploy(id.setID());
    *deploy2 = *deploy;

    ol->add(order);
    ol->add(deploy);
    ol->add(deploy2);
    ol->add(advance);
    ol->add(bomb);
    ol->add(blockade);
    ol->add(airlift);
    ol->add(negotiate);
    ol2 = *ol;

    cout << endl;
    ol2.remove(deploy);
    ol2.move(airlift,3);
    for (int i = 0; i < ol2.myList.size(); i++){
        (ol2.myList.at(i))->execute();
        cout << endl;
    }

//    for (int i = 0; i < ol->myList.size(); i++){
//        cout <<  (*ol->myList.at(i)).getID() << endl;
//    }

    for (int i = 0; i < ol2.myList.size(); i++){
        cout << "Copied: " << (*ol2.myList.at(i)).getID() << endl;
    }
    cout << endl;

    cout << order->getID() << endl;
    cout << order2.getID() << endl;

    cout << deploy->getID() << endl;
    cout << deploy2->getID() << endl;

}
