#include "Drone.h"

#include <cstring>

void Drone::copy(const Drone& other) {
    size_t idLength = strlen(other.id);
    id = new char[idLength + 1];
    strcpy(id, other.id);

    pathLength = other.pathLength;

    for (size_t i = 0; i <= pathLength; ++i) {
        path[i] = other.path[i];
    }
}

void Drone::free() {
    delete[] id;
    id = nullptr;
    currPos = 0;
    pathLength = 0;
}

Drone::Drone() : id(nullptr), pathLength(0), currPos(0) {}

Drone::Drone(const char* _id, const Position* _path, const size_t _pathLength) : pathLength(_pathLength), currPos(0) {
    size_t idLength = strlen(_id);
    id = new char[idLength + 1];
    strcpy(id, _id);

    for (size_t i = 0; i < pathLength; ++i) {
        path[i] = _path[i];
    }
}

Drone::~Drone() {
    free();
}

Drone::Drone(const Drone& other) {
    copy(other);
}

Drone& Drone::operator=(const Drone& other) {
    if (this != &other) {
        free();
        copy(other);
    }
    return *this;
}

char* Drone::getId() const {
    return id;
}

size_t Drone::getPathLength() const {
    return pathLength;
}

Position Drone::getCurrentPos() const {
    return path[currPos];
}

void Drone::printCurrentPos() const {
    path[currPos].print();
}

void Drone::printRemainingPath() const {
    for (size_t i = 0; i < pathLength - currPos - 1; ++i) {
        path[currPos + i + 1].print();
    }
}

bool Drone::hasRemainingPath() const {
    return currPos + 1 < pathLength;
}

bool Drone::moveWithOneStep() {
    if (!hasRemainingPath()) return false;

    ++currPos;
    
    return true;
}
