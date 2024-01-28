#include "LongNumber.h"

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
        s += std::to_string(digits[i]); // Append digit to string
        if (exp != 0 && i == exp - 1) {
            s += ".";
        }
    }

    return s;
}
