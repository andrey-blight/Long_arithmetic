#ifndef LONG_ARITHMETIC_LONGNUMBER_H
#define LONG_ARITHMETIC_LONGNUMBER_H

#include <utility>
#include <vector>
#include <string>

namespace long_arithmetic {
/**
 * Класс длинное число. Будем представлять длинное число в виде (-1/1)*0.d1d2d3d4d5*(10^exp)
 * Точность будет равна max(size(digits) - exp, 0)
 * @example main.cpp
 */
    class LongNumber {
    private:
        std::vector<int> digits;
        unsigned long long exp{};
        short sgn{};
        unsigned long long accuracy = 1000;

        LongNumber(std::vector<int> digits, unsigned long long exp, short sgn) : digits(std::move(digits)), exp(exp),
                                                                                 sgn(sgn) {}


        void delete_zeroes();

    public:
        explicit LongNumber(const std::string &s);

        void set_accuracy(unsigned long long accuracy);

        std::string to_string();

        LongNumber inverse() const;

        bool operator==(const LongNumber &another) const;

        bool operator!=(const LongNumber &another) const;

        bool operator>(const LongNumber &another) const;

        bool operator<(const LongNumber &another) const;

        bool operator>=(const LongNumber &another) const;

        bool operator<=(const LongNumber &another) const;

        LongNumber operator-() const;

        LongNumber operator+(const LongNumber &other) const;

        LongNumber operator-(const LongNumber &other) const;

        LongNumber operator*(const LongNumber &long_number) const;

        LongNumber operator/(const LongNumber &other) const;
    };

    LongNumber operator ""_ln(const char *s);
}
#endif
