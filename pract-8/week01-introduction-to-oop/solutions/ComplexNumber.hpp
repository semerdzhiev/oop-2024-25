#ifndef COMPLEX_NUMBER_HPP_
#define COMPLEX_NUMBER_HPP_

#include <iostream>

struct ComplexNumber {
    double real;
    double imag;

    ComplexNumber();
    ComplexNumber(double r, double i);

    ComplexNumber add(const ComplexNumber &other) const;
    ComplexNumber subtract(const ComplexNumber &other) const;
    ComplexNumber multiply(const ComplexNumber &other) const;
    void print() const;
};

#endif // COMPLEX_NUMBER_HPP