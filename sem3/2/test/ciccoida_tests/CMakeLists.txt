include_directories(${gtest_SOURCE_DIR}/include${gtest_SOURCE_DIR})

add_executable(runCiccoidaTests Test.cpp)

target_link_libraries(runCiccoidaTests gtest gtest_main)
target_link_libraries(runCiccoidaTests Ciccoida)
