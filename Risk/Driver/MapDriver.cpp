#include <iostream>

#include "Common/Map.h"
#include "Common/MapLoader.h"

int main() {
    Map *map1 = new Map();
    Map *map2 = new Map();
    Map *map3 = new Map();
    Map *map4 = new Map();

    MapLoader loader1 = MapLoader();
    cout << "\n*********** Test1: Map is not connected graph ***********\n" << endl;
    try {
        *map1 = loader1.parse("../Resource/test_unreachable_territory.map");
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    MapLoader loader2 = MapLoader();
    cout << "\n*********** Test2: Continents are not a connected subgraph ***********\n" << endl;
    try {
        *map2 = loader2.parse("../Resource/test_unreachable_continent.map");
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    MapLoader loader3 = MapLoader();
    cout << "\n*********** Test5: Territories do not have unique continents (duplicate territory) ***********\n" << endl;
    try {
        *map3 = loader3.parse("../Resource/test_duplicate_territory.map");
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    MapLoader loader4 = MapLoader();
    cout << "\n*********** Test4: Loaded Europa map successfully ***********\n" << endl;
    try {
        *map4 = loader4.parse("../Resource/test_success1.map");
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    return 0;
}
