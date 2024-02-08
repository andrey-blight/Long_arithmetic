cmake_minimum_required(VERSION 3.8)
project(Long_arithmetic)
set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES main.cpp)
add_executable(long_arithmetic_run ${SOURCE_FILES})
add_subdirectory(src)

target_link_libraries(long_arithmetic_run PRIVATE long_arithmetic_src)

add_subdirectory(test)