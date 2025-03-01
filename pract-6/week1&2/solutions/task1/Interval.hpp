#ifndef INTERVAL_HPP
#define INTERVAL_HPP

class Interval {
private:
    int a;#pragma once

class Interval {
private:
    int a;
    int b;

public:
    // Constructors
    Interval();
    Interval(int a, int b);

    // Setters and Getters
    void setA(int a);
    void setB(int b);
    int getA() const;
    int getB() const;

    // Member functions
    int length() const;
    bool contains(int num) const;
    int calcPrimeNumbersInTheInterval() const;
    int calcPalindromeNumbersInTheInterval() const;
    int calcUniqueDigitNumbersInTheInterval() const;
    bool isPowerOfTwoInterval() const;
    Interval intersect(const Interval& other) const;
    bool isSuperInterval(const Interval& other) const;
    void print() const;

private:
    // Helper functions
    bool isPrime(int num) const;
    bool isPalindrome(int num) const;
    bool hasUniqueDigits(int num) const;
    bool isPowerOfTwo(int num) const;
};

    int b;

public:
    // Constructors
    Interval();
    Interval(int a, int b);

    // Setters and Getters
    void setA(int a);
    void setB(int b);
    int getA() const;
    int getB() const;

    // Member functions
    int length() const;
    bool contains(int num) const;
    int calcPrimeNumbersInTheInterval() const;
    int calcPalindromeNumbersInTheInterval() const;
    int calcUniqueDigitNumbersInTheInterval() const;
    bool isPowerOfTwoInterval() const;
    Interval intersect(const Interval& other) const;
    bool isSuperInterval(const Interval& other) const;
    void print() const;

private:
    // Helper functions
    bool isPrime(int num) const;
    bool isPalindrome(int num) const;
    bool hasUniqueDigits(int num) const;
    bool isPowerOfTwo(int num) const;
};

#endif // INTERVAL_HPP
