#include <iostream>
#include <cstddef>
#include <fstream>

// position - current position of input stream
// (in the case the input stream is at the begining when calling the function)
// File   : dkjfkasdflasdfkkasldfjaldfj
// get pos: |
// Step 1:                             |
// Step 2:  |

size_t SizeOfFile(std::ifstream &f){
    // Store position of next char to read
    size_t position = f.tellg();

    // Step 1:
    // Move to the end of the file (0 distance from the end)
    f.seekg(0, std::ios::end);

    // Gets the position of the input stream, which is at the end
    // This equals the file size.
    size_t size = f.tellg();

    // Step 2:
    // Returns the position of the input stream in the original state
    f.seekg(position);

    return size;
}

int main()
{
    std::ifstream ifs("test.txt");

    if (!ifs.is_open())
    {
		std::cout << "Error!" << std::endl;
		return -1;
    }

    std::cout << SizeOfFile(ifs) << '\n';
    return 0;
}