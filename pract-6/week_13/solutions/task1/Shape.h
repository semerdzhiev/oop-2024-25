#pragma once

class Shape {
   protected:
    unsigned sideCount;
   public:
    Shape(unsigned _sideCount) : sideCount(_sideCount) {}
    virtual ~Shape() = default;

    virtual void printInfo() const = 0;
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
};