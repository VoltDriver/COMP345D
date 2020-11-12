#include <iostream>
#include "Common\GameEngine.h"
#include "Common\GameObservers.h"

using namespace std;

int main() {
    cout << "test" << endl;

    GameEngine *engine = new GameEngine;
    engine->gameStart();
    PhaseObserver *phaseView = new PhaseObserver(engine);


}
