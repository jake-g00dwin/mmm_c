#include "CppUTest/TestHarness.h"

extern C 
{
#include "mmm_c.h" 
}


TEST_GROUP(simple_test)
{
    void setup()
    {

    }
    void teardown()
    {

    }
};

TEST(simple_test, passing_test)
{
    CHECK_TRUE(1);
}
