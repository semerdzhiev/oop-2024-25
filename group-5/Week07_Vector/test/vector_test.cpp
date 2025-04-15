#define CATCH_CONFIG_MAIN  
#include "catch.hpp"
#include "../src/vector.hpp"
#include <iostream>
using namespace std;

TEST_CASE("Constructor default capacity is correct")
{
    // Arrange, Act
    Vector vector;

    // Assert
    REQUIRE(vector.getCapacity() == DEFAULT_CAPACITY);
    REQUIRE(vector.getSize() == 0);
    REQUIRE(vector.getResizeFactor() == DEFAULT_RESIZE_FACTOR);
}

TEST_CASE("Constructor with initial capacity")
{
    // Arrange
    int new_capacity = 10;

    // Act
    Vector vector(new_capacity);

    // Assert
    REQUIRE(vector.getCapacity() == new_capacity);
    REQUIRE(vector.getSize() == 0);
    REQUIRE(vector.getResizeFactor() == DEFAULT_RESIZE_FACTOR);
}

TEST_CASE("Copy constructor with initial capacity")
{
    // Arrange
    int new_capacity = 10;
    Vector vector(new_capacity);

    // Act
    Vector test_copy(vector);

    // Assert
    REQUIRE(test_copy.getCapacity() == new_capacity);
    REQUIRE(test_copy.getSize() == 0);
    REQUIRE(test_copy.getResizeFactor() == DEFAULT_RESIZE_FACTOR);
}

TEST_CASE("Push back in empty vector")
{
    // Arrange
    int value = 5;
    Vector vector;

    // Act
    vector.push_back(value);

    // Assert
    REQUIRE(vector.getSize() == 1);
    REQUIRE(vector[0] == value);
}

TEST_CASE("At invalid position throws error")
{
    // Arrange
    Vector vector;

    // Act & Assert
    REQUIRE_THROWS_WITH(vector.at(2), "Index out of bounds");
}
