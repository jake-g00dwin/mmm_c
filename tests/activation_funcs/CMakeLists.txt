# TEST_RUNNER
add_library(test_activation_funcs
    test_activation_funcs.cpp    
)

target_link_libraries(test_activation_funcs
    ${CPPUTEST_LIBRARIES}/libCppUTest.a
    ${CPPUTEST_LIBRARIES}/libCppUTestExt.a
    activation_funcs
)
