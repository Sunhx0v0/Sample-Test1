#include "pch.h"
#include<cmath>

const double M_PI = 3.1415926535;
// ���ǵ���������,����һ�������Ƚϸ�����
#define EXPECT_FLOAT_NEAR(a, b, epsilon) \
    EXPECT_TRUE(abs((a) - (b)) <= (epsilon)) << "Expected: " #a " == " #b ", but got " << a << " and " << b;

// �Կ⺯���Ĳ���
// ���� sin ����
TEST(MathFunctionsTest, SinTest) {
    // ��������Ƕȵ�����ֵ
    EXPECT_FLOAT_NEAR(sin(0.0), 0.0, 1e-6);
    EXPECT_FLOAT_NEAR(sin(M_PI / 2), 1.0, 1e-6);
    EXPECT_FLOAT_NEAR(sin(M_PI), 0.0, 1e-6);
    EXPECT_FLOAT_NEAR(sin(3 * M_PI / 2), -1.0, 1e-6);
}

// ���� cos ����
TEST(MathFunctionsTest, CosTest) {
    // ��������Ƕȵ�����ֵ
    EXPECT_FLOAT_NEAR(cos(0.0), 1.0, 1e-6);
    EXPECT_FLOAT_NEAR(cos(M_PI / 2), 0.0, 1e-6);
    EXPECT_FLOAT_NEAR(cos(M_PI), -1.0, 1e-6);
    EXPECT_FLOAT_NEAR(cos(3 * M_PI / 2), 0.0, 1e-6);
}

// ���� sqrt ����
TEST(MathFunctionsTest, SqrtTest) {
    // �������������Լ�������Ӧ���׳� domain error��
    EXPECT_FLOAT_NEAR(sqrt(4.0), 2.0, 1e-6);
    EXPECT_FLOAT_NEAR(sqrt(9.0), 3.0, 1e-6);
    EXPECT_FLOAT_NEAR(sqrt(0.0), 0.0, 1e-6);

    // ��鵱����Ϊ����ʱ�Ƿ��׳��쳣
    EXPECT_TRUE(std::isnan(sqrt(-1)))<< "should return NaN but return "<< sqrt(-1);
}

// ���� pow �����Ļ�������
TEST(PowFunctionTest, BasicFunctionality) {
    // ����������ָ��
    EXPECT_FLOAT_NEAR(pow(2.0, 3.0), 8.0, 1e-6);
    EXPECT_FLOAT_NEAR(pow(5.0, 2.0), 25.0, 1e-6);

    // ����Ϊ 1
    EXPECT_FLOAT_NEAR(pow(1.0, 100.0), 1.0, 1e-6);
}

// ���� pow �����ı߽�����
TEST(PowFunctionTest, EdgeCases) {
    // ָ��Ϊ 0
    EXPECT_FLOAT_NEAR(pow(10.0, 0.0), 1.0, 1e-6);
    EXPECT_FLOAT_NEAR(pow(-10.0, 0.0), 1.0, 1e-6);

    // ����Ϊ 0
    EXPECT_FLOAT_NEAR(pow(0.0, 2.0), 0.0, 1e-6);
    EXPECT_FLOAT_NEAR(pow(0.0, 100.0), 0.0, 1e-6);

    // ָ��Ϊ 1
    EXPECT_FLOAT_NEAR(pow(7.0, 1.0), 7.0, 1e-6);
    EXPECT_FLOAT_NEAR(pow(-7.0, 1.0), -7.0, 1e-6);
}

// ���� pow �������쳣���
TEST(PowFunctionTest, ExceptionalCases) {
    // ���������ͷ�����ָ��
    EXPECT_FLOAT_NEAR(pow(-1.0, 3.0), -1.0, 1e-6);
    EXPECT_FLOAT_NEAR(pow(-2.0, 3.0), -8.0, 1e-6);
    EXPECT_TRUE(std::isnan(pow(-2.0, 0.5))) << "should return NaN but return " << pow(-2.0, 0.5);

    // ����Ϊ 0 ��ָ��Ϊ����
    //EXPECT_TRUE(std::isnan(pow(0.0, -1.0))) << "should return NaN but return "<<pow(0.0,-1);
    EXPECT_TRUE(std::isinf(pow(0.0, -1.0)));    // �ҵı������᷵��inf
}

// ���� pow �����ļ������
TEST(PowFunctionTest, ExtremeCases) {
    double max_double = std::numeric_limits<double>::max();
    double min_double = std::numeric_limits<double>::min();

    // �ǳ���ĵ���
    EXPECT_FLOAT_NEAR(pow(max_double, 0.0), 1.0, 1e-6); // �κ����� 0 �η����� 1
    // �ǳ�С�ĵ���
    EXPECT_FLOAT_NEAR(pow(min_double, 2.0), min_double * min_double, 1e-6);

    // ��ָ�����᷵��inf
    EXPECT_TRUE(std::isinf(pow(max_double, 2.0)));
    EXPECT_TRUE(std::isinf(pow(-max_double, 2.0)));
}

// ���� pow ����������ֵ
TEST(PowFunctionTest, SpecialValues) {
    // INFINITY ��Ϊ����
    EXPECT_EQ(pow(INFINITY, 2.0), INFINITY);
    EXPECT_EQ(pow(INFINITY, -2.0), 0.0);

    // NAN ��Ϊ������ָ��
    EXPECT_TRUE(std::isnan(pow(NAN, 2.0)));
    EXPECT_TRUE(std::isnan(pow(2.0, NAN)));
}

// ���û����ܺ����Ĳ���
TEST(GetWeekdayTest, BasicTest) {
    // ��������
    EXPECT_EQ(getWeekday(2024, 12, 4), 3);
    EXPECT_EQ(getWeekday(2024, 2, 29), 4);
    EXPECT_EQ(getWeekday(2020, 12, 26), 6);
    EXPECT_EQ(getWeekday(2000, 1, 16), 7);
    EXPECT_EQ(getWeekday(2100, 1, 16), 6);
}

TEST(GetWeekdayTest, ExceptionalTest) {
    // Խ������
    EXPECT_EQ(getWeekday(0, 1, 16), -1);
    EXPECT_EQ(getWeekday(10, -1, 16), -1);
    EXPECT_EQ(getWeekday(20, 2, 30), -1);
    EXPECT_EQ(getWeekday(0x7FFFFFFF, 1, 16), -1);
}