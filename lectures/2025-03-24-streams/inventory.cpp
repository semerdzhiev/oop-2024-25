#include <fstream>
#include <iostream>
#include <limits>

int main()
{
    const size_t max_size = std::numeric_limits<std::streamsize>::max();

    const size_t buffer_size = 100;
    char item[buffer_size];
    char country[buffer_size];
    int quantity;
    double price;

    std::ifstream input("inventory.txt");

    while(input) {
        input.getline(item, buffer_size, ',');
        input.getline(country, buffer_size, ',');
        input >> quantity;
        input.ignore(max_size, ','); // discard the delimeter after the quantity
        input >> price;
        input.ignore(max_size, '\n'); // discard the newline after the price

        if(input) {
            std::cout
                << quantity << " "
                << item << " from "
                << country << " at "
                << price << std::endl;
        }
        else if(input.eof()) {
            std::cout << "[EOF]\n";
        }
        else {
            input.clear();
            std::cerr
                << "ERROR at pos "
                << input.tellg()
                << "!\n";
        }
    }
}