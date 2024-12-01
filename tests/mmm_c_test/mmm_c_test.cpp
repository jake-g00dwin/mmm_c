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


TEST(mmm_c_test, allocateSingleHeapMatrix)
{
    unsigned int rows = 8;
    unsigned int cols = 8;

    uint_fast16_t *ptr = (uint_fast16_t *)malloc(sizeof(uint_fast16_t) * rows * cols);
    
    if(ptr == NULL) {
        FAIL_TEST("Not allocated!");
    }

    free(ptr);

    CHECK(true);
}


TEST(mmm_c_test, DU16_New)
{
    U16_DMAT mat = DU16_New(8, 8);
    
    CHECK_TRUE(mat.cols == 8);
    CHECK_TRUE(mat.rows == 8);
    CHECK_TRUE(mat.cells == NULL);
    CHECK_TRUE(mat.is_allocated == false);
}

TEST(mmm_c_test, DU16_ManualMatAllocate) 
{
    U16_DMAT mat;
    mat.cols = 8;
    mat.rows = 8;
    mat.cells = NULL;
    
    CHECK_TRUE(mat.cells == NULL);
    
    mat.cells = (uint_fast16_t *)malloc(
            sizeof(uint_fast16_t) * mat.cols * mat.rows
            );

    if(mat.cells == NULL) {
        FAIL_TEST("Not allocated!");
    }
    
    free(mat.cells);
}

TEST(mmm_c_test, DU16_AllocateMemoryPasses)
{
    U16_DMAT mat = DU16_New(8, 8);
    
    DU16_AllocateMemory(&mat);

    CHECK_FALSE(mat.cells == NULL);
    CHECK_FALSE(mat.is_allocated == false);

    free(mat.cells);
}

TEST(mmm_c_test, DU16_FreeWorks)
{
    U16_DMAT mat = DU16_New(8, 8);
    
    DU16_AllocateMemory(&mat);

    CHECK_FALSE(mat.cells == NULL);
    CHECK_FALSE(mat.is_allocated == false);

    DU16_FreeMatrix(&mat);

    CHECK_TRUE(mat.cells == NULL);
    CHECK_TRUE(mat.is_allocated == false);
}

TEST(mmm_c_test, DU16_FreeReturnsErrorOnMisMatch)
{
    U16_DMAT mat = DU16_New(8, 8);
    
    //Manually set the value to an invalid one.
    mat.is_allocated = true; 
    int result = DU16_FreeMatrix(&mat);

    CHECK_EQUAL(Error, result);

    //The function should set them correctly.
    CHECK_TRUE(mat.cells == NULL);
    CHECK_TRUE(mat.is_allocated == false);
}

TEST(mmm_c_test, DU16_SetAllToValuesSetsValues)
{
    U16_DMAT mat = DU16_New(8, 8);
    CHECK_EQUAL(Ok, DU16_AllocateMemory(&mat));
    
    if(DU16_SetAllTo(&mat, 5) != Ok){
        FAIL_TEST("Expected allocated matrix.");
    }

    for(int i = 0; i < (mat.cols * mat.rows); i++){
        CHECK_EQUAL(5, mat.cells[i]);
    }

    DU16_FreeMatrix(&mat);
}

