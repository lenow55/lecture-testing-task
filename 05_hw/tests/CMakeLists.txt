# GTest include code would
# go somewhere in here

find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(stack_test stack_test.cpp)

target_link_libraries(stack_test
  PRIVATE
  GTest::gtest_main
  stack_lib
)

gtest_discover_tests(stack_test)
