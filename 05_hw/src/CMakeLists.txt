add_library(stack_lib stack.c)

target_include_directories(stack_lib PUBLIC .)

add_executable(main main.c)
target_compile_options(stack_lib PRIVATE)
if(STACKLIB_COVERAGE)
    target_link_libraries(main stack_lib gcov)
else()
    target_link_libraries(main stack_lib)
endif()
