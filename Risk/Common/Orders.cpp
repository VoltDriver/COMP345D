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
            return i;
        }
    }
    return 0;
}

void OrdersList::move(Orders order, int pos){
    std::vector<Orders>:: iterator i;
    Orders temp = order;
    int place = this->remove(order);
    this->myList->insert(myList->begin()+place,myList->at(pos));
    this->myList->insert(myList->begin()+pos, temp);
}

void OrdersList::add(Orders order){
    myList->push_back(order);
}



int main(){

    vector<Orders> list1;
    int i = 2;
    Orders order1(i);
    Orders deploy1(++i);
    Orders deploy2(++i);
    cout << i << endl;
    cout << order1.getID() << endl;
    cout << "2nd " << deploy1.getID() << endl;
    OrdersList ol(list1);
    ol.add(deploy1);
    ol.add(order1);
    ol.add(deploy2);
    Orders * ptr = &ol.myList->at(0);
    //vector<Orders> &vec1 = ol.myList;
    cout << ol.myList->size() << endl;
    ol.remove(deploy1);
    cout << ol.myList->at(0).id << endl;
    ol.move(deploy2,0);
    cout << "moved " << ol.myList->at(0).id << endl;
    cout << ol.myList->at(2).id << endl;
    cout << ol.myList->size() << endl;
}