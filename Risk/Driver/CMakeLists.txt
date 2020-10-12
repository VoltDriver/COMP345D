include_directories(..)

# Add driver files here and link to Common library
add_executable(CardsDriver CardsDriver.cpp)
target_link_libraries(CardsDriver Common)

add_executable(MapLoaderDriver MapLoaderDriver.cpp)
target_link_libraries(MapLoaderDriver Common)

add_executable(MapDriver MapDriver.cpp)
target_link_libraries(MapDriver Common)

add_executable(PlayerDriver PlayerDriver.cpp)
target_link_libraries(PlayerDriver Common)

add_executable(OrdersDriver OrdersDriver.cpp)
target_link_libraries(OrdersDriver Common)