# Sample static library
add_library(lib_dynamic_array STATIC)

target_sources(
    lib_dynamic_array
    PRIVATE
        "dynamic_array.cpp"
        "dynamic_array.h"
)
