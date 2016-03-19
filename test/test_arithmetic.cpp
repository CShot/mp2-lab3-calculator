#include <gtest.h>
#include "calculator.h"

TEST(calculator, add)
{
	char s[] = "25+5";
	char s2[10] = { 0 };
	polish_notation(s, s2);
	int result = calculator(s2);
	EXPECT_EQ(30, result);
}

TEST(calculator, subtraction)
{
	char s[] = "25-5";
	char s2[10] = {0};
	polish_notation(s, s2);
	int result=calculator(s2);
	EXPECT_EQ(20, result);
}

TEST(calculator, multiplication)
{
	char s[] = "25*5";
	char s2[10] = { 0 };
	polish_notation(s, s2);
	int result = calculator(s2);
	EXPECT_EQ(125, result);
}

TEST(calculator,division)
{
	char s[] = "25/5";
	char s2[10] = { 0 };
	polish_notation(s, s2);
	int result = calculator(s2);
	EXPECT_EQ(5, result);
}

TEST(calculator, error_in_brackets)
{
	char s[] = "2-)3+4(";
	int result = foolproof(s);
	EXPECT_EQ(1, result);
}

TEST(calculator,consecutive_characters)
{
	char s[] = "2-+4";
	int result = foolproof(s);
	EXPECT_EQ(1, result);
}

TEST(calculator, inappropriate_symbols)
{
	char s[] = "3+5%r*6";
	int result = foolproof(s);
	EXPECT_EQ(1, result);
}

TEST(calculator, complex_expressions_with_parentheses)
{
	char s[] = "10-5*(4*(4/1)/2-3)*2";
	char s2[100] = { 0 };
	polish_notation(s, s2);
	int result = calculator(s2);
	EXPECT_EQ(-40, result);
}

TEST(calculator, complex_expressions_without_parentheses)
{
	char s[] = "10-5*4*4/1/2-3*2";
	char s2[100] = { 0 };
	polish_notation(s, s2);
	int result = calculator(s2);
	EXPECT_EQ(-36, result);
}

TEST(calculator, division_by_0)
{
	char s[] = "10/(5-5)";
	char s2[100] = { 0 };
	polish_notation(s, s2);
	int result = calculator(s2);
	EXPECT_EQ(NULL, result);
}

