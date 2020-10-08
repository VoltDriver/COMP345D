#include <iostream>

#include "Common/Map.h"
#include "Common/MapLoader.h"

int main() {
    cout << "\n*********** Test1: Loaded Europa map successfully ***********\n" << endl;
    try {
        Map *map = MapLoader::parse("../Resource/test_success1.map");
        delete map;
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    cout << "\n*********** Test2: Loaded Brazil map successfully ***********\n" << endl;
    try {
        Map *map = MapLoader::parse("../Resource/test_success2.map");
        delete map;
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    cout << "\n*********** Test3: Loaded Canada map successfully ***********\n" << endl;
    try {
        Map *map = MapLoader::parse("../Resource/test_success3.map");
        delete map;
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    cout << "\n*********** Test4: Map index not in order error ***********\n" << endl;
    try {
        Map *map = MapLoader::parse("../Resource/test_index_error.map");
        delete map;
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    MapLoader loader5 = MapLoader();
    cout << "\n*********** Test5: Territory with invalid continent id ***********\n" << endl;
    try {
        Map *map = MapLoader::parse("../Resource/test_invalid_continent_id.map");
        delete map;
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

//    MapLoader loader6 = MapLoader();
//    cout << "\n*********** Test6: ***********\n" << endl;
//    try {
//        loader6.parse("../Resource/test.map");
//    } catch (const std::exception &e) {
//        cout << e.what() << endl;
//    }

    cout << "\n*********** Test7: Unable to parse territories because ['Countries'] is missing or misspelled in map file ***********\n" << endl;
    try {
        Map *map = MapLoader::parse("../Resource/test_finding_territory_error.map");
        delete map;
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    return 0;
}
