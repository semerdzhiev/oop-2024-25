#pragma once
#include <iostream>

#include "Position.h"

class Drone {
    char* id;
    Position path[32];
    size_t currPos;
    size_t pathLength;

    void copy(const Drone& other);
    void free();

   public:
    Drone();
    Drone(const char* _id, const Position* _path, const size_t _pathLength);
    ~Drone();

    Drone(const Drone& other);
    Drone& operator=(const Drone& other);

    char* getId() const;
    size_t getPathLength() const;

    Position getCurrentPos() const;
    void printCurrentPos() const;
    void printRemainingPath() const;
    bool hasRemainingPath() const;
    bool moveWithOneStep();
};