#define CATCH_CONFIG_MAIN  
#include "car.h"
#include "catch.hpp"
#include <cstring>
#include <cmath>

const double EPS = 0.001;
bool areDoubleEqual(double first, double second)
{
    return abs(first - second) < EPS;
}

TEST_CASE("Car created correctly")
{
    // Arrange 
    double fuelConsumption = 4.5;
    double fuel = 50;

    // Act
    Car c("BMW", "V8", 300, 2020, fuelConsumption, fuel);

    // Assert
    REQUIRE(strcmp(c.getBrand(), "BMW") == 0);
    REQUIRE(strcmp(c.getEngine(), "V8") == 0);
    REQUIRE(c.getHp() == 300);
    REQUIRE(c.getYear() == 2020);
    REQUIRE(areDoubleEqual(c.getFuelConsumption(), fuelConsumption));
    REQUIRE(areDoubleEqual(c.getFuel(), fuel));
}

TEST_CASE("Drive calculated correctly")
{
    // Arrange 
    double fuelConsumption = 4.5;
    int fuel = 50;
    Car c("BMW", "V8", 300, 2020, fuelConsumption, fuel);

    // Act
    c.drive(100);

    // Assert
    REQUIRE(areDoubleEqual(c.getFuel(), fuel - 4.5));
}