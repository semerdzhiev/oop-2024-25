#include "DroneShow.hpp"
#include <cstring>
#include <iostream>

bool DroneShow::isEmpty(unsigned position) const {
    if(position >= MAX_DRONES)
        return true;
    return (this->drones[position] == nullptr);
}

DroneShow::DroneShow(const char* _name, Drone* drArr[], int droneSize) {
    std::strncpy(this->name, _name, MAX_NAME_SIZE - 1);
    this->name[MAX_NAME_SIZE - 1] = '\0';
    
    for (unsigned int i = 0; i < MAX_DRONES; i++) {
        drones[i] = nullptr;
    }

    for (int i = 0; i < droneSize && i < (int)MAX_DRONES; i++) {
        drones[i] = drArr[i];
    }
}

void DroneShow::play() {
    bool proceed = true;

    while(proceed) {
        for (unsigned int i = 0; i < MAX_DRONES; i++) {

            if(drones[i] != nullptr) {
                drones[i]->printCurrentCoordinates();

                if(!drones[i]->canMove()) {
                    proceed = false;
                }

                drones[i]->moveWithOneStep();
            
            }
        }
    }
}
