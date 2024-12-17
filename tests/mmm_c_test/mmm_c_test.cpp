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

TEST(mmm_c_test, DU16_IndexingFailsOnOutOfBounds)
{
    U16_DMAT mat = DU16_New(8, 8);
    CHECK_EQUAL(Ok, DU16_AllocateMemory(&mat));
    DU16_SetAllTo(&mat, 0);

    CHECK_EQUAL(NULL, DU16_CellIndex(&mat, 0, 8));
    CHECK_EQUAL(NULL, DU16_CellIndex(&mat, 8, 0));

    DU16_FreeMatrix(&mat);
}

//Works but commented out to keep test output cleaner
/*
TEST(mmm_c_test, DU16_PrintWorksOnInitializedMatrix)
{
    U16_DMAT mata = DU16_New(2, 3);
    CHECK_EQUAL(Ok, DU16_AllocateMemory(&mata));
    DU16_SetAllTo(&mata, 0);

    Result r = DU16_PrintMatrix(&mata);
    CHECK_EQUAL_TEXT(Ok, r, "Failure to print matrix");
}
*/

TEST(mmm_c_test, DU16_IndexingSquareMatrixWorks)
{
    U16_DMAT mat = DU16_New(8, 8);
    CHECK_EQUAL(Ok, DU16_AllocateMemory(&mat));
   
    DU16_SetAllTo(&mat, 0);

    for(int i = 0; i < 64; i++){
        mat.cells[i] = i;
    }

    //nested for loops with outer loop being columns and the 
    //inner loop being rows.
    int index = 0;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            CHECK_TRUE(*DU16_CellIndex(&mat, j, i) == index);
            index += 1;
        }
    }

    DU16_FreeMatrix(&mat);
}

TEST(mmm_c_test, DU16_MultiplyBySingleValueFailsOnUnallocated)
{
    U16_DMAT mat = DU16_New(8, 8);

    CHECK_EQUAL(Error, DU16_MultiplyByNum(&mat, 2));
}

TEST(mmm_c_test, DU16_MultiplyBySingleValueWorks)
{
    U16_DMAT mat = DU16_New(8, 8);
    CHECK_EQUAL(Ok, DU16_AllocateMemory(&mat));

    for(int i = 0; i < 64; i++){
        mat.cells[i] = i;
    }

    if(DU16_MultiplyByNum(&mat, 2) == Error) {
        FAIL("Single multiplication returned error!");
    }

    for(uint_fast16_t i = 0; i < 64; i++){
        CHECK_EQUAL(i * 2, mat.cells[i]); 
    }

    DU16_FreeMatrix(&mat);
}

TEST(mmm_c_test, DU16_DotProductOfMatAndVectorIsCorrect)
{
    U16_DMAT mata = DU16_New(2, 3);
    CHECK_EQUAL(Ok, DU16_AllocateMemory(&mata));
    DU16_SetAllTo(&mata, 2);

    U16_DMAT matb = DU16_New(3, 2);
    CHECK_EQUAL(Ok, DU16_AllocateMemory(&matb));
    DU16_SetAllTo(&matb, 4);

    //Setup the conditions
    uint_fast16_t vala = 1;
    for(int i = 0; i < mata.rows; i++){
        for(int j = 0; j < mata.cols; j++){
            uint_fast16_t *cella = DU16_CellIndex(&mata, i, j);
            *cella = vala;
            vala += 1;
        }
    }

    uint_fast16_t valb = 7;
    for(int i = 0; i < matb.rows; i++){
        for(int j = 0; j < matb.cols; j++){
            uint_fast16_t *cellb = DU16_CellIndex(&matb, i, j);
            *cellb = valb;
            valb += 1;
        }
    }

    U16_DMAT mat_result = DU16_DotProduct(&mata, &matb);

    //Test the conditions
    
    //Check the shape
    CHECK_TRUE_TEXT(mat_result.is_allocated, "The matrix wasn't allocated!");
    CHECK_TRUE_TEXT(mat_result.rows == 2, "Number of rows incorrect!");
    CHECK_TRUE_TEXT(mat_result.cols == 2, "Number of columns incorrect!");


    uint_fast16_t *ptr = NULL;

    //All indecies are done via Row, Col
    ptr = DU16_CellIndex(&mat_result, 0, 0);
    CHECK_EQUAL(58, *ptr);

    ptr = DU16_CellIndex(&mat_result, 0, 1);
    CHECK_EQUAL(64, *ptr);
    
    ptr = DU16_CellIndex(&mat_result, 1, 0);
    CHECK_EQUAL(139, *ptr);
    
    ptr = DU16_CellIndex(&mat_result, 1, 1);
    CHECK_EQUAL(154, *ptr);

    DU16_FreeMatrix(&mata);
    DU16_FreeMatrix(&matb);
    DU16_FreeMatrix(&mat_result);
}

