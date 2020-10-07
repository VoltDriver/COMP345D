set(SOURCES
        Map.cpp
        Continent.cpp
        Territory.cpp
        MapLoader.cpp
        Util.cpp
        Player.cpp)
set(HEADERS
        Map.h
        Continent.h
        Territory.h
        MapLoader.h
        Util.h
        Player.h)

add_library(Common STATIC ${SOURCES} ${HEADERS})
add_executable(CommonLib Main.cpp)
target_link_libraries(CommonLib Common)