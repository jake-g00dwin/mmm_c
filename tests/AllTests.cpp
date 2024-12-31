#include "CppUTest/CommandLineTestRunner.h"


//ImportTestGroups
IMPORT_TEST_GROUP(simple_test);
IMPORT_TEST_GROUP(mmm_c_test);
IMPORT_TEST_GROUP(activation_funcs);

//START: main
int main(int argc, char** argv)
{
    return RUN_ALL_TESTS(argc, argv);
}
//END: main
