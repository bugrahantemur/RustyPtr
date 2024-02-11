cmake_minimum_required(VERSION 3.27)

add_executable(RustyPtr_test tests.cpp)
target_link_libraries(RustyPtr_test GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(RustyPtr_test)
