#include <iostream>
#include <fstream>

int main() {
    std::ifstream file("./task02.cpp");
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return -1;
    }

    char line[1024];
    while (file.getline(line, sizeof(line))) {
        std::cout << line << std::endl;
    }
}