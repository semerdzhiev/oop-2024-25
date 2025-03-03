#include <iostream>
#include <fstream>

int main()
{
	std::ofstream file("myFile.txt");

	if (!file.is_open())
	{
		std::cout << "Error!" << std::endl;
		return -1;
	}
	
	int a = 3;
	int b = 10;

	file << a << " " << b << " " << a + b << std::endl;

	file.close();
}