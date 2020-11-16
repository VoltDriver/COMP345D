#include <iostream>
#include "Common\GameEngine.h"
#include "Common\GameObservers.h"

using namespace std;

int main() {
    GameEngine *engine = new GameEngine;

    try {
        engine->gameStart(true);
    }
    catch (exception &e) {
        cout << "Invalid Map provided, the game will now terminate." << endl;
    }

    if(engine->getPhase_observer_flag()) {
        PhaseObserver *phaseView = new PhaseObserver(engine);
    }
    if(engine->getStat_observer_flag()) {
        StatsObserver *statsView = new StatsObserver(engine);
    }

    engine->startupPhase();

    engine->mainGameLoop();

}
