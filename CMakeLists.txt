cmake_minimum_required(VERSION 3.17)
project(simpl_demo)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(src)
add_subdirectory(test)

enable_testing()

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC simpl_lib)
