set(SOURCES
        Cards.cpp
        Map.cpp
        MapLoader.cpp
        Player.cpp
        Util.cpp)
set(HEADERS
        Cards.h
        Map.h
        MapLoader.h
        Player.h
        Util.h)

add_library(Common STATIC ${SOURCES} ${HEADERS})
add_executable(CommonLib Main.cpp)
target_link_libraries(CommonLib Common)