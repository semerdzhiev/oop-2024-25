#pragma once
#include "Drone.h"

class DroneShow {
    char name[128];
    Drone drones[64];
    size_t droneCount;

   public:
    DroneShow(const char _name[128], const Drone _drones[64], const size_t _droneCount);
    void play();
};