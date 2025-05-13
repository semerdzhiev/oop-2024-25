#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio> // За sprintf
#include "Drone.hpp"
#include "DroneShow.hpp"

const int MAX_DRONES_COUNT = MAX_DRONES;

int main() {
    const char* binaryFileName = "drone.bin";

    std::ifstream textFile("dronesPath.txt");
    if (!textFile) {
        std::cerr << "Failed to open the text file dronesPath.txt\n";
        return 1;
    }

    Drone* dronePointers[MAX_DRONES_COUNT];
    int droneCount = 0;
    const int lineSize = 256;
    char line[lineSize];
    int droneIndex = 0;

    while (textFile.getline(line, lineSize) && droneCount < MAX_DRONES_COUNT) {
        if (std::strlen(line) == 0)
            continue;

        std::ofstream binaryFile(binaryFileName, std::ios::binary);
        if (!binaryFile) {
            std::cerr << "Failed to open binary file " << binaryFileName << " for writing.\n";
            continue;
        }

        char* token = std::strtok(line, " ");
        while (token != nullptr) {
            double x = std::atof(token);
            token = std::strtok(nullptr, " ");
            if (token == nullptr)
                break;
            double y = std::atof(token);
            token = std::strtok(nullptr, " ");

            binaryFile.write((char*)&x, sizeof(double));
            binaryFile.write((char*)&y, sizeof(double));
        }
        binaryFile.close();

        char droneId[32] = "Drone_";
        std::sprintf(droneId + std::strlen(droneId), "%d", droneIndex);

        try {
            dronePointers[droneCount] = new Drone(binaryFileName, droneId);
        } catch (std::exception &e) {
            std::cerr << "Error creating Drone: " << e.what() << "\n";
            continue;
        }

        droneCount++;
        droneIndex++;
    }

    textFile.close();

    if (droneCount == 0) {
        std::cout << "No drones were created.\n";
        return 0;
    }

    char showName[] = "My Drone Show";
    DroneShow droneShow(showName, dronePointers, droneCount);
    droneShow.play();

    for (int i = 0; i < droneCount; i++) {
        delete dronePointers[i];
    }

    return 0;
}
