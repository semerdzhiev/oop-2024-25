#include "DroneShow.h"

#include <cstring>

DroneShow::DroneShow(const char _name[128], const Drone _drones[64], const size_t _droneCount) : droneCount(_droneCount) {
    strcpy(name, _name);

    for (size_t i = 0; i < droneCount; ++i) {
        drones[i] = _drones[i];
    }
}

void DroneShow::play() {
    if (droneCount == 0) return;

    while (drones[0].hasRemainingPath()) {
        for (size_t i = 0; i < droneCount; ++i) {
            drones[i].printCurrentPos();
            std::cout << ' ';

            drones[i].moveWithOneStep();
        }
        std::cout << std::endl;
    }
}
