cmake_minimum_required(VERSION 3.20)
project(lab3)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab3 main.cpp)

include_directories(Sequence)

add_subdirectory(Sequence)

target_link_libraries(lab3 Sequence)