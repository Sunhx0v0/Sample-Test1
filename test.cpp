#include "pch.h"
#include<cmath>

const double M_PI = 3.1415926535;
// 考虑到精度问题,定义一个宏来比较浮点数
#define EXPECT_FLOAT_NEAR(a, b, epsilon) \
    EXPECT_TRUE(abs((a) - (b)) <= (epsilon)) << "Expected: " #a " == " #b ", but got " << a << " and " << b;

// 对库函数的测试
// 测试 sin 函数
TEST(MathFunctionsTest, SinTest) {
    // 测试特殊角度的正弦值
    EXPECT_FLOAT_NEAR(sin(0.0), 0.0, 1e-6);
    EXPECT_FLOAT_NEAR(sin(M_PI / 2), 1.0, 1e-6);
    EXPECT_FLOAT_NEAR(sin(M_PI), 0.0, 1e-6);
    EXPECT_FLOAT_NEAR(sin(3 * M_PI / 2), -1.0, 1e-6);
}

// 测试 cos 函数
TEST(MathFunctionsTest, CosTest) {
    // 测试特殊角度的余弦值
    EXPECT_FLOAT_NEAR(cos(0.0), 1.0, 1e-6);
    EXPECT_FLOAT_NEAR(cos(M_PI / 2), 0.0, 1e-6);
    EXPECT_FLOAT_NEAR(cos(M_PI), -1.0, 1e-6);
    EXPECT_FLOAT_NEAR(cos(3 * M_PI / 2), 0.0, 1e-6);
}

// 测试 sqrt 函数
TEST(MathFunctionsTest, SqrtTest) {
    // 测试正数、零以及负数（应该抛出 domain error）
    EXPECT_FLOAT_NEAR(sqrt(4.0), 2.0, 1e-6);
    EXPECT_FLOAT_NEAR(sqrt(9.0), 3.0, 1e-6);
    EXPECT_FLOAT_NEAR(sqrt(0.0), 0.0, 1e-6);

    // 检查当输入为负数时是否抛出异常
    EXPECT_TRUE(std::isnan(sqrt(-1)))<< "should return NaN but return "<< sqrt(-1);
}

// 测试 pow 函数的基本功能
TEST(PowFunctionTest, BasicFunctionality) {
    // 正数底数和指数
    EXPECT_FLOAT_NEAR(pow(2.0, 3.0), 8.0, 1e-6);
    EXPECT_FLOAT_NEAR(pow(5.0, 2.0), 25.0, 1e-6);

    // 底数为 1
    EXPECT_FLOAT_NEAR(pow(1.0, 100.0), 1.0, 1e-6);
}

// 测试 pow 函数的边界条件
TEST(PowFunctionTest, EdgeCases) {
    // 指数为 0
    EXPECT_FLOAT_NEAR(pow(10.0, 0.0), 1.0, 1e-6);
    EXPECT_FLOAT_NEAR(pow(-10.0, 0.0), 1.0, 1e-6);

    // 底数为 0
    EXPECT_FLOAT_NEAR(pow(0.0, 2.0), 0.0, 1e-6);
    EXPECT_FLOAT_NEAR(pow(0.0, 100.0), 0.0, 1e-6);

    // 指数为 1
    EXPECT_FLOAT_NEAR(pow(7.0, 1.0), 7.0, 1e-6);
    EXPECT_FLOAT_NEAR(pow(-7.0, 1.0), -7.0, 1e-6);
}

// 测试 pow 函数的异常情况
TEST(PowFunctionTest, ExceptionalCases) {
    // 负数底数和非整数指数
    EXPECT_FLOAT_NEAR(pow(-1.0, 3.0), -1.0, 1e-6);
    EXPECT_FLOAT_NEAR(pow(-2.0, 3.0), -8.0, 1e-6);
    EXPECT_TRUE(std::isnan(pow(-2.0, 0.5))) << "should return NaN but return " << pow(-2.0, 0.5);

    // 底数为 0 且指数为负数
    //EXPECT_TRUE(std::isnan(pow(0.0, -1.0))) << "should return NaN but return "<<pow(0.0,-1);
    EXPECT_TRUE(std::isinf(pow(0.0, -1.0)));    // 我的编译器会返回inf
}

// 测试 pow 函数的极端情况
TEST(PowFunctionTest, ExtremeCases) {
    double max_double = std::numeric_limits<double>::max();
    double min_double = std::numeric_limits<double>::min();

    // 非常大的底数
    EXPECT_FLOAT_NEAR(pow(max_double, 0.0), 1.0, 1e-6); // 任何数的 0 次方都是 1
    // 非常小的底数
    EXPECT_FLOAT_NEAR(pow(min_double, 2.0), min_double * min_double, 1e-6);

    // 大指数，会返回inf
    EXPECT_TRUE(std::isinf(pow(max_double, 2.0)));
    EXPECT_TRUE(std::isinf(pow(-max_double, 2.0)));
}

// 测试 pow 函数的特殊值
TEST(PowFunctionTest, SpecialValues) {
    // INFINITY 作为底数
    EXPECT_EQ(pow(INFINITY, 2.0), INFINITY);
    EXPECT_EQ(pow(INFINITY, -2.0), 0.0);

    // NAN 作为底数或指数
    EXPECT_TRUE(std::isnan(pow(NAN, 2.0)));
    EXPECT_TRUE(std::isnan(pow(2.0, NAN)));
}

// 对用户功能函数的测试
TEST(GetWeekdayTest, BasicTest) {
    // 正常数据
    EXPECT_EQ(getWeekday(2024, 12, 4), 3);
    EXPECT_EQ(getWeekday(2024, 2, 29), 4);
    EXPECT_EQ(getWeekday(2020, 12, 26), 6);
    EXPECT_EQ(getWeekday(2000, 1, 16), 7);
    EXPECT_EQ(getWeekday(2100, 1, 16), 6);
}

TEST(GetWeekdayTest, ExceptionalTest) {
    // 越界数据
    EXPECT_EQ(getWeekday(0, 1, 16), -1);
    EXPECT_EQ(getWeekday(10, -1, 16), -1);
    EXPECT_EQ(getWeekday(20, 2, 30), -1);
    EXPECT_EQ(getWeekday(0x7FFFFFFF, 1, 16), -1);
}