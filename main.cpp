#include "LongNumber.h"
#include <iostream>

int main() {
    LongNumber input("+0001234.000001112000");
    LongNumber a("879244285724852409.24824024582495872945");
    LongNumber b("38012939104.301489358935");
    double d = 465.975 * 971.1241;
    std::cout.setf(std::ios::fixed);
    std::cout.precision(10);
    std::cout << (a * b).to_string() << std::endl;
    std::cout << d;
}