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

    cout << "\n\n************ Running auto initializer ************\n" << endl;
    cout << "*** Running with invalid map ***\n" << endl;

    try {
        engine->gameStart_Auto("test_bordering_territory_index_error.map", 4, true, true);
    } catch (exception &e) {
        cout << "Invalid Map provided, the game will now terminate.\n\n" << endl;
    }

    delete engine;
    engine = new GameEngine;

    cout << "*** Running with valid map ***" << endl;

    try {
        engine->gameStart_Auto();
    } catch (exception &e) {
        cout << "Invalid Map provided, the game will now terminate." << endl;
    }

    return 0;
}