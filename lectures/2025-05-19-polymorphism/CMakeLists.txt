cmake_minimum_required (VERSION 3.13)

project ("Minimalistic CMake Template" VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(application "main.cpp")

