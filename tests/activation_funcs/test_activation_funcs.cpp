/*
 * Author: username
 * Date: todays_date 
 * filename: test_activation_funcs.c
 * description: module_purpose
 */

#include "CppUTest/CommandLineTestRunner.h"

extern "C" 
{
#include "activation_funcs.h"
}

TEST_GROUP(activation_funcs)
{
    void setup()
    {

    }
    void teardown()
    {

    }
};


TEST(activation_funcs, SelfTest)
{
    CHECK_TRUE(true);
}

TEST(activation_funcs, SigmoidLargeClamped)
{
    float BigNum = 256.0;
    float result = AF_Sigmoid(BigNum);
    CHECK_EQUAL_TEXT(1, result, "The returned value should be 1!");
}

TEST(activation_funcs, SigmoidSmallClamped)
{
    float SmallNum = -256.0;
    float result = AF_Sigmoid(SmallNum);
    CHECK_EQUAL_TEXT(0, result, "The returned value should be 0!");
}

TEST(activation_funcs, SigmoidReturnsInValidRange)
{
    float InputNum = 0.5;
    float result = AF_Sigmoid(InputNum);
    printf("value: %f", result);
    CHECK_TRUE(result < 0.7);
    CHECK_TRUE(result > 0.5);
}
