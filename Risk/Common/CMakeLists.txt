set(SOURCES
        Cards.cpp
        Map.cpp
        MapLoader.cpp
        Player.cpp
        Util.cpp
        Orders.cpp
        GameEngine.cpp
        GameObservers.cpp
        PlayerStrategies.cpp)
set(HEADERS
        Cards.h
        Map.h
        MapLoader.h
        Player.h
        Util.h
        Orders.h
        GameEngine.h
        GameObservers.h
        PlayerStrategies.h)

add_library(Common STATIC ${SOURCES} ${HEADERS})
add_executable(CommonLib Main.cpp)
target_link_libraries(CommonLib Common)