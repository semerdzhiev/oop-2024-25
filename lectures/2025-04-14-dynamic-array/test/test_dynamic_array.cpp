#include "catch2/catch_all.hpp"
#include "dynamic_array.h"

#include <iostream>

using namespace examples;

/// Helper function to create a sample dynamic_array for testing
/// @param size The size of the dynamic_array to create
/// @return A dynamic_array of the specified size, initialized with values from 0 to size-1
/// @throws std::bad_alloc if memory allocation fails
dynamic_array create_sample_array(size_t size)
{
	dynamic_array arr(size);

	for(size_t i = 0; i < size; ++i)
	{
		arr[i] = i;
	}

	return arr;
}

TEST_CASE("dynamic_array() creates an empty array")
{
	dynamic_array empty;

	SECTION("Empty array should have size 0")
	{
		REQUIRE(empty.size() == 0);
	}
	SECTION("Attempt to access an element should throw std::out_of_range")
	{
		const dynamic_array& cref = empty;
		REQUIRE_THROWS_AS(empty.at(0), std::out_of_range);
		REQUIRE_THROWS_AS(cref.at(0), std::out_of_range);
	}
	SECTION("empty() should return true")
	{
		REQUIRE(empty.empty() == true);
	}
}

TEST_CASE("dynamic_array(N) creates an array with size N")
{
	const size_t size = 10;
	dynamic_array arr(size);
	REQUIRE(arr.size() == size);
	REQUIRE_FALSE(arr.empty());
}

TEST_CASE("dynamic_array(N) throws when allocation fails")
{
	const size_t impossible_size = std::numeric_limits<size_t>::max();

	REQUIRE_THROWS_AS(
		dynamic_array(impossible_size),
		std::bad_alloc
	);
}

TEST_CASE("dynamic_array::at() can be used to access all elements of a non-empty array")
{
	const size_t size = 10;
	dynamic_array arr = create_sample_array(size);
	const dynamic_array& cref = arr;

	for(size_t i = 0; i < size; ++i)
	{
		REQUIRE(arr.at(i) == static_cast<int>(i));
		REQUIRE(cref.at(i) == static_cast<int>(i));
	}
}

TEST_CASE("dynamic_array::at() throws when accessing elements outside of the bounds of the array")
{
	const size_t size = 10;
	dynamic_array arr = create_sample_array(size);
	const dynamic_array& cref = arr;

	REQUIRE_THROWS_AS(arr.at(size), std::out_of_range);
	REQUIRE_THROWS_AS(cref.at(size), std::out_of_range);
}

TEST_CASE("dynamic_array::swap() correctly swaps the contents of two arrays")
{
	dynamic_array sample1(3);
	sample1[0] = 1;
	sample1[1] = 2;
	sample1[2] = 3;

	dynamic_array sample2(5);
	sample2[0] = 10;
	sample2[1] = 20;
	sample2[2] = 30;
	sample2[3] = 40;
	sample2[4] = 50;

	dynamic_array left = sample1;
	dynamic_array right = sample2;

	left.swap(right);

	REQUIRE(left == sample2);
	REQUIRE(right == sample1);
}

TEST_CASE("dynamic_array::operator[]() can be used to access all elements of a non-empty array")
{
	const size_t size = 10;
	dynamic_array arr = create_sample_array(size);
	const dynamic_array& cref = arr;

	for(size_t i = 0; i < size; ++i)
	{
		REQUIRE(arr[i] == static_cast<int>(i));
		REQUIRE(cref[i] == static_cast<int>(i));
	}
}

TEST_CASE("dynamic_array::operator<() correctly compares arrays")
{
	SECTION("Two empty arrays")
	{
		dynamic_array arr1;
		dynamic_array arr2;
		REQUIRE_FALSE(arr1 < arr2);
	}
	SECTION("Two equal non-empty arrays")
	{
		dynamic_array arr1 = create_sample_array(10);
		dynamic_array arr2 = arr1;
		REQUIRE_FALSE(arr1 < arr2);
	}
	SECTION("Arrays with different sizes")
	{
		dynamic_array arr1 = create_sample_array(5);
		dynamic_array arr2 = create_sample_array(10);

		SECTION("One of the arrays is a proper subset of the other")
		{
			REQUIRE(arr1 < arr2);
			REQUIRE_FALSE(arr2 < arr1);
		}
		SECTION("Difference at first position") {
			arr1[0]--;
			REQUIRE(arr1 < arr2);
			REQUIRE_FALSE(arr2 < arr1);
		}
		SECTION("Difference at mid position") {
			arr1[arr1.size()/2]--;
			REQUIRE(arr1 < arr2);
			REQUIRE_FALSE(arr2 < arr1);
		}
		SECTION("Difference at last position") {
			arr1[arr1.size()-1]--;
			REQUIRE(arr1 < arr2);
			REQUIRE_FALSE(arr2 < arr1);
		}
	}
}

