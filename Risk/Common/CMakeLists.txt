set(SOURCES
        Map.cpp
        MapLoader.cpp
        Util.cpp
        Player.cpp)
set(HEADERS
        Map.h
        MapLoader.h
        Util.h
        Player.h)

add_library(Common STATIC ${SOURCES} ${HEADERS})
add_executable(CommonLib Main.cpp)
target_link_libraries(CommonLib Common)