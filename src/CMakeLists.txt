project(Long_arithmetic_lib)
set(HEADER_FILE include/LongNumber.h)
set(SOURCE_FILE LongNumber.cpp)

add_library(long_arithmetic_src ${HEADER_FILE} ${SOURCE_FILE})