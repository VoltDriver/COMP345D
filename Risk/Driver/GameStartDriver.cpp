#include "Common/GameEngine.h"

int main() {
    GameEngine *engine = new GameEngine;

    try {
        engine->gameStart(true);
    } catch (exception &e) {
        cout << "Invalid Map provided, the game will now terminate." << endl;
    };

    delete engine;

    engine = new GameEngine;

    cout << "\n\n========= Running auto initializer ==========" << endl;

    try {
        engine->gameStart_Auto();
    } catch (exception &e) {
        cout << "Invalid Map provided, the game will now terminate." << endl;
    };


    return 0;
}