#include "Common/MapLoader.h"

int main() {
    MapLoader loader = MapLoader();
    ConquestFileReader conquestLoader = ConquestFileReader();

    auto adapter = ConquestFileReaderAdapter(&conquestLoader);

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

    return 0;
}