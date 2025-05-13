#include "Drone.hpp"
#include <stdexcept>
#include <cstring>
#include <iostream>
#include <fstream>

Drone::Drone(const char* fileName, const char* id) {
    this->currentPosition = 0;
    this->pathSize = 0;

    this->id = new char[std::strlen(id) + 1];
    std::strncpy(this->id, id, std::strlen(id) + 1);

    std::ifstream input(fileName, std::ios::binary);
    if (!input.is_open()) {
        throw std::invalid_argument("Invalid filename!");
    }

    // The commented code does not work correctly!
    // while (!input.eof()) {
    //     double x, y;
    //     input.read((char*)&x, sizeof(x));
    //     input.read((char*)&y, sizeof(y));
    //     Point2D currentP(x, y);
    //     coordinates[pathSize] = currentP;
    //     pathSize++;
    // }

    double x, y = 0;
    while (input.read(reinterpret_cast<char*>(&x), sizeof(x)) &&
           input.read(reinterpret_cast<char*>(&y), sizeof(y))) {
        Point2D currentP(x, y);
        coordinates[pathSize] = currentP;
        pathSize++;
    }
    input.close();
}

Drone::Drone(const Drone& other) {
    this->currentPosition = other.currentPosition;
    this->pathSize = other.pathSize;
    
    this->id = new char[std::strlen(other.id) + 1];
    std::strncpy(this->id, other.id, std::strlen(other.id) + 1);
    
    for (int i = 0; i < this->pathSize; ++i) {
        this->coordinates[i] = other.coordinates[i];
    }
}

Drone& Drone::operator=(const Drone& other) {
    if (this != &other) {
        delete[] this->id;
        
        this->currentPosition = other.currentPosition;
        this->pathSize = other.pathSize;
        
        this->id = new char[std::strlen(other.id) + 1];
        std::strncpy(this->id, other.id, std::strlen(other.id) + 1);
        
        for (int i = 0; i < this->pathSize; ++i) {
            this->coordinates[i] = other.coordinates[i];
        }
    }
    return *this;
}

Drone::~Drone() {
    delete[] this->id;
    this->id = nullptr;
}

void Drone::printGeneratedPath() const {
    for (int i = 0; i < pathSize; ++i) {
        Point2D p = this->coordinates[i];
        std::cout << "(" << p.x << ", " << p.y << ")\n";
    }
}

void Drone::moveWithOneStep() {
    this->currentPosition++;
}

void Drone::printCurrentCoordinates() const {
    double x = coordinates[currentPosition].x;
    double y = coordinates[currentPosition].y;
    std::cout << "Drone " << this->id << " is at " << "(" << x << ", " << y << ")" << "\n";
}
bool Drone::canMove() const {
    return currentPosition  + 1 < pathSize;
}

int Drone::getPathSize() const {
    return this->pathSize;
}