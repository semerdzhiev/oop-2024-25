#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "Vector.hpp"
#include <sstream>
#include <stdexcept>

TEST_CASE("Push_back, Pop_back, at and operator[]", "[Vector]") {
    Vector v;

    SECTION("Push_back and at") {
        v.push_back(10);
        v.push_back(20);
        v.push_back(30);
        REQUIRE(v.at(0) == 10);
        REQUIRE(v.at(1) == 20);
        REQUIRE(v.at(2) == 30);
      
        REQUIRE(v[0] == 10);
        REQUIRE(v[1] == 20);
        REQUIRE(v[2] == 30);
    }

    SECTION("Pop_back reduces size and resizes capacity") {
        v.push_back(5);
        v.push_back(15);
        v.push_back(25);
        v.pop_back();

        REQUIRE_NOTHROW(v.at(0));
        REQUIRE_NOTHROW(v.at(1));
        REQUIRE_THROWS_AS(v.at(2), std::out_of_range);
    }

    SECTION("Pop_back on empty vector throws exception") {
        REQUIRE_THROWS_AS(v.pop_back(), std::out_of_range);
    }
}

TEST_CASE("Insert_at and Delete_at", "[Vector]") {
    Vector v;

    v.push_back(1);
    v.push_back(3);
    v.push_back(5);

    SECTION("Insert_at valid index") {
        v.insert_at(1, 2);
        REQUIRE(v.at(0) == 1);
        REQUIRE(v.at(1) == 2);
        REQUIRE(v.at(2) == 3);
        REQUIRE(v.at(3) == 5);
    }

    SECTION("Insert_at at end") {
        v.insert_at(3, 7);
        REQUIRE(v.at(3) == 7);
    }

    SECTION("Insert_at invalid index throws") {
        REQUIRE_THROWS_AS(v.insert_at(5, 100), std::out_of_range);
    }

    SECTION("Delete_at valid index") {
        v.push_back(7);

        v.delete_at(1);
        REQUIRE(v.at(0) == 1);
        REQUIRE(v.at(1) == 5);
        REQUIRE(v.at(2) == 7);
        REQUIRE_THROWS_AS(v.at(3), std::out_of_range);
    }

    SECTION("Delete_at invalid index throws") {
        REQUIRE_THROWS_AS(v.delete_at(3), std::out_of_range);
    }
}

TEST_CASE("Sort and Reverse", "[Vector]") {
    Vector v;
    v.push_back(5);
    v.push_back(3);
    v.push_back(4);
    v.push_back(1);
    v.push_back(2);

    SECTION("Sort vector") {
        v.sort();
        for (int i = 0; i < 5; i++) {
            REQUIRE(v.at(i) == i + 1);
        }
    }

    SECTION("Reverse vector") {
        v.sort();
        v.reverse();
        for (int i = 0; i < 5; i++) {
            REQUIRE(v.at(i) == 5 - i);
        }
    }
}

TEST_CASE("Concatenation with concat and operator+", "[Vector]") {
    Vector v1;
    Vector v2;
    // v1 = [1, 2], v2 = [3, 4]
    v1.push_back(1);
    v1.push_back(2);
    v2.push_back(3);
    v2.push_back(4);

    SECTION("concat method") {
        v1.concat(v2);
        // Expected: v1 = [1, 2, 3, 4]
        REQUIRE(v1.at(0) == 1);
        REQUIRE(v1.at(1) == 2);
        REQUIRE(v1.at(2) == 3);
        REQUIRE(v1.at(3) == 4);
    }

    SECTION("operator+ for concatenation") {
        Vector v3;
        v3.push_back(1);
        v3.push_back(2);
        v3 + v2; 
        REQUIRE(v3.at(0) == 1);
        REQUIRE(v3.at(1) == 2);
        REQUIRE(v3.at(2) == 3);
        REQUIRE(v3.at(3) == 4);
    }
}

TEST_CASE("Slice", "[Vector]") {
    Vector v;
    for (int i = 0; i < 10; i++) {
        v.push_back(i);
    }

    SECTION("Valid slice") {
        Vector s = v.slice(3, 7);
        REQUIRE(s.at(0) == 3);
        REQUIRE(s.at(1) == 4);
        REQUIRE(s.at(2) == 5);
        REQUIRE(s.at(3) == 6);
        REQUIRE_THROWS_AS(s.at(4), std::out_of_range);
    }

    SECTION("Invalid slice throws exception") {
        REQUIRE_THROWS_AS(v.slice(7, 3), std::out_of_range);
        REQUIRE_THROWS_AS(v.slice(0, 11), std::out_of_range);
    }
}

TEST_CASE("Equality and Dot Product", "[Vector]") {
    Vector v1;
    Vector v2;
    // v1 = [1, 2, 3, 4, 5], v2 = [1, 2, 3, 4, 5]
    for (int i = 1; i <= 5; i++) {
        v1.push_back(i);
        v2.push_back(i);
    }

    SECTION("Equality operator") {
        REQUIRE(v1 == v2);
        v2.push_back(6);
        REQUIRE_FALSE(v1 == v2);
    }

    SECTION("Dot product operator*") {
        // 1*1 + 2*2 + 3*3 + 4*4 + 5*5 = 55
        int dot = v1 * v2;
        REQUIRE(dot == 55);
    }
}

TEST_CASE("Stream output operator", "[Vector]") {
    Vector v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    std::ostringstream oss;
    oss << v;
    // Expected: "[10, 20, 30]"
    REQUIRE(oss.str() == "[10, 20, 30]");
}
