#include <iostream>
#include <fstream>

int countNonEmptyCharacters(const char* fileName) {
    if (!fileName) {
        std::cerr << "Invalid parameter!";
        return -1;
    }

    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error! Couldn't open the file for reading: \"" << fileName << "\"" << std::endl;
        return -1;
    }

    int result = 0;
    char c;
    while (file.get(c)) {
        if (c != ' ') {
            ++result;
        }
    }

    return result;
}

int main() {
    std::cout << countNonEmptyCharacters("task04Input.txt");
}