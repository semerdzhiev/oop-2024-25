#include <iostream>
#include <fstream>
#include "vector.hpp"

int main()
{
    Vector vector;

    for (size_t i = 0; i < 10; i++)
    {
        vector.push_back(i);
    }
    
    cout << "Vector: " << vector << endl;

    fstream file("vector.txt", ios::out);
    if (file.is_open())
    {
        file << vector << endl;
        file.close();
    }
}