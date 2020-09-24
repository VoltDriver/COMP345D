set(SOURCES
        Map.cpp
        Continent.cpp
        Country.cpp
        MapLoader.cpp
        Util.cpp)
set(HEADERS
        Map.h
        Continent.h
        Country.h
        MapLoader.h
        Util.h)

add_library(Common STATIC ${SOURCES} ${HEADERS})
add_executable(CommonLib Main.cpp)
target_link_libraries(CommonLib Common)