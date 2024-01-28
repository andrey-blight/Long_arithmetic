#include "LongNumber.h"
#include <iostream>

int main() {
    LongNumber long_number("+0.12324");
    std::cout << long_number.to_string();
}