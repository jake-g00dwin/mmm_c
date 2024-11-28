
# TEST_RUNNER
add_library(mmm_c_test
    mmm_c_test.cpp    
)

target_link_libraries(mmm_c_test
    mmm_c
    ${CPPUTEST_LIBRARIES}/libCppUTest.a
    ${CPPUTEST_LIBRARIES}/libCppUTestExt.a
)

