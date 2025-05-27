#pragma once
#include "Shape.h"

class Square : public Shape {
   protected:
    double a;

   public:
    Square(double _a) : Shape(4), a(_a) {}

    void printInfo() const override;
    double area() const override;
    double perimeter() const override;
};