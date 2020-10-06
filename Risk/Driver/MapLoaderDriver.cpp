#include <iostream>

#include "Common/Map.h"
#include "Common/MapLoader.h"

int main() {
    MapLoader loader1 = MapLoader();
    cout << " *********** Test1: loading map successfully ***********\n" << endl;
    try {
        loader1.parse("../Resource/test1.map");
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    MapLoader loader2 = MapLoader();
    cout << "*********** Test2: loading different map successfully ***********\n" << endl;
    try {
        loader2.parse("../Resource/test2.map");
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    MapLoader loader3 = MapLoader();
    cout << "*********** Test3: map index not in order error ***********\n" << endl;
    try {
        loader3.parse("../Resource/test3_index_error.map");
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    MapLoader loader_test = MapLoader();
    cout << "*********** Test: TEST ***********\n" << endl;
    try {
        loader_test.parse("../Resource/test7_unreachable_continent.map");
    } catch (const std::exception &e) {
        cout << e.what() << endl;
    }

    return 0;
}
