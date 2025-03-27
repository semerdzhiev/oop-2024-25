#include <iostream>

int main()
{
    const size_t size = 100;
    char buffer[size];

    std::cout
        << "Enter a sequence of words, each less than " << size << " characters.\n"
        << "Multiple words can be entered on the same line, separated by whitespace.\n"
        << "They will be echoed back to you.\n"
        << "Enter [Ctrl]+[Z] to end.\n";

    while(std::cin >> buffer)
        std::cout << "#" << buffer << "\n";
}