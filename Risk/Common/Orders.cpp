#include "Orders.h"
#include <iostream>

using namespace std;

Orders:: Orders(){
    id = 0;
}

Orders::Orders(int id) {
    this->id = id;
}

int Orders:: getID(){
    return id;
}

Deploy::Deploy(){

}

Advance::Advance() {

}

Bomb::Bomb(){

}

Blockade::Blockade() {

}

Airlift::Airlift() {

}

Negotiate::Negotiate() {

}

OrdersList::OrdersList(vector<Orders> &list){
    myList = &list;

}


int OrdersList::remove(Orders order){
    for(int i =0; i<myList->size(); i++ ){
        if (myList->at(i).id == order.id) {
            myList->erase(myList->begin() + i);
            myList->shrink_to_fit();
            return i;
        }
    }
    return 0;
}

void OrdersList::move(Orders order, int pos){
    std::vector<Orders>:: iterator i;
    Orders temp = order;
    this->remove(order);
    this->myList->insert(myList->begin()+pos, temp);
}

void OrdersList::add(Orders order){
    myList->push_back(order);
}



int main(){

    vector<Orders> list1;
    int i = 0;
    Orders order1(i);
    Orders deploy1(++i);
    Orders deploy2(++i);
    Orders deploy3(++i);
    Orders deploy4(++i);
    Orders deploy5(++i);
    Orders deploy6(++i);
    OrdersList ol(list1);
    ol.add(order1);
    ol.add(deploy1);
    ol.add(deploy2);
    ol.add(deploy3);
    ol.add(deploy4);
    ol.add(deploy5);
    ol.add(deploy6);
    cout << "size: " << ol.myList->size() << endl;
    for (i = 0; i < ol.myList->size(); i++){
        cout <<  ol.myList->at(i).id << endl;
    }
    ol.move(deploy5,3);
    for (i = 0; i < ol.myList->size(); i++){
        cout << "moved: " << ol.myList->at(i).id << endl;
    }
    cout << ol.myList->size() << endl;
}