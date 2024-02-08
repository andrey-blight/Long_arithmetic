#include "src/LongNumber.h"
#include <iostream>
using namespace long_arithmetic;

int main() {
    LongNumber a = 0.123_ln;

    std::cout<<a.to_string();

}