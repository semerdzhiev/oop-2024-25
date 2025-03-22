#include <iostream>
#include <fstream>

bool appendFileContent(const char* sourceFileName, const char* destinationFileName) {
    if (!sourceFileName || !destinationFileName) {
        std::cerr << "Invalid parameters!";
        return false;
    }

    std::ifstream srcFile(sourceFileName);
    if (!srcFile.is_open()) {
        std::cerr << "Error! Couldn't open the file for reading: \"" << sourceFileName << "\"" << std::endl;
        return false;
    }

    std::ofstream destFile(destinationFileName, std::ios::app);
    if (!destFile.is_open()) {
        std::cerr << "Error! Couldn't open the file for writing: \"" << destinationFileName << "\"" << std::endl;
        return false;
    }

    char buffer[1024];
    while (srcFile.getline(buffer, sizeof(buffer))) {
        destFile << buffer << std::endl;
    }

    // srcFile.close(); destFile.close();

    return true;
}

int main() {
    if (appendFileContent("task5Input.txt", "task5Output.txt")) {
        std::cout << "Success!";
    }
}