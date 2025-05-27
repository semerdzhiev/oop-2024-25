#pragma once
#include "Shape.h"

class Circle : public Shape {
    protected:
    double r;
   public:
    Circle(double _r) : Shape(0), r(r) {}

    void printInfo() const override;
    double area() const override;
    double perimeter() const override;
};