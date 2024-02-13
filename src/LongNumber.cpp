#include "LongNumber.h"
#include <algorithm>

namespace long_arithmetic {
/**
 * Удаляет все ведущие нули и замыкающие лишние нули после запятой
 */
    void LongNumber::delete_zeroes() {
        if (digits.empty()) {
            exp = 0;
            return;
        }
        long long start_index = 0;
        for (int digit: digits) { // Delete starting zeroes
            if (digit != 0 || exp == 0) {
                break;
            }
            ++start_index;
            --exp;
        }
        unsigned long long end_index = digits.size() - 1;
        while (end_index != 0) { // Delete ending zeroes
            if (end_index < exp + start_index || digits[end_index] != 0) {
                break;
            }
            --end_index;
            if (end_index == 0) {
                break;
            }
        }
        auto start = digits.begin() + start_index; // resize digits vector
        auto end = digits.begin() + (long long) end_index + 1;
        digits.resize(end - start);
        copy(start, end, digits.begin());

        if (digits.empty() && sgn == -1) { // make -0 to +0
            sgn = 1;
        }

        if (accuracy > 0 && digits.size() - exp > accuracy) {
            digits = std::vector<int>(digits.begin(), digits.begin() + (long) exp + (long) accuracy);
        }
    }

    void LongNumber::set_accuracy(unsigned long long my_accuracy) {
        accuracy = my_accuracy;
        if (digits.size() - exp > accuracy) {
            digits = std::vector<int>(digits.begin(), digits.begin() + (long) exp + (long) accuracy);
        }
    }

/**
 * Строим длинное число с плавающей точкой из строки
 * @param s строка в виде числа с плавающей точкой
 * @return LongNumber
 */
    LongNumber::LongNumber(const std::string &s) {

        sgn = 1; // assume that the number is positive
        short start_index = 0;
        bool has_dot = false;

        for (unsigned long long i = 0; i < s.size(); ++i) { // check string is correct and save some information
            char ch = s[i];

            if (ch == '-' || ch == '+') {
                if (i != 0) { // if +/- not at the beginning throw exception
                    exit(1);
                }
                if (ch == '-') { // if the ch '-', sgn negative
                    sgn = -1;
                }
                start_index = 1; // digits will start at 1
                continue;
            }

            if (ch == '.') {
                if (has_dot) { // if already has dot throw exception
                    exit(1);
                }
                has_dot = true;
                continue;
            }

            if (ch > '9' || ch < '0') { // throw exception if ch isn't a number
                exit(1);
            }
        }

        // save how many digits number will have
        digits.resize(s.size() - start_index - (int) has_dot);
        exp = 0;
        has_dot = false;
        for (unsigned long long i = start_index; i < s.size(); ++i) {
            char ch = s[i];

            if (ch == '.') {
                has_dot = true;
                continue;
            }

            digits[i - (int) has_dot - start_index] = ch - '0';
            if (!has_dot) {
                ++exp; // if already has a dot we don't need to increase by tan.
            }
        }
        delete_zeroes(); // Delete extra zeroes
    }

/**
 * Приведение длинного числа в виде строки
 * @return Строка длинного числа
 */
    std::string LongNumber::to_string() {
        std::string s;

        if (sgn == 1) { // Add sign to beginning
            s = "+";
        } else {
            s = "-";
        }

        if (exp == 0) {
            s += "0.";
        }

        for (unsigned long long i = 0; i < digits.size(); ++i) {
            s += std::to_string(digits[i]); // Append a digit to string
            if (exp != 0 && i == exp - 1) {
                s += ".";
            }
        }

        return s;
    }

/**
 * Оператор равно для двух длинных чисел
 * @return a==b true/false
 */
    bool LongNumber::operator==(const LongNumber &another) const {
        if (sgn != another.sgn) {
            return false;
        }
        if (exp != another.exp) {
            return false;
        }
        if (digits != another.digits) {
            return false;
        }
        return true;
    }

/**
 * Оператор неравно для двух длинных чисел
 * @return a!=b true/false
 */
    bool LongNumber::operator!=(const LongNumber &another) const {
        return !(*this == another);
    }

/**
 * Оператор больше для двух длинных чисел
 * @return a>b true/false
 */
    bool LongNumber::operator>(const LongNumber &another) const {
        if (sgn != another.sgn) { // if numbers have different sign return sign(a) > sign(b)
            return sgn > another.sgn;
        }

        if (exp != another.exp) {// Positive numbers have different exponents. So we can find more one.
            if (sgn == 1) {
                return exp > another.exp;
            }
            return exp < another.exp;
        }

        // check every digit by min len
        for (int i = 0; i < std::min(digits.size(), another.digits.size()); ++i) {
            if (digits[i] != another.digits[i]) {
                if (sgn == 1) {
                    return digits[i] > another.digits[i];
                }
                return digits[i] < another.digits[i];
            }
        }

        // if digits equal we check first more than second.
        return digits.size() > another.digits.size();
    }

/**
 * Оператор меньше для двух длинных чисел
 * @return a<b true/false
 */
    bool LongNumber::operator<(const LongNumber &another) const {
        return !(*this > another || *this == another);
    }


/**
 * Оператор больше или равно для двух длинных чисел
 * @return a>=b true/false
 */
    bool LongNumber::operator>=(const LongNumber &another) const {
        return (*this == another || *this > another);
    }

/**
 * Оператор больше или равно для двух длинных чисел
 * @return a<=b true/false
 */
    bool LongNumber::operator<=(const LongNumber &another) const {
        return (*this == another || *this < another);
    }

/**
 * Унарный минус для длинного числа, возвращает то же число умноженное на -1
 * @return -a
 */
    LongNumber LongNumber::operator-() const {
        return {digits, exp, static_cast<short>(-sgn)};
    }

