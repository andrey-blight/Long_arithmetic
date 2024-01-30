#include "LongNumber.h"
#include <iostream>

int main() {
//    LongNumber input("+0001234.000001112000");
    LongNumber a("-000000.00000000");
    LongNumber b("0000.00000");
    std::cout.setf(std::ios::fixed);
    std::cout.precision(10);
    std::cout << a.to_string() << std::endl << b.to_string();
}