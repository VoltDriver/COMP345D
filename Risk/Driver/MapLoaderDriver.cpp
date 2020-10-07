#include <iostream>

#include "Common/Map.h"
#include "Common/MapLoader.h"

int main() {
    MapLoader loader1 = MapLoader();
    cout << "\n*********** Test1: loaded Europa map successfully ***********\n" << endl;
    try {
        loader1.parse("../Resource/test_success1.map");
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    MapLoader loader2 = MapLoader();
    cout << "\n*********** Test2: loaded Brasil map successfully ***********\n" << endl;
    try {
        loader2.parse("../Resource/test_success2.map");
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    MapLoader loader3 = MapLoader();
    cout << "\n*********** Test3: loaded Canada map successfully ***********\n" << endl;
    try {
        loader3.parse("../Resource/test_success3.map");
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    MapLoader loader4 = MapLoader();
    cout << "\n*********** Test4: map index not in order error ***********\n" << endl;
    try {
        loader4.parse("../Resource/test_index_error.map");
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

//    MapLoader loader5 = MapLoader();
//    cout << "\n*********** Test:  ***********\n" << endl;
//    try {
//        loader5.parse("../Resource/test_finding_territory_error.map");
//    } catch (const std::exception &e) {
//        cout << e.what() << endl;
//    }
    return 0;
}
