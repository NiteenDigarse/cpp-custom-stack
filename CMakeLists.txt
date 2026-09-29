cmake_minimum_required(VERSION 3.20)

project(CustomStack
    LANGUAGES CXX
    VERSION 1.0
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(custom_stack
    src/custom_stack.cpp
)

target_include_directories(custom_stack
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/external/custom-vector/include
)

add_executable(test_custom_stack
    tests/test_custom_stack.cpp
)

target_link_libraries(test_custom_stack
    PRIVATE
        custom_stack
)
add_executable(benchmark_custom_stack
    benchmarks/benchmark_custom_stack.cpp
)

target_link_libraries(benchmark_custom_stack
    PRIVATE
        custom_stack
)