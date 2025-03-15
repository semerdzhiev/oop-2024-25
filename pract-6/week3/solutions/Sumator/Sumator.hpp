#pragma once

#include <iostream>
#include <cmath>

class Sumator {
private:
    int* arr;
    int size;
    int capacity;
public:
    Sumator();                  // Default constructor (capacity = 10)
    Sumator(int capacity);       // Parameterized constructor
    Sumator(const Sumator&); // Copy constructor
    Sumator& operator=(const Sumator&); // Copy assignment
    ~Sumator();                  // Destructor

    void add(int);         // Adds a number to the array
    void removeLast();         // Removes the last element
    void changeAt(int, int); // Changes element at given index
    int getSum() const;        // Calculates the sum as per formula
    void print() const;        // Prints the array

private:
    void resize(); // Resizes the array when full
    void copyFrom(const Sumator&); // Helper function to reuse copy logic
    void free(); // Helper function to clean unwanted memory
};
