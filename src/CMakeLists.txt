add_library(mmm_c SHARED
    mmm_c.c
)

set_target_properties(mmm_c PROPERTIES
    VERSION ${PROJECT_VERSION}    
)
add_subdirectory(activation_funcs)
