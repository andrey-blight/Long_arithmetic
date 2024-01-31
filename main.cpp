#include "LongNumber.h"
#include <iostream>

int main() {
    LongNumber a("4659.61");
    LongNumber b("645.1357");
    std::cout.setf(std::ios::fixed);
    std::cout.precision(10);
    std::cout << (a + b).to_string();
}