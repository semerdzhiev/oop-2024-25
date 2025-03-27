cmake_minimum_required (VERSION 3.13)

project ("Streams" VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(numbers "numbers.cpp")

add_executable(inventory "inventory.cpp")

add_executable(words "words.cpp")

add_executable(long-input "long-input.cpp")