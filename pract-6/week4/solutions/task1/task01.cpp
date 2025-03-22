#include <iostream>
#include <fstream>

void writeNumbersToFile(const char* fileName, unsigned int n) {
    if (!fileName) {
        std::cerr << "Invalid parameter!";
        return;
    }

    std::ofstream outFile(fileName);
    if (!outFile.is_open()) {
        std::cerr << "Error!" << std::endl;
        return;
    }

    for (int i = 0; i <= n; ++i) {
        outFile << i << ' ';
    }
}

int main() {
    writeNumbersToFile("task01Output", 10);
}