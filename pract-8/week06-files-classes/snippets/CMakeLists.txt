cmake_minimum_required (VERSION 3.13)

project ("Files and classes" VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v2.x
)

FetchContent_MakeAvailable(Catch2)
message(STATUS "Catch2 was successfully added!")

include_directories(${CMAKE_BINARY_DIR}/_deps/catch2-src/single_include)

add_executable(application main.cpp)
# add_executable(tests test_main.cpp)

target_sources(application PRIVATE Person.cpp)

# target_link_libraries(tests Catch2::Catch2)
