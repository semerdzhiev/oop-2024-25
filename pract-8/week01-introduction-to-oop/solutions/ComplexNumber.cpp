#include "ComplexNumber.hpp"

ComplexNumber::ComplexNumber() : real(0), imag(0) {}
ComplexNumber::ComplexNumber(double r, double i) : real(r), imag(i) {}

ComplexNumber ComplexNumber::add(const ComplexNumber &other) const {
    return ComplexNumber(real + other.real, imag + other.imag);
}

ComplexNumber ComplexNumber::subtract(const ComplexNumber &other) const {
    return ComplexNumber(real - other.real, imag - other.imag);
}

ComplexNumber ComplexNumber::multiply(const ComplexNumber &other) const {
    double r = real * other.real - imag * other.imag;
    double i = real * other.imag + imag * other.real;
    return ComplexNumber(r, i);
}

void ComplexNumber::print() const {
    std::cout << real;
    if (imag >= 0)
        std::cout << " + " << imag << "i";
    else
        std::cout << " - " << -imag << "i";
    std::cout << std::endl;
}