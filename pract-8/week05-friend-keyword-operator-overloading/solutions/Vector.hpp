#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <iostream>
#include <stdexcept>

class Vector {
private:
    int* data;
    unsigned size;
    unsigned capacity;

    void resize(unsigned new_capacity);

public:
    Vector();
    Vector(const Vector& other);
    Vector& operator=(const Vector& other);
    ~Vector();

    void push_back(int value);
    void pop_back();
    int at(unsigned index) const;
    void insert_at(unsigned index, int value);
    void delete_at(unsigned index);
    void sort();
    void concat(const Vector& other);
    Vector slice(unsigned start, unsigned end) const; 
    void reverse();

    int operator[] (unsigned index) const;
    void operator+(const Vector& other); 
    bool operator==(const Vector& other) const;
    int operator*(const Vector& other) const; 

    friend std::ostream& operator<<(std::ostream& os, const Vector& vector);
};

#endif // VECTOR_HPP_
