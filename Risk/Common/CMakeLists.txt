set(SOURCES
        Map.cpp
        Continent.cpp
        Country.cpp
        MapLoader.cpp)
set(HEADERS
        Map.h
        Continent.h
        Country.h
        MapLoader.h)

add_library(Common STATIC ${SOURCES} ${HEADERS})
add_executable(CommonLib Main.cpp)
target_link_libraries(CommonLib Common)