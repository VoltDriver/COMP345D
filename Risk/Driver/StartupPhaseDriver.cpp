#include "Common/GameEngine.h"

#include <iostream>

using namespace std;

int main() {

    GameEngine *engine = new GameEngine;
    engine->gameStart_Auto();
    engine->startupPhase();

    return 0;
}