    LongNumber LongNumber::operator+(const LongNumber &other) const {
        if (sgn != other.sgn) {
            if (sgn == -1) {
                return other - (-(*this));
            }
            return *this - (-other);
        }

        unsigned long long combined_exp = std::max(exp, other.exp);
        unsigned long long combined_fractional = std::max(digits.size() - exp, other.digits.size() - other.exp);
        std::vector<int> digits_1(combined_exp + combined_fractional);
        std::vector<int> digits_2(combined_exp + combined_fractional);
        std::vector<int> digits_res(combined_exp + combined_fractional + 1);
        for (unsigned long long i = 0; i < combined_exp; ++i) { // aligning the tens
            if (i < combined_exp - exp) {
                digits_1[i] = 0;
            } else {
                digits_1[i] = digits[i - (combined_exp - exp)];
            }
            if (i < combined_exp - other.exp) {
                digits_2[i] = 0;
            } else {
                digits_2[i] = other.digits[i - (combined_exp - other.exp)];
            }
            digits_res[i] = 0;
        }

        for (unsigned long long i = 0; i < combined_fractional; ++i) { // align the fractional part
            if (exp + i >= digits.size()) {
                digits_1[combined_exp + i] = 0;
            } else {
                digits_1[combined_exp + i] = digits[exp + i];
            }
            if (other.exp + i >= other.digits.size()) {
                digits_2[combined_exp + i] = 0;
            } else {
                digits_2[combined_exp + i] = other.digits[other.exp + i];
            }
            digits_res[combined_exp + i] = 0;
        }
        digits_res[combined_exp + combined_fractional] = 0;

        unsigned long long i = combined_exp + combined_fractional - 1;
        while (true) {
            digits_res[i + 1] += digits_1[i] + digits_2[i];
            digits_res[i] += digits_res[i + 1] / 10;
            digits_res[i + 1] %= 10;

            if (i == 0) {
                break;
            }
            --i;
        }

        LongNumber res(digits_res, combined_exp + 1, sgn);
        res.set_accuracy(accuracy);
        res.delete_zeroes();
        return res;
    }

