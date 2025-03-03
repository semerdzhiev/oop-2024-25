#define CATCH_CONFIG_MAIN  
#include "person.h"
#include "catch.hpp"

TEST_CASE("Person creation with valid data") 
{
    // Arrange
    bool gender = false;
    int age = 12;
    const char* name = "Hi";

    // Act
    Person p = createPerson(gender, age, name);

    // Assert
    REQUIRE(p.gender == gender);
    REQUIRE(p.age == age);
    REQUIRE(strcmp(p.name, name) == 0);
}

TEST_CASE("Testing Person related methods")
{
    Person p1 = createPerson(false, 15, "Fernando");
    Person p2 = createPerson(false, 22, "Ivan");
    Person p3 = createPerson(false, 22, "Maria");

    SECTION("Test isOlder when first person is older")
    {
        REQUIRE(isOlder(p2, p1));
        REQUIRE_FALSE(isOlder(p1, p2));
    }

    SECTION("Test isOlder when ages are equal")
    {
        REQUIRE((!isOlder(p2, p3)));
        REQUIRE((!isOlder(p3, p2)));
    }
}