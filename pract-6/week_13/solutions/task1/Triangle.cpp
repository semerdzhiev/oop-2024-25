#include "Triangle.h"

#include <math.h>

#include <iostream>

void Triangle::printInfo() const {
    std::cout << "Hello, I am a triangle! I have three sides: "
              << a << ", " << b << " and " << c << "!" << std::endl;
    std::cout << "My perimeter is " << this->perimeter() << "and my area is " << this->area() << "!";
}

double Triangle::area() const {
    double halfP = this->perimeter() / 2;
    return std::sqrt(halfP * (halfP - a) * (halfP - b) * (halfP - c));
}

double Triangle::perimeter() const {
    return a + b + c;
}
