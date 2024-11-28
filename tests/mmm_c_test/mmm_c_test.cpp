#include "CppUTest/TestHarness.h"

extern "C" 
{
    #include "mmm_c.h" 
}

TEST_GROUP(mmm_c_test)
{
    void setup()
    {

    }
    void teardown()
    {

    }
};

TEST(mmm_c_test, passing_test)
{
    CHECK_TRUE(1);
}