TEST_CASE("dynamic_array::operator==() and operator!=() correctly compare arrays")
{
	SECTION("Two empty arrays")
	{
		dynamic_array arr1;
		dynamic_array arr2;
		REQUIRE(arr1 == arr2);
		REQUIRE_FALSE(arr1 != arr2);
	}
	SECTION("Two equal non-empty arrays")
	{
		dynamic_array arr1 = create_sample_array(10);
		dynamic_array arr2 = arr1;
		REQUIRE(arr1 == arr2);
		REQUIRE_FALSE(arr1 != arr2);
	}
	SECTION("Arrays with different sizes")
	{
		dynamic_array arr1 = create_sample_array(5);
		dynamic_array arr2 = create_sample_array(10);

		SECTION("One of the arrays is a proper subset of the other")
		{
			REQUIRE_FALSE(arr1 == arr2);
			REQUIRE(arr2 != arr1);
		}
		SECTION("Difference at first position") {
			arr1[0]--;
			REQUIRE_FALSE(arr1 == arr2);
			REQUIRE(arr2 != arr1);
		}
		SECTION("Difference at mid position") {
			arr1[arr1.size()/2]--;
			REQUIRE_FALSE(arr1 == arr2);
			REQUIRE(arr2 != arr1);
		}
		SECTION("Difference at last position") {
			arr1[arr1.size()-1]--;
			REQUIRE_FALSE(arr1 == arr2);
			REQUIRE(arr2 != arr1);
		}
	}
}

TEST_CASE("dynamic_array::dynamic_array(const dynamic_array&) correctly copies an array")
{
	SECTION("Empty array")
	{
		dynamic_array arr1;
		dynamic_array arr2(arr1);
		REQUIRE(arr1.size() == arr2.size());
	}
	SECTION("Non-empty array")
	{
		const size_t size = 10;
		dynamic_array arr1 = create_sample_array(size);
		dynamic_array arr2(arr1);

		REQUIRE(arr1 == arr2);
	}
}

TEST_CASE("dynamic_array::operator=() correctly copies an array")
{
	SECTION("Copy from empty array")
	{
		dynamic_array arr1 = create_sample_array(10);
		dynamic_array empty;

		arr1 = empty;

		REQUIRE(arr1 == empty);
	}
	SECTION("Non-empty arrays")
	{
		const size_t size = 10;
		dynamic_array arr1 = create_sample_array(size);
		dynamic_array arr2 = create_sample_array(size*2);

		arr1 = arr2;

		REQUIRE(arr1 == arr2);
	}
}

TEST_CASE("operator<<(ostream&, dynamic_array&) correctly serializes an array")
{
	SECTION("Empty array")
	{
		dynamic_array empty;
		std::ostringstream output;
		output << empty;
		REQUIRE(output.str() == "array 0");
	}
	SECTION("Non-empty array")
	{
		dynamic_array arr = create_sample_array(5);
		std::ostringstream output;
		output << arr;
		REQUIRE(output.str() == "array 5 0 1 2 3 4");
	}
}


TEST_CASE("operator>>(istream&, dynamic_array&) correctly reads an array when the input is valid")
{
	SECTION("Empty array")
	{
		std::istringstream input("array 0");
		dynamic_array arr;

		input >> arr;

		REQUIRE(arr.empty());
	}
	SECTION("Non-empty array")
	{
		std::istringstream input("array 5 1 2 3 4 5");
		dynamic_array arr;

		input >> arr;

		REQUIRE(arr.size() == 5);
		REQUIRE(arr[0] == 1);
		REQUIRE(arr[1] == 2);
		REQUIRE(arr[2] == 3);
		REQUIRE(arr[3] == 4);
		REQUIRE(arr[4] == 5);
	}
}

TEST_CASE("operator>>(istream&, dynamic_array&) does not alter the array when the input is invalid")
{
	dynamic_array original_contents = create_sample_array(5);
	dynamic_array arr = original_contents;

	SECTION("Incorrect input format")
	{
		std::istringstream input("incorrect data here");
		input >> arr;
		REQUIRE(input.fail());
	}
	SECTION("Negative size")
	{
		std::istringstream input("array -1 1 2 3 4 5");
		input >> arr;
		REQUIRE(input.fail());
	}
	SECTION("Size too large")
	{
		std::istringstream input("array 123456789123456789 1 2 3 4 5");
		input >> arr;
		REQUIRE(input.fail());
	}
	SECTION("Too few elements")
	{
		std::istringstream input("array 5 1 2 3");
		input >> arr;
		REQUIRE(input.fail());
	}
	SECTION("One of the elements is incorrect")
	{
		std::istringstream input("array 5 1 2 3 word 4");
		input >> arr;
		REQUIRE(input.fail());
	}
	SECTION("One of the elements is too large")
	{
		std::istringstream input("array 5 1 2 3 123456789123456789 4");
		input >> arr;
		REQUIRE(input.fail());
	}
}
