#include <iostream>
#include <sstream>

void process_line(std::stringstream& str)
{
    const size_t size = 4;
    char buffer[size];

    int chunk = 0;

    while(str) {
        str.getline(buffer, size);

        if(str.bad()) {
            // An error has occurred.
            std::cout << "ERROR!\n";
        }

        std::cout << "Chunk " << chunk++ << ": " << buffer << std::endl;

        if(str.fail()) {
            // In this case reading stopped because the buffer
            // was filled up, but the delimeter was not reached.
            str.clear(); // clear the error, so that reading can continue.
        }
        else if(str.eof()) {
            // In this case the data has been read successfully
            // and reading stopped because EOF was hit.
            std::cout << "[EOF]\n";
            break;
        }
        else if(str.good()) {
            // In this case the data has been read successfully
            // and reading stopped because the delimeter was reached.
            break;
        }
    }
}

int main()
{
    std::stringstream str("A long line of text.\nAnd another one");

    // Note that "str" is equivalent to "!str.fail()",
    // which is different from "str.good()"
    // Try changing "str.good()" to "str" below.
    for(int line = 0; str.good(); ++line) {
        std::cout << "# Line " << line << std::endl;
        process_line(str);
    }
}