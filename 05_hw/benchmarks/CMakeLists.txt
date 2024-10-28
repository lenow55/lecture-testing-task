include(FetchContent)

set(BENCHMARK_ENABLE_TESTING OFF)
set(ENABLE_GPROF OFF)

FetchContent_Declare(googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark
        GIT_TAG main)

FetchContent_MakeAvailable(googlebenchmark)

add_executable(stack_benchmark stack_benchmark.cpp)

target_link_libraries(stack_benchmark
  PRIVATE
    benchmark::benchmark
    stack_lib
)
