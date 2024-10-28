# GTest include code would
# go somewhere in here

find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(stack_test stack_test.cpp)

target_link_libraries(stack_test
  PRIVATE
    GTest::gtest_main
    stack_lib
    gcov
)

find_program(GCOVR_EXECUTABLE gcovr)

if(STACKLIB_COVERAGE AND GCOVR_EXECUTABLE)
    message(STATUS "Измерение покрытия кода тестами включено")

    target_compile_options(stack_test PRIVATE --coverage)
    target_compile_options(stack_lib PRIVATE --coverage)

    add_custom_target(coverage
      COMMAND
        ctest
            --test-dir ${PROJECT_BINARY_DIR}
            -T Test -T Coverage
      COMMAND
        lcov --directory ${PROJECT_BINARY_DIR}/src/
            --capture --output-file ${PROJECT_BINARY_DIR}/coverage.info
      COMMAND
        genhtml --demangle-cpp -o ${PROJECT_SOURCE_DIR}/coverage
            ${PROJECT_BINARY_DIR}/coverage.info
      )
elseif(STACKLIB_COVERAGE AND NOT GCOVR_EXECUTABLE)
    set(STACKLIB_COVERAGE OFF)
    message(WARNING
  "Для замеров покрытия кода тестами требуется программа gcovr")
endif()

include(CTest)

gtest_discover_tests(stack_test)
