cmake_minimum_required (VERSION 3.13)

project ("Static library sample" VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# A sample static library
add_library(abc)

target_sources(
	abc
	PRIVATE
		"library.cpp"
)


# Main target
add_executable(application)

target_sources(
	application
	PRIVATE
		"main.cpp"
)

target_link_libraries(
	application
	PRIVATE
		abc	
)
