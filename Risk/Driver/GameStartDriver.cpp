#include "Common/GameEngine.h"

int main() {
    GameEngine *engine = new GameEngine;

    try {
        engine->gameStart(true);
    } catch (exception &e) {
        cout << "\n\n==================================================" << endl;
        cout << "Invalid Map provided, the game will now terminate." << endl;
        cout << "==================================================" << endl;
    };

    delete engine;
    engine = new GameEngine;

    cout << "\n\n************ Running auto initializer ************\n" << endl;
    cout << "*** Running with invalid map ***\n" << endl;

    try {
        engine->gameStart_Auto("test_bordering_territory_index_error.map", 4, true, false);
    } catch (exception &e) {
        cout << "==================================================" << endl;
        cout << "Invalid Map provided, the game will now terminate." << endl;
        cout << "==================================================\n\n" << endl;
    }

    delete engine;
    engine = new GameEngine;

    cout << "*** Running with valid map ***" << endl;

    try {
        engine->gameStart_Auto();
    } catch (exception &e) {
        cout << "==================================================" << endl;
        cout << "Invalid Map provided, the game will now terminate." << endl;
        cout << "==================================================\n\n" << endl;
    }

    delete engine;
    engine = new GameEngine;

    cout << "\n\n*** Running with valid map 2 ***" << endl;

    try {
        engine->gameStart_Auto("test_success2.map", 2, false, false);
    } catch (exception &e) {
        cout << "==================================================" << endl;
        cout << "Invalid Map provided, the game will now terminate." << endl;
        cout << "==================================================\n\n" << endl;
    }

    return 0;
}