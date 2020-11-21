#include <iostream>

#include "Common/Map.h"
#include "Common/MapLoader.h"

int main() {
    MapLoader loader = MapLoader();
    cout << "\n*********** Test1: Map is not connected graph ***********\n" << endl;
    try {
        Map *map = loader.parse("../Resource/test_unreachable_territory.map", true);
        delete map;

    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    cout << "\n*********** Test2: Continents are not a connected subgraph ***********\n" << endl;
    try {
        Map *map2 = loader.parse("../Resource/test_unreachable_continent.map", true);
        delete map2;
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    cout << "\n*********** Test5: Territories do not have unique continents (duplicate territory) ***********\n" << endl;
    try {
        Map *map3 = loader.parse("../Resource/test_duplicate_territory.map", true);
        delete map3;
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    cout << "\n*********** Test4: Loaded Europa map successfully ***********\n" << endl;
    try {
        Map *map4 = loader.parse("../Resource/test_success1.map", true);
        delete map4;
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    return 0;
}
