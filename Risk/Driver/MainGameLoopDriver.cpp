#include <iostream>
#include "Common/Cards.h"
#include "Common/Player.h"
#include "Common/GameEngine.h"

int main() {
    // 1) A Player receives the correct number of armies in the reinforcement phase (showing different cases)
    GameEngine engine = GameEngine();
    engine.gameStart_Auto("test_success1.map", 2, true, true);
    engine.reinforcementPhase();

    GameEngine engine2 = GameEngine();
    engine2.gameStart_Auto("test_success1.map", 3, true, true);
    engine2.reinforcementPhase();

    GameEngine engine3 = GameEngine();
    engine3.gameStart_Auto("test_success1.map", 4, true, true);
    engine3.reinforcementPhase();

    GameEngine engine4 = GameEngine();
    engine4.gameStart_Auto("test_success1.map", 5, true, true);
    engine4.reinforcementPhase();

    // 2) A player will only issue deploy orders and no other kind of orders if they still have armies in their reinforcement pool.
    // 3) The  game  engine  will  only  execute  non-deploy orders  when  all  the  deploy  orders  of  all  players  have  been  executed
    // 4) A  player  can  issue  advance  orders  to  either  defend  or  attack,  based  on  the toAttack() and toDefend()  lists
    // 5) A  player  can  play  cards  to  issue  orders
    // 6) A player that does not control any territory is removed from the game.
    // 7) The game ends when a single player  controls  all  the  territories.
    GameEngine engineHuman = GameEngine();
    engineHuman.hasHumanPlayers = true;
    engineHuman.gameStart();
    engineHuman.startupPhase();

    Card c = Card(Bomb);

    for(Player* p : engineHuman.getPlayers())
    {
        p->hand->addCard(c);
    }

    engineHuman.mainGameLoop();
}

