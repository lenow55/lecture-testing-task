# GTest include code would
# go somewhere in here

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
  OVERRIDE_FIND_PACKAGE
)

find_package(googletest REQUIRED)

include(GoogleTest)

add_executable(stack_test stack_test.cpp)

find_program(GCOVR_EXECUTABLE gcovr)

if(STACKLIB_COVERAGE AND GCOVR_EXECUTABLE)
    message(STATUS "Измерение покрытия кода тестами включено")

    target_compile_options(stack_test PRIVATE --coverage)
    target_compile_options(stack_lib PRIVATE --coverage)

    target_link_libraries(stack_test
      PRIVATE
        GTest::gtest_main
        stack_lib
        gcov
    )

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

if(NOT STACKLIB_COVERAGE)
    target_link_libraries(stack_test
      PRIVATE
        GTest::gtest_main
        stack_lib
    )
endif()

include(CTest)

gtest_discover_tests(stack_test)
