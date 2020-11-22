#include <iostream>
#include "Common\GameEngine.h"

using namespace std;

int main() {
    GameEngine* engine = new GameEngine();

    engine->main();

    delete engine;
}
