#include "catch2/catch_all.hpp"
#include "solution.h"

TEST_CASE("calculator::factorial(0) returns 1")
{
	calculator calc;
	REQUIRE(calc.factorial(0) == 1);
}

TEST_CASE("calculator::factorial() returns correct values")
{
	calculator calc;
	REQUIRE(calc.factorial(1) == 1);
	REQUIRE(calc.factorial(2) == 2);
	REQUIRE(calc.factorial(3) == 6);
	REQUIRE(calc.factorial(4) == 24);
	REQUIRE(calc.factorial(5) == 120);
	REQUIRE(calc.factorial(6) == 720);
	REQUIRE(calc.factorial(7) == 5'040);
	REQUIRE(calc.factorial(8) == 40'320);
	REQUIRE(calc.factorial(9) == 362'880);
	REQUIRE(calc.factorial(10) == 3'628'800);
}

TEST_CASE("calculator::factorial() throws for negative values")
{
	calculator calc;
	REQUIRE_THROWS_AS(calc.factorial(-1), std::invalid_argument);
	REQUIRE_THROWS_AS(calc.factorial(-2), std::invalid_argument);
	REQUIRE_THROWS_AS(calc.factorial(-3), std::invalid_argument);
}

TEST_CASE("calculator::performed_calculations() returns 0 for newly created objects")
{
	calculator calc;
	REQUIRE(calc.performed_calculations() == 0);
}

TEST_CASE("calculator::performed_calculations() each successful calculation increments the counter")
{
	calculator calc;
	
	calc.factorial(5);
	REQUIRE(calc.performed_calculations() == 1);
	calc.factorial(6);
	REQUIRE(calc.performed_calculations() == 2);
	calc.fibonacci(7);
	REQUIRE(calc.performed_calculations() == 3);
	calc.factorial(8);
	REQUIRE(calc.performed_calculations() == 4);
	calc.fibonacci(9);
	REQUIRE(calc.performed_calculations() == 5);
}

TEST_CASE("calculator::performed_calculations() does not count failed calculations")
{
	calculator calc;

	calc.factorial(5);
	calc.fibonacci(5);
	
	REQUIRE_THROWS_AS(calc.factorial(-1), std::invalid_argument);

	calc.factorial(5);
	calc.fibonacci(5);

	REQUIRE_THROWS_AS(calc.fibonacci(-1), std::invalid_argument);

	REQUIRE(calc.performed_calculations() == 4);
}