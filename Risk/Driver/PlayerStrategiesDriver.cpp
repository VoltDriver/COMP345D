#include <iostream>
#include "Common\GameEngine.h"

using namespace std;

int main() {
    // Setting up GameEngine
    GameEngine engine = GameEngine();
    engine.gameStart_Auto("test_success1.map", 4, true, true);
    engine.startupPhase();

    // Assigning strategies
    int counter = 0;
    for(Player* p : engine.getPlayers())
    {
        switch (counter) {
            case 0:
                p->setStrategy(new AggressivePlayerStrategy());
                break;
            case 1:
                p->setStrategy(new AggressivePlayerStrategy());
                break;
            case 2:
                p->setStrategy(new BenevolentPlayerStrategy());
                break;
            default:
                p->setStrategy(new NeutralPlayerStrategy());
                break;
        }

        counter++;
    }

    // Set dynamic switching to on, so we can see a dynamic change in strategies.
    engine.dynamicStrategySwitching = true;

    // Launching game
    engine.mainGameLoop();

    // Printing out the players and their strategies.
    for(Player* p : engine.getPlayers())
    {
        cout << "========================================================" << endl;
        cout << *p << endl;
        cout << "Strategy was: " << p->getPlayerStrategy()->getStrategyName() << endl;
        cout << "========================================================" << endl;
    }

    for(Player* p : engine.getEliminatedPlayers())
    {
        cout << "========================================================" << endl;
        cout << *p << endl;
        cout << "Strategy was: " << p->getPlayerStrategy()->getStrategyName() << endl;
        cout << "========================================================" << endl;
    }
}
