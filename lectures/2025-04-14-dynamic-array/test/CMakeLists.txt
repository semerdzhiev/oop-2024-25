# Executable target for the unit tests
add_executable(unit-tests)

target_link_libraries(
    unit-tests
    PRIVATE
    lib_dynamic_array
        Catch2::Catch2WithMain
)

target_sources(
    unit-tests
    PRIVATE
        "test_dynamic_array.cpp"
)

# Automatically register all tests
catch_discover_tests(unit-tests)
