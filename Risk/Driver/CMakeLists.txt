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

add_executable(GameEngineDriver GameEngineDriver.cpp)
target_link_libraries(GameEngineDriver Common)

add_executable(GameStartDriver GameStartDriver.cpp)
target_link_libraries(GameStartDriver Common)

add_executable(GameObserversDriver GameObserversDriver.cpp)
target_link_libraries(GameObserversDriver Common)

add_executable(StartupPhaseDriver StartupPhaseDriver.cpp)
target_link_libraries(StartupPhaseDriver Common)

add_executable(MainGameLoopDriver MainGameLoopDriver.cpp)
target_link_libraries(MainGameLoopDriver Common)

add_executable(FileReaderAdapterDriver FileReaderAdapterDriver.cpp)
target_link_libraries(FileReaderAdapterDriver Common)

add_executable(PlayerStrategiesDriver PlayerStrategiesDriver.cpp)
target_link_libraries(PlayerStrategiesDriver Common)