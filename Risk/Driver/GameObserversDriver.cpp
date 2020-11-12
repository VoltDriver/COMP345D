#include <iostream>
#include "Common\GameEngine.h"
#include "Common\GameObservers.h"

using namespace std;

int main() {
    GameEngine *engine = new GameEngine;

    engine->gameStart();

    if(engine->getPhase_observer_flag()) {
        PhaseObserver *phaseView = new PhaseObserver(engine);
    }
    if(engine->getStat_observer_flag()) {

    }

    engine->mainGameLoop();


}
