#include "Interval.hpp"
#include <iostream>
#include <cmath>

Interval::Interval(): a(0), b(0) {}

Interval::Interval(int a, int b) : Interval() {
    if (a <= b) {
        this->a = a;
        this->b = b;
    }
}

void Interval::setA(int a) {
    if (a > this->b)
        a = this->b;
    this->a = a;
}

void Interval::setB(int b) {
    if (b < this->a)
        b = this->a;
    this->b = b;
}

int Interval::getA() const {
    return this->a;
}

int Interval::getB() const {
    return this->b;
}

int Interval::length() const {
    return b - a + 1;
}

bool Interval::contains(int num) const {
    return num >= a && num <= b;
}

int Interval::calcPrimeNumbersInTheInterval() const {
    int count = 0;
    for (int i = a; i <= b; ++i) {
        if (isPrime(i)) count++;
    }
    return count;
}

int Interval::calcPalindromeNumbersInTheInterval() const {
    int count = 0;
    for (int i = a; i <= b; ++i) {
        if (isPalindrome(i)) count++;
    }
    return count;
}

int Interval::calcUniqueDigitNumbersInTheInterval() const {
    int count = 0;
    for (int i = a; i <= b; ++i) {
        if (hasUniqueDigits(i)) count++;
    }
    return count;
}

bool Interval::isPowerOfTwoInterval() const {
    return isPowerOfTwo(a) && isPowerOfTwo(b);
}

Interval Interval::intersect(const Interval& other) const {
    int start = std::max(a, other.a);
    int end = std::min(b, other.b);
    if (start <= end) {
        return Interval(start, end);
    }
    return Interval(0, 0);
}

bool Interval::isSuperInterval(const Interval& other) const {
    return a <= other.a && b >= other.b;
}

void Interval::print() const {
    std::cout << "[" << a << ", " << b << "]" << std::endl;
}

bool Interval::isPrime(int num) const {
    if (num <= 1) return false;
    for (int i = 2; i <= std::sqrt(num); ++i) {
        if (num % i == 0) return false;
    }
    return true;
}

bool Interval::isPalindrome(int num) const {
    int original = num, reversed = 0;
    while (num > 0) {
        reversed = reversed * 10 + num % 10;
        num /= 10;
    }
    return original == reversed;
}

bool Interval::hasUniqueDigits(int num) const {
    bool digits[10] = { false };
    while (num > 0) {
        int digit = num % 10;
        if (digits[digit]) return false;
        digits[digit] = true;
        num /= 10;
    }
    return true;
}

bool Interval::isPowerOfTwo(int num) const {
    return (num > 0) && (num & (num - 1)) == 0;
}
