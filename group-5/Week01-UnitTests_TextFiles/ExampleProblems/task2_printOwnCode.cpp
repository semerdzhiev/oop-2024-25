#include <iostream>
#include <fstream>

using namespace std;

const int MAX_LINE_SIZE = 10000;

// argc is the number of arguments received when starting the program
// argv contains the arguments
// The first argument (at index 0) is always the name of the program
int main(int argc, const char* argv[])
{
    // Checks if there are no arguments except the name of the program
    if (argc < 2)
    {
        cout << "Not enough arguments" << endl;
        return -1;
    }

    std::fstream file(argv[1], fstream::in);

    // Checks if the file opened correctly
    if (!file.is_open())
    {
		std::cout << "Error!" << std::endl;
		return -1;
    }

    char temp[MAX_LINE_SIZE];

    while(!file.eof())
    {
        file.getline(temp, MAX_LINE_SIZE);
        cout << temp << endl;
    }

    // After finishing using the file, we always close it
    file.close();
}