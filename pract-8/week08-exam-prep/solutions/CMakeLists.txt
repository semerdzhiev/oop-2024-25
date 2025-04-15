cmake_minimum_required(VERSION 3.13)

project("Project name" VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

add_executable(application)
target_sources(
    application 
    PRIVATE 
    main.cpp 
    Drone.cpp
    # Point.cpp
    DroneShow.cpp 

    # other cpp files
)

# include(FetchContent)

# FetchContent_Declare(
#     Catch2
#     GIT_REPOSITORY https://github.com/catchorg/Catch2.git
#     GIT_TAG        v2.x
# )

# FetchContent_MakeAvailable(Catch2)
# message(STATUS "Catch2 was successfully added!")

# include_directories(${CMAKE_BINARY_DIR}/_deps/catch2-src/single_include)



#testing

# enable_testing()
# include(CTest)

# add_executable(tests)
# target_sources(
#     tests 
#     PRIVATE 
#     example_test.cpp # Only define CATCH_CONFIG_MAIN in this file
#     # other cpp tests
# )

# target_link_libraries(tests PRIVATE Catch2::Catch2)

# add_test(NAME Catch2Tests COMMAND tests)

