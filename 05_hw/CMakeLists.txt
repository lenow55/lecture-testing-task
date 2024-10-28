cmake_minimum_required(VERSION 3.10)
project(stack)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)

if(CMAKE_EXPORT_COMPILE_COMMANDS)
    find_program(CLANG_EXECUTABLE clang)
    add_custom_target(analyze
        COMMAND
          analyze-build --cdb ${PROJECT_BINARY_DIR}/compile_commands.json
            --use-analyzer ${CLANG_EXECUTABLE}
            --output ${PROJECT_BINARY_DIR}/analyzer
    )
endif()

