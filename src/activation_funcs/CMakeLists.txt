add_library(activation_funcs STATIC
    activation_funcs.c
)

target_include_directories(activation_funcs PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
