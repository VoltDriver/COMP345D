#include "Common/GameEngine.h"

#include <iostream>

using namespace std;

int main() {

    GameEngine engine = GameEngine();

    try {
        engine.main();
    } catch (exception &e) {
        cout << "Invalid Map provided, the game will now terminate." << endl;
    };

    return 0;
}