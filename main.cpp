#include "LongNumber.h"
#include <iostream>

int main() {
    LongNumber a = 0.000101_ln;
    std::cout<< a.to_string();
}