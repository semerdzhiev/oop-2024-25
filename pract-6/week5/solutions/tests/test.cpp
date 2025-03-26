#define CATCH_CONFIG_MAIN

#include <catch2/catch_all.hpp>

#include "../Drone.h"

TEST_CASE("Default drone has correct behaviour", "[drone]") {
    Drone drone;

    REQUIRE(drone.getId() == nullptr);
    REQUIRE_FALSE(drone.hasRemainingPath());
    REQUIRE_FALSE(drone.moveWithOneStep());
}

TEST_CASE("Drone has correct behaviour", "[drone]") {
    Position path[4] = {Position(1, 1), Position(2, 2), Position(3, 3), Position(4, 4)};
    Drone drone("1", path, 4);

    REQUIRE(strcmp(drone.getId(), "1") == 0);
    REQUIRE(drone.hasRemainingPath());
    REQUIRE(drone.getPathLength() == 4);

    Position currPosition = drone.getCurrentPos();
    REQUIRE(currPosition.x == 1);
    REQUIRE(currPosition.y == 1);
    REQUIRE(drone.moveWithOneStep());

    currPosition = drone.getCurrentPos();
    REQUIRE(currPosition.x == 2);
    REQUIRE(currPosition.y == 2);
    REQUIRE(drone.moveWithOneStep());

    currPosition = drone.getCurrentPos();
    REQUIRE(currPosition.x == 3);
    REQUIRE(currPosition.y == 3);
    REQUIRE(drone.moveWithOneStep());

    currPosition = drone.getCurrentPos();
    REQUIRE(currPosition.x == 4);
    REQUIRE(currPosition.y == 4);
    REQUIRE_FALSE(drone.moveWithOneStep());
}