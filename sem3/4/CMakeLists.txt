cmake_minimum_required(VERSION 3.20)
project(lab3)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab3 main.cpp Dialog.cpp Dialog.h)

include_directories(Libraries)

add_subdirectory(Libraries)
add_subdirectory(Test)

target_link_libraries(lab3 Libraries)