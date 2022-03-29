cmake_minimum_required(VERSION 3.20)
project(External)

set(CMAKE_CXX_STANDARD 17)

add_executable(External main.cpp Dialog.h Dialog.cpp External.cpp External.h)

include_directories(lab3_library)

add_subdirectory(lab3_library)

target_link_libraries(External lab3_library)