    LongNumber LongNumber::operator-(const LongNumber &other) const {
        if (sgn != other.sgn) {
            return *this + (-other);
        }
        if (sgn == -1 && other.sgn == -1) {
            return (-other) - (-(*this));
        }

        unsigned long long combined_exp = std::max(exp, other.exp);
        unsigned long long combined_fractional = std::max(digits.size() - exp, other.digits.size() - other.exp);
        std::vector<int> digits_1(combined_exp + combined_fractional);
        std::vector<int> digits_2(combined_exp + combined_fractional);
        std::vector<int> digits_res(combined_exp + combined_fractional);
        for (unsigned long long i = 0; i < combined_exp; ++i) { // aligning the tens
            if (i < combined_exp - exp) {
                digits_1[i] = 0;
            } else {
                digits_1[i] = digits[i - (combined_exp - exp)];
            }
            if (i < combined_exp - other.exp) {
                digits_2[i] = 0;
            } else {
                digits_2[i] = other.digits[i - (combined_exp - other.exp)];
            }
            digits_res[i] = 0;
        }

        for (unsigned long long i = 0; i < combined_fractional; ++i) { // align the fractional part
            if (exp + i >= digits.size()) {
                digits_1[combined_exp + i] = 0;
            } else {
                digits_1[combined_exp + i] = digits[exp + i];
            }
            if (other.exp + i >= other.digits.size()) {
                digits_2[combined_exp + i] = 0;
            } else {
                digits_2[combined_exp + i] = other.digits[other.exp + i];
            }
            digits_res[combined_exp + i] = 0;
        }

        bool first_more = *this > other;
        unsigned long long i = combined_exp + combined_fractional - 1;
        while (true) {
            if (first_more) {
                digits_res[i] += digits_1[i] - digits_2[i];
            } else {
                digits_res[i] += digits_2[i] - digits_1[i];
            }
            if (digits_res[i] < 0) {
                digits_res[i - 1] -= 1;
                digits_res[i] += 10;
            }

            if (i == 0) {
                break;
            }
            --i;
        }

        LongNumber res(digits_res, combined_exp, first_more ? 1 : -1);
        res.set_accuracy(accuracy);
        res.delete_zeroes();
        return res;
    }

/**
 * Умножает 2 числа типа LongNumber
 * @return a*b
 */
    LongNumber LongNumber::operator*(const LongNumber &long_number) const {
        if (digits.empty() || long_number.digits.empty()) {
            LongNumber res = 0_ln;
            return res;
        }

        std::vector<int> res_digits(digits.size() + long_number.digits.size()); // new vector size
        for (int &el: res_digits) {
            el = 0;
        }

        size_t i = long_number.digits.size() - 1;
        while (true) {
            size_t j = digits.size() - 1;
            while (true) {

                res_digits[i + j + 1] += long_number.digits[i] * digits[j]; // multiply a digit[i] and another digit[i]
                res_digits[i + j] += res_digits[i + j + 1] / 10; // if res >10 res/10 move to next ten
                res_digits[i + j + 1] %= 10; // leave only res%10 in this ten

                if (j == 0) {
                    break;
                }
                --j;
            }

            if (i == 0) {
                break;
            }
            --i;
        }

        LongNumber res{res_digits, exp + long_number.exp, (short) (sgn * long_number.sgn)};
        res.set_accuracy(accuracy);
        res.delete_zeroes(); // delete all zeroes if exist
        return res;
    }

    LongNumber LongNumber::inverse() const {
        if (digits.empty()) {
            exit(1); // dividing by zero
        }

        LongNumber n = (*this);
        n.sgn = 1; // work with plus numbers
        LongNumber num("1");
        unsigned long long res_exp = 1;
        std::vector<int> res_digits;

        while (n < num) { // multiply by 10 while n<1
            ++n.exp;
            n.digits.push_back(0);
            ++res_exp;
        }

        while (num < n) { // multiply by 10 while num<n
            ++num.exp;
            num.digits.push_back(0);
            res_digits.push_back(0);
        }

        LongNumber zero_check("0");
        unsigned long long numbers = 0;
        while (num != zero_check && numbers < accuracy) {
            int digit_now = 0;

            while (num >= n) {
                ++digit_now;
                num = num - n;
            }

            ++num.exp;
            num.digits.push_back(0);
            num.delete_zeroes();
            res_digits.push_back(digit_now);
            ++numbers;
        }
        LongNumber res(res_digits, res_exp, sgn);
        res.set_accuracy(accuracy);
        res.delete_zeroes();
        return res;
    }

    LongNumber LongNumber::operator/(const LongNumber &other) const {
        LongNumber res = *this * other.inverse();
        res.set_accuracy(accuracy);
        return res;
    }

    LongNumber operator ""_ln(const char *s) {
        LongNumber res(s);
        return res;
    }
}