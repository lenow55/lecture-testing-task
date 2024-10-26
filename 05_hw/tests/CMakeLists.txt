# GTest include code would
# go somewhere in here

add_executable(stack_test stack_test.cpp)

target_link_libraries(stack_test PRIVATE stack_lib)
