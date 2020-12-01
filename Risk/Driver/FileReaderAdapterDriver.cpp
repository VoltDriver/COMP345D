#include "Common/MapLoader.h"

int main() {
    MapLoader loader = MapLoader();
    ConquestFileReader conquestLoader = ConquestFileReader();

    auto adapter = ConquestFileReaderAdapter(&conquestLoader);

    cout << "\n*********** Tests with Adapter: Can read Conquest maps ***********" << endl;

    cout << "\n*********** Test1: Loaded conquest map successfully ***********" << endl;
    try {
        Map *map = adapter.parse("../Resource/valid_conquest.map", true);
        delete map;
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    cout << "\n*********** Test2: invalid_conquest invalid error ***********" << endl;
    try {
        Map *map = adapter.parse("../Resource/invalid_conquest.map", true);
        delete map;
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    cout << "\n*********** Tests with MapLoader: Can still read normal Domination maps ***********" << endl;

    cout << "\n*********** Test1: Loaded Europa map successfully ***********" << endl;
    try {
        Map *map = loader.parse("../Resource/test_success1.map", true);
        delete map;
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    cout << "\n*********** Test2: Loaded Brazil map successfully ***********" << endl;
    try {
        Map *map = loader.parse("../Resource/test_success2.map", true);
        delete map;
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    return 0;
}