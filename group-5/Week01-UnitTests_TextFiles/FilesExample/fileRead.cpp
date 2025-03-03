#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    // We have ate flag (at the end) -> positional pointers are at the end
	std::fstream file("myFile.txt", fstream::in | fstream::out | fstream::ate);

	if (!file.is_open())
	{
		std::cout << "Error!" << std::endl;
		return -1;
	}
	
    // Print positional pointers
    cout << "tellg: " << file.tellg() << endl;
    cout << "tellp: " << file.tellp() << endl;

    // Set the positional pointers at the beginning
    file.seekg(0);
    
    cout << "tellg: " << file.tellg() << endl;
    cout << "tellp: " << file.tellp() << endl;
    
    // Reading from the file moves the positional pointers
    int a, b;
    file >> a >> b;

    std::cout << a << " " << b << endl;

    // Print positional pointers
    cout << "tellg: " << file.tellg() << endl;
    cout << "tellp: " << file.tellp() << endl;

    // Writing to the file moves the positional pointers
    file << "hi" << endl;
    
    // Print positional pointers
    cout << "tellg: " << file.tellg() << endl;
    cout << "tellp: " << file.tellp() << endl;

	file.close();
}

/*
Binary representation of numbers example
1101 = 2^3 * 1 + 2^2 *1 + 2^1 *0 + 2^0 *1

Binary operators example
00000010 |
00000100 =
00000110 

00010010 &
00010100 =
00010000 

Useful for understanding the flag's "|" usage
*/