cmake_minimum_required(VERSION 3.19)
project(2)

set(CMAKE_CXX_STANDARD 17)

add_executable(2 main.cpp)

include_directories(Ciccoida)

add_subdirectory(Ciccoida)
add_subdirectory(Test)

target_link_libraries(2 Ciccoida)