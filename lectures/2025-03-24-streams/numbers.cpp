#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
	if(argc != 2) {
		std::cout << "Usage: numbers.exe <path>\n";
		return 1;
	}

	std::cout << "Opening \"" << argv[1] << "\" for reading...\n";

	std::ifstream file(argv[1]);

	if( ! file.is_open() ) {
		std::cerr
			<< "ERROR: cannot open "
			<< argv[1]
			<< " for reading.\n";
		return 2;
	}

	std::cout << "Proceed to read numbers from the file:" << std::endl;

	while( ! file.eof() ) {
		int value;
		file >> value;

		if(file.eof()) {
			break;
		}
		else if( ! file.good()) {
			file.clear();
			std::cerr
				<< "ERROR: bad data at position "
				<< file.tellg()
				<< std::endl;
			return 3;
		}

		std::cout << value << std::endl;
	}
}