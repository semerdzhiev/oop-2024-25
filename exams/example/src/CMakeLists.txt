# Sample static library
add_library(solution STATIC)

target_sources(
    solution
    PRIVATE
        "solution.cpp"
        "solution.h"
)


# Executable target for the application
add_executable(application)

target_link_libraries(
    application
    PRIVATE
        solution
)

target_sources(
    application
    PRIVATE
        "application.cpp"
)