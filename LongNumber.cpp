#include "LongNumber.h"

/**
 * Удаляет все ведущие нули и замыкающие лишние нули после запятой
 */
void LongNumber::delete_zeroes() {
    long long start_index = 0;
    for (int digit: digits) { // Delete starting zeroes
        if (digit != 0 || exp == 0) {
            break;
        }
        ++start_index;
        --exp;
    }
    unsigned long long end_index = digits.size() - 1;
    while (true) { // Delete ending zeroes
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
 * Унарный минус для длинного числа, возвращает то же число умноженное на -1
 * @return -a
 */
LongNumber LongNumber::operator-() const {
    return {digits, exp, static_cast<short>(-sgn)};
}

/**
 * Умножает 2 числа типа LongNumber
 * @return a*b
 */
LongNumber LongNumber::operator*(const LongNumber &long_number) const {
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
    res.delete_zeroes(); // delete all zeroes if exist
    return res;
}
