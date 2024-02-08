#include <gtest/gtest.h>

#include "LongNumber.h"


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
    LongNumber b("-4");
    LongNumber c("0");
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

TEST(Long_arithmetic, divide) {
    LongNumber a("12");
    LongNumber b("-4");
    LongNumber c("-3");
    EXPECT_EQ(a / b, c);
}

