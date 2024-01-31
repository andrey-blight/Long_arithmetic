#include "LongNumber.h"
#include <iostream>

int main() {
    LongNumber a("1");
    LongNumber b("10");
    LongNumber c("2");
    std::cout.setf(std::ios::fixed);
    std::cout.precision(10);
    std::cout << (a/a).to_string();
}