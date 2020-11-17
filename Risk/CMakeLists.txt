cmake_minimum_required(VERSION 3.8)
project(COMP345RISK CXX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Common)
add_subdirectory(Driver)

# Delete Resource directory if it already exists to prevent zombie files
file(REMOVE_RECURSE ${CMAKE_CURRENT_BINARY_DIR}/Resource)
# Copy Resource directory to output binary
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Resource)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Resource DESTINATION ${CMAKE_CURRENT_BINARY_DIR})