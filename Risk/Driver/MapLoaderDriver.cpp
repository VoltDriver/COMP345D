#include <iostream>

#include "Common/Map.h"
#include "Common/MapLoader.h"

int main() {
    MapLoader loader1 = MapLoader();
    cout << "\n*********** Test1: Loaded Europa map successfully ***********\n" << endl;
    try {
        loader1.parse("../Resource/test_success1.map");
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    MapLoader loader2 = MapLoader();
    cout << "\n*********** Test2: Loaded Brazil map successfully ***********\n" << endl;
    try {
        loader2.parse("../Resource/test_success2.map");
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    MapLoader loader3 = MapLoader();
    cout << "\n*********** Test3: Loaded Canada map successfully ***********\n" << endl;
    try {
        loader3.parse("../Resource/test_success3.map");
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    MapLoader loader4 = MapLoader();
    cout << "\n*********** Test4: Map index not in order error ***********\n" << endl;
    try {
        loader4.parse("../Resource/test_index_error.map");
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    MapLoader loader5 = MapLoader();
    cout << "\n*********** Test5: Territory with invalid continent id ***********\n" << endl;
    try {
        loader5.parse("../Resource/test_invalid_continent_id.map");
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

    MapLoader loader7 = MapLoader();
    cout << "\n*********** Test7: Unable to parse territories because ['Countries'] is missing or misspelled in map file ***********\n" << endl;
    try {
        loader7.parse("../Resource/test_finding_territory_error.map");
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }


    return 0;
}
