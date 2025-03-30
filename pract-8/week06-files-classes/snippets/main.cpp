#include "Person.hpp"
#include <iostream>
#include <fstream>

int main() {

	const char textFilePath[] = ".\\person.txt";
    const char binaryFilePath[] = ".\\person.bin";

	std::ofstream out(textFilePath);

	Person person("Ivan", "Draganov", 42);
	person.serialize(out);
	out.close();

	std::ifstream in(textFilePath);
	Person readFromFile;
	readFromFile.deserialize(in);
	readFromFile.print();
	in.close();

    Person p2("Maria", "Ivanova", 25);

    // RAII
    {
        std::ofstream outBin(binaryFilePath, std::ios::binary);
        if (!outBin) {
            std::cerr << "Cannot open file!" << std::endl;
            return 1;
        }
        p2.serializeBinary(outBin);
    }

    // RAII
    {
        std::ifstream inBin(binaryFilePath, std::ios::binary);
        if (!inBin) {
            std::cerr << "Cannot open file!" << std::endl;
            return 1;
        }
        Person pBin;
        pBin.deserializeBinary(inBin);
        std::cout << "\nBinary serialization:\n";
        pBin.print();
    }

}