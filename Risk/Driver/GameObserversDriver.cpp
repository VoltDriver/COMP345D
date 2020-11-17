#include <iostream>
#include "Common\GameEngine.h"
#include "Common\GameObservers.h"

using namespace std;

int main() {
    GameEngine *engine = new GameEngine;

    engine->start();

    delete engine;
}
