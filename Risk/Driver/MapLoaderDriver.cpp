#include <iostream>

#include "Common/Map.h"
#include "Common/MapLoader.h"

int main() {
    MapLoader loader = MapLoader();
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

    cout << "\n*********** Test3: Loaded Canada map successfully ***********" << endl;
    try {
        Map *map = loader.parse("../Resource/test_success3.map", true);
        delete map;
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    cout << "\n*********** Test4: Map index not in order error ***********" << endl;
    try {
        Map *map = loader.parse("../Resource/test_index_error.map", true);
        delete map;
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    cout << "\n*********** Test5: Territory with invalid continent id ***********" << endl;
    try {
        Map *map = loader.parse("../Resource/test_invalid_continent_id.map", true);
        delete map;
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    cout << "\n*********** Test6: Initial territory index out of range ***********" << endl;
    try {
        Map *map = loader.parse("../Resource/test_initial_territory_index_error.map", true);
        delete map;
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    cout << "\n*********** Test7: Bordering territory id doesn't exist ***********" << endl;
    try {
        Map *map = loader.parse("../Resource/test_bordering_territory_index_error.map", true);
        delete map;
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    cout << "\n*********** Test8: Missing continent data error ***********" << endl;
    try {
        Map *map = loader.parse("../Resource/test_missing data.map", true);
        delete map;
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    cout << "\n*********** Test9: Missing border data ***********" << endl;
    try {
        Map *map = loader.parse("../Resource/test_missing_border_info.map", true);
        delete map;
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    cout << "\n*********** Test10: Unable to parse territories because ['Countries'] is missing or misspelled in map file ***********" << endl;
    try {
        Map *map = loader.parse("../Resource/test_finding_territory_error.map", true);
        delete map;
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    return 0;
}
