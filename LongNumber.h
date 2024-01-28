#ifndef LONG_ARITHMETIC_LONGNUMBER_H
#define LONG_ARITHMETIC_LONGNUMBER_H

#include <vector>
#include <string>

/**
 * Класс длинное число. Будем представлять длинное число в виде (-1/1)*0.d1d2d3d4d5*(10^exp)
 * Точность будет равна max(size(digits) - exp, 0)
 * @example main.cpp
 */
class LongNumber {
private:
    std::vector<short> digits;
    unsigned long long exp{};
    unsigned long long precision{};
    short sgn{};
public:
    explicit LongNumber(const std::string &s);

    std::string to_string();
};

#endif
