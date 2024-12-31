project(Tests)

# TEST_DIRS 
add_subdirectory(simple_test)
add_subdirectory(mmm_c_test)
add_subdirectory(activation_funcs)

# TEST_RUNNER
add_executable(AllTests
    AllTests.cpp    
)

target_link_libraries(AllTests
    ${CPPUTEST_LIBRARIES}/libCppUTest.a
    ${CPPUTEST_LIBRARIES}/libCppUTestExt.a
    # TEST_LINKS
    simple_test
    mmm_c_test
    test_activation_funcs
)
