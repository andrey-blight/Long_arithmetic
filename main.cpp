#include "src/include/LongNumber.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

using namespace long_arithmetic;

LongNumber calculate_arctg(const LongNumber &x, unsigned long long accuracy) {
    LongNumber res = 0_ln;

    std::string str_lower_bound = "0.";
    for (int i = 0; i < accuracy - 1; ++i) {
        str_lower_bound += '0';
    }
    str_lower_bound += "1";
    LongNumber lower_bound(str_lower_bound);

    LongNumber zero("0");
    int sign = 1;
    long long degree = 1;
    while (true) {
        LongNumber power = 1_ln;
        for (int i = 0; i < degree; ++i) {
            power = power * x;
        }
        LongNumber denominator(std::to_string(degree));
        denominator.set_accuracy(accuracy);
        power.set_accuracy(accuracy);
        LongNumber fraction = power / denominator;
        fraction.set_accuracy(accuracy);
        if (fraction < lower_bound) {
            break;
        }
        if (sign == 1) {
            res = res + fraction;
        } else {
            res = res - fraction;
        }
        sign *= -1;
        degree += 2;
    }
    return res;
}

LongNumber calculate_pi(unsigned long long accuracy) {
    const std::clock_t c_start = std::clock();
    auto t_start = std::chrono::high_resolution_clock::now();

    LongNumber ln_5 = 5_ln;
    LongNumber ln_239 = 239_ln;
    LongNumber ln_1 = 1_ln;
    ln_5.set_accuracy(accuracy);
    ln_239.set_accuracy(accuracy);
    ln_1.set_accuracy(accuracy);
    LongNumber first_arc = calculate_arctg(ln_1 / ln_5, accuracy);
    LongNumber second_arc = calculate_arctg(ln_1 / ln_239, accuracy);
    LongNumber pi = first_arc * 16_ln - 4_ln * second_arc;

    const std::clock_t c_end = std::clock();
    const auto t_end = std::chrono::high_resolution_clock::now();

    std::cout << std::fixed << std::setprecision(2) << "CPU time used: "
              << 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC << "ms\n";
    return pi;
}

int main() {
    LongNumber pi = calculate_arctg(1_ln/5_ln, 6);
    std::cout << pi.to_string();
}