#pragma once

#include "Drone.hpp"

const unsigned int MAX_NAME_SIZE = 127;
const unsigned int MAX_DRONES = 1024;

class DroneShow {
private:
    char name[MAX_NAME_SIZE];
    Drone* drones[MAX_DRONES];

public:
    DroneShow(const char* name, Drone* drones[], int droneSize);
    bool isEmpty(unsigned position) const;
    void play();
};