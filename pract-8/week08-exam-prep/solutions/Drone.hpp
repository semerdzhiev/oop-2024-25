#pragma once

#include "Point.hpp"
#include <fstream>
#include <iostream>
#include <cstring>
#include <stdexcept>

class Drone {   
private:
    char* id;
    Point2D coordinates[63];
    unsigned pathSize;
    unsigned currentPosition;

public:
    Drone(const char* fileName, const char* id);
    Drone(const Drone& other);
    Drone& operator=(const Drone& other);
    ~Drone();

    void printGeneratedPath() const;
    void moveWithOneStep();
    void printCurrentCoordinates() const;
    bool canMove() const;
    int getPathSize() const;
};