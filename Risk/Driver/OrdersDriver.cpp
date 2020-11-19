#include <iostream>
#include <vector>
#include "Common/Orders.h"
#include "Common/GameEngine.h"

int main(){

    /**
     * To execute both tests, enter 1 as map, 2 players, and y for both observers. This code does not simulate a full turn but rather
     * orders that we have manually to show different cases. Hence no card is handed out in this driver but you will see that if a player
     * conquers a territory, the bool conquered is flagged as true and players draw a card based on that in the actual turns. This is done in
     * line 657 of GameEngine.cpp in the executeOrdersPhase()
     */

    /**
     * Test without blockade to demonstrate friendly attack (Negotiate), the advance will not execute since it belongs to a friendly player
     */
    GameEngine ge = *new GameEngine();
    ge.gameStart();
    ge.startupPhase();
    list<Player*> players = ge.getPlayers();
    list<Player*>::iterator player2;
    list<Player*>::iterator player1;
    ID id = *new ID();

    int armies = 9;

    player1 = players.begin();
    player2 = ++players.begin();

    Deploy *deploy = new Deploy(id.setID(), 9, (*player1)->to_defend().at(0), *player1);
    Advance *advance = new Advance(id.setID(), 10, (*player1)->to_defend().at(0), (*player1)->to_attack().at(0), *player1);
    class Bomb *bomb = new class Bomb(id.setID(), (*player1)->to_defend().at(0), *player1);
    class Airlift *airlift = new class Airlift(id.setID(), armies, (*player2)->to_defend().at(0), (*player1)->to_attack().at(0), *player1);
    Negotiate *negotiate = new Negotiate(id.setID(), *player1, *player2);
    (*player1)->getOrdersList()->add(advance);
    (*player1)->getOrdersList()->add(bomb);
    (*player1)->getOrdersList()->add(airlift);
    (*player1)->getOrdersList()->add(negotiate);
    (*player1)->getOrdersList()->add(deploy);

    Deploy *deploy1 = new Deploy(id.setID(), 9, (*player2)->to_defend().at(0), *player2);
    Advance *advance1 = new Advance(id.setID(), 8, (*player2)->to_defend().at(0), (*player2)->to_attack().at(0), *player2);
    class Bomb *bomb1 = new class Bomb(id.setID(), (*player1)->to_defend().at(0), *player2);
    class Blockade *blockade1 = new class Blockade(id.setID(), (*player1)->to_defend().at(0), *player2);
    class Airlift *airlift1 = new class Airlift(id.setID(), 1, (*player2)->to_defend().at(0), (*player1)->to_attack().at(0), *player2);
    Negotiate *negotiate1 = new Negotiate(id.setID(), *player2, *player1);
    (*player2)->getOrdersList()->add(bomb1);
    (*player2)->getOrdersList()->add(blockade1);
    (*player2)->getOrdersList()->add(airlift1);
    (*player2)->getOrdersList()->add(negotiate1);
    (*player2)->getOrdersList()->add(deploy1);
    (*player2)->getOrdersList()->add(advance1);

    ge.executeOrdersPhase();

    /**
     * Test with blockade to show neutral player and to show that the territory has been conquered since it belongs to the neutral player
     */

    GameEngine ge1 = *new GameEngine();
    ge1.gameStart();
    ge1.startupPhase();
    list<Player*> players1 = ge1.getPlayers();
    list<Player*>::iterator player4;
    list<Player*>::iterator player3;

    player3 = players1.begin();
    player4 = ++players1.begin();

    Deploy *deploy2 = new Deploy(id.setID(), 9, (*player3)->to_defend().at(0), *player3);
    Advance *advance2 = new Advance(id.setID(), 10, (*player3)->to_defend().at(0), (*player3)->to_attack().at(0), *player3);
    class Bomb *bomb2 = new class Bomb(id.setID(), (*player3)->to_defend().at(0), *player3);
    class Blockade *blockade2 = new class Blockade(id.setID(), (*player3)->to_defend().at(0), *player3);
    class Airlift *airlift2 = new class Airlift(id.setID(), armies, (*player4)->to_defend().at(0), (*player3)->to_attack().at(0), *player3);
    Negotiate *negotiate2 = new Negotiate(id.setID(), *player3, *player4);
    (*player3)->getOrdersList()->add(advance2);
    (*player3)->getOrdersList()->add(bomb2);
    (*player3)->getOrdersList()->add(blockade2);
    (*player3)->getOrdersList()->add(airlift2);
    (*player3)->getOrdersList()->add(negotiate2);
    (*player3)->getOrdersList()->add(deploy2);

    Deploy *deploy3 = new Deploy(id.setID(), 9, (*player4)->to_defend().at(0), *player4);
    Advance *advance3 = new Advance(id.setID(), 8, (*player4)->to_defend().at(0), (*player4)->to_attack().at(0), *player4);
    class Bomb *bomb3 = new class Bomb(id.setID(), (*player3)->to_defend().at(0), *player4);
    class Blockade *blockade3 = new class Blockade(id.setID(), (*player3)->to_defend().at(0), *player4);
    class Airlift *airlift3 = new class Airlift(id.setID(), 1, (*player4)->to_defend().at(0), (*player3)->to_attack().at(0), *player4);
    Negotiate *negotiate3 = new Negotiate(id.setID(), *player4, *player3);
    (*player4)->getOrdersList()->add(bomb3);
    (*player4)->getOrdersList()->add(blockade3);
    (*player4)->getOrdersList()->add(airlift3);
    (*player4)->getOrdersList()->add(negotiate3);
    (*player4)->getOrdersList()->add(deploy3);
    (*player4)->getOrdersList()->add(advance3);

    ge1.executeOrdersPhase();
}
