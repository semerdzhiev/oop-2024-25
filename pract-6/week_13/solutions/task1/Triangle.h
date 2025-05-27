#pragma once
#include "Shape.h"

class Triangle : public Shape {
    protected:
    double a, b, c;
   public:
    Triangle(double _a, double _b, double _c) : Shape(3), a(_a), b(_b), c(_c) {
        // Валидацията е оставена за упражнение на читателя...
    }
    void printInfo() const override;
    double area() const override;
    double perimeter() const override;
};