#include <gtest/gtest.h>

#include "../src/include/LongNumber.h"

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

TEST(Long_arithmetic, delete_zeroes) {
    LongNumber a("0000.00010100000000");
    EXPECT_EQ("+0.000101", a.to_string());
}

TEST(Long_arithmetic, inverse) {
    LongNumber a("2");
    LongNumber b("0.5");
    EXPECT_EQ(a.inverse(), b);
}

TEST(Long_arithmetic, eq) {
    LongNumber a("2");
    LongNumber b("3");
    EXPECT_EQ(a == b, false);
}

TEST(Long_arithmetic, eq_1) {
    LongNumber a("2");
    LongNumber b("-3");
    EXPECT_EQ(a == b, false);
}

TEST(Long_arithmetic, eq_not) {
    LongNumber a("2");
    LongNumber b("3");
    EXPECT_EQ(a != b, true);
}

TEST(Long_arithmetic, more) {
    LongNumber a("2");
    LongNumber b("3");
    EXPECT_EQ(a > b, false);
}

TEST(Long_arithmetic, more_1) {
    LongNumber a("2");
    LongNumber b("-3");
    EXPECT_EQ(a > b, true);
}

TEST(Long_arithmetic, low) {
    LongNumber a("2");
    LongNumber b("3");
    EXPECT_EQ(a < b, true);
}

TEST(Long_arithmetic, more_eq) {
    LongNumber a("3");
    LongNumber b("3");
    EXPECT_EQ(a >= b, true);
}

TEST(Long_arithmetic, low_eq) {
    LongNumber a("4");
    LongNumber b("3");
    EXPECT_EQ(a <= b, false);
}

TEST(Long_arithmetic, sing_minus) {
    LongNumber a("4");
    LongNumber b("-4");
    EXPECT_EQ(-a, b);
}

TEST(Long_arithmetic, plus) {
    LongNumber a("4");
    LongNumber b("0.004");
    LongNumber c("4.004");
    EXPECT_EQ(a + b, c);
}

TEST(Long_arithmetic, plus_1) {
    LongNumber a("-4");
    LongNumber b("0.004");
    LongNumber c("-3.996");
    EXPECT_EQ(a + b, c);
}

TEST(Long_arithmetic, minuse) {
    LongNumber a("4");
    LongNumber b("-4");
    LongNumber c("8");
    EXPECT_EQ(a - b, c);
}

TEST(Long_arithmetic, multiply) {
    LongNumber a("3");
    LongNumber b("-4");
    LongNumber c("-12");
    EXPECT_EQ(a * b, c);
}

TEST(Long_arithmetic, ln_test) {
    LongNumber a("1");
    EXPECT_EQ(1_ln, a);
}

TEST(Long_arithmetic, divide) {
    LongNumber a("12");
    LongNumber b("-4");
    LongNumber c("-3");
    EXPECT_EQ((a / b).to_string(), c.to_string());
}

TEST(Long_arithmetic, divide_1) {
    LongNumber n = 0.1_ln;
    LongNumber a = 1_ln;
    n.set_accuracy(2);
    a.set_accuracy(2);
    EXPECT_EQ((a / n).to_string(), (9.9_ln).to_string());
}

TEST(Long_arithmetic, arctg) {
    EXPECT_EQ(calculate_arctg(1_ln / 5_ln, 1), 0.2_ln);
}