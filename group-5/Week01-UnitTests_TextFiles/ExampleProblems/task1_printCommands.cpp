#include <iostream>
#include <fstream>

using namespace std;

const int MAX_LINE_SIZE = 10000;

int main(int argc, const char* argv[])
{
    for (size_t i = 0; i < argc; i++)
    {
        cout << argv[i] << endl;
    }
}