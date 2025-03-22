#include <iostream>
#include <fstream>

bool replaceCharInFile(const char* fileName, char oldChar, char newChar) {
    if (!fileName) {
        std::cerr << "Invalid parameter!";
        return false;
    }

    std::ifstream inFile(fileName);
    if (!inFile) {
        std::cerr << "Error! Couldn't open the file for reading: " << fileName << std::endl;
        return false;
    }

    const char* outFileName = "task03Output.txt";
    std::ofstream outFile(outFileName);
    if (!outFile) {
        std::cerr << "Error! Couldn't open the file for writing: " << outFileName << std::endl;
        inFile.close();
        return false;
    }

    char c;
    while (inFile.get(c)) {
        outFile.put(c == oldChar ? newChar : c); 
    }

    //inFile.close(); outFile.close();  // No need. Let RAII handle it
    
    return true;
}

int main() {
    if (replaceCharInFile("task03Input.txt", 'z', 'a')) {
        std::cout << "Success!";
    }
}
