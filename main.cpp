#include "LongNumber.h"
#include <iostream>

int main() {
    LongNumber a("1");
    LongNumber b("0.999");
    std::cout.setf(std::ios::fixed);
    std::cout.precision(10);
    std::cout << (a - b).to_string();
}