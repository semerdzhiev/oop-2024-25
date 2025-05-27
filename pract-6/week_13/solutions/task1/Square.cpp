#include <math.h>

#include <iostream>

#include "Square.h"

void Square::printInfo() const {
    std::cout << "Hello, I am a square! I have one side - " << a << "!" << std::endl;
    std::cout << "My perimeter is " << this->perimeter() << "and my area is " << this->area() << "!";
}

double Square::area() const {
    return a * a;
}

double Square::perimeter() const {
    return a * 4;
}
