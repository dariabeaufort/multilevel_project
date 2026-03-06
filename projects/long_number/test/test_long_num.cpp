#include <gtest/gtest.h>

#include "long_num.hpp"

using namespace rwh;

TEST(LongNumberTest, NoArguments) {
    LongNumber number;
    std::stringstream output;
    output << number;
    EXPECT_EQ(output.str(), "0");
}

TEST(LongNumberTest, StringPositive) {
    LongNumber number("270220080022072");
    std::stringstream output;
    output << number;
    EXPECT_EQ(output.str(), "270220080022072");
}

TEST(LongNumberTest, StringNegative) {
    LongNumber number("-270220080022072");
    std::stringstream output;
    output << number;
    EXPECT_EQ(output.str(), "-270220080022072");
}

TEST(LongNumberTest, StringZero) {
    LongNumber number("0");
    std::stringstream output;
    output << number;
    EXPECT_EQ(output.str(), "0");
}

TEST(LongNumberTest, Copy) {
    LongNumber original("270220080022072");
    LongNumber copy(original);

    std::stringstream output_1, output_2;
    output_1 << original;
    output_2 << copy;

    EXPECT_EQ(output_1.str(), output_2.str());
}

TEST(LongNumberTest, Equality) {
    LongNumber number_1("270220080022072");
    LongNumber number_2("270220080022072");
    LongNumber number_3("270220070022072");

    EXPECT_TRUE(number_1 == number_2);
    EXPECT_FALSE(number_1 == number_3);
}

TEST(LongNumberTest, InEquality) {
    LongNumber number_1("270220080022072");
    LongNumber number_2("270220080022072");
    LongNumber number_3("270220070022072");

    EXPECT_FALSE(number_1 != number_2);
    EXPECT_TRUE(number_1 != number_3);
}

TEST(LongNumberTest, GreaterThan) {
    LongNumber number_1("27022008");
    LongNumber number_2("72");
    LongNumber number_3("27022009");
    LongNumber number_4("-27022008");

    EXPECT_TRUE(number_1 > number_2);
    EXPECT_FALSE(number_1 > number_3);
    EXPECT_TRUE(number_1 > number_4);
}

TEST(LongNumberTest, LessThan) {
    LongNumber number_1("22072");
    LongNumber number_2("270220090022072");
    LongNumber number_3("-270220080022072");

    EXPECT_TRUE(number_1 < number_2);
    EXPECT_FALSE(number_2 < number_1);
    EXPECT_TRUE(number_3 < number_1);
}

TEST(LongNumberTest, IsNegative) {
    LongNumber positive("270220080022072");
    LongNumber negative("-270220080022072");
    LongNumber zero("0");

    EXPECT_FALSE(positive.is_negative());
    EXPECT_TRUE(negative.is_negative());
    EXPECT_FALSE(zero.is_negative());
}

TEST(StringSumTest, CheckEquality) {
    LongNumber number_1("123456000");
    LongNumber number_2("789");
    LongNumber result = number_1 + number_2;
	
    std::string expected = "123456789";
    std::string actual = getNumberString(result);
	
    EXPECT_EQ(expected, actual) 
		<< "Ошибка: неверный результат сложения";
}

TEST(StringSubtractionTest, CheckEquality) {
    LongNumber number_1("6000");
    LongNumber number_2("7000");
    LongNumber result = number_2 - number_1;
	
    std::string expected = "1000";
    std::string actual = getNumberString(result);
	
    EXPECT_EQ(expected, actual) 
		<< "Ошибка: неверный результат вычитания";
}

TEST(StringMultipleTest, CheckEquality) {
    LongNumber number_1("2000");
    LongNumber number_2("400");
    LongNumber result = number_1 * number_2;
	
    std::string expected = "800000";
    std::string actual = getNumberString(result);
	
    EXPECT_EQ(expected, actual) 
		<< "Ошибка: неверный результат умножения";
}

TEST(StringDivisionTest, CheckEquality) {
    LongNumber number_1("800000");
    LongNumber number_2("400");
    LongNumber result = number_1 / number_2;
	
    std::string expected = "2000";
    std::string actual = getNumberString(result);
	
    EXPECT_EQ(expected, actual) 
		<< "Ошибка: неверный результат деления";
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}