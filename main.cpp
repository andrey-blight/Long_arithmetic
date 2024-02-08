#include "LongNumber.h"
#include <iostream>

int main() {
    LongNumber a("0000.00010100000000");
    std::cout<< a.to_string();
}