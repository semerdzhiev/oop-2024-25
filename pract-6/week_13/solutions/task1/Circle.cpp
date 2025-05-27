#include <math.h>

#include <iostream>

#include "Circle.h"

void Circle::printInfo() const {
    std::cout << "Hello, I am a circle! I don't have any sides, but I have a radius - " << r << "!" << std::endl;
    std::cout << "My perimeter is " << this->perimeter() << "and my area is " << this->area() << "!";
}

double Circle::area() const {
    return M_PI * r * r;
}

double Circle::perimeter() const {
    return 2 * M_PI * r;
}
