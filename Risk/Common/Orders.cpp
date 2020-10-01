#include "Orders.h"
#include <iterator>
#include <iostream>

using namespace std;

Orders:: Orders(){
    id = 0;
}

Deploy::Deploy(){
    id = 1;
}

Advance::Advance() {
    id = 2;
}

Bomb::Bomb(){
    id = 3;
}

Blockade::Blockade() {
    id = 4;
}

Airlift::Airlift() {
    id = 5;
}

Negotiate::Negotiate() {
    id = 6;
}

OrdersList::OrdersList(vector<Orders> &list){
    myList = &list;

}


void OrdersList::remove(Orders order){
    for(int i =0; i<myList->size(); i++ ){
        if (myList->at(i).id == order.id)
            myList->erase(myList->begin()+i);
    }
}

void OrdersList::move(Orders order){
    std::vector<Orders>:: iterator i;
    for(i = myList->begin(); i != myList->end(); i++){

    }
}

void OrdersList::add(Orders order){
    myList->push_back(order);
}



/*int main(){

    vector<Orders> list1;
    Orders order1;
    Deploy deploy1;
    OrdersList ol(list1);
    ol.add(deploy1);
    ol.add(order1);
    //vector<Orders> &vec1 = ol.myList;
    cout << ol.myList->at(0).id << endl;
    cout << ol.myList->size() << endl;
    ol.remove(deploy1);
    cout << ol.myList->at(0).id << endl;
    cout << ol.myList->size() << endl;
}*/