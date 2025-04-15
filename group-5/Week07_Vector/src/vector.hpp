#pragma once
#include <iostream>

using namespace std;

const int DEFAULT_CAPACITY = 4;
const int DEFAULT_RESIZE_FACTOR = 2;

class Vector
{
private:
    const float RESIZE_FACTOR = DEFAULT_RESIZE_FACTOR;

    size_t capacity = DEFAULT_CAPACITY;
    size_t size = 0;

    int* data = nullptr;

    void _resize(size_t new_capacity);
    void copy(const Vector& other);

public:
    Vector();
    Vector(size_t initial_capacity);
    Vector(size_t initial_capacity, size_t resize_factor);
    Vector(const Vector& other);
    Vector& operator=(const Vector& other);

    ~Vector();

    size_t getSize() const;
    size_t getCapacity() const;
    float getResizeFactor() const;

    void push_back(int value);
    void pop_back();

    int& operator[](size_t index);
    const int& operator[](size_t index) const;

    int& at(size_t index);
    const int& at(size_t index) const;

    int& front();
    const int& front() const;

    int& back();
    const int& back() const;

    void resize(size_t new_capacity, int value = 0);

    bool empty() const;

    void reserve(size_t new_capacity);
    void shrink_to_fit();

    void insert(int *list, size_t size);
    void clear();

    friend ostream& operator<<(ostream &os, const Vector &vector);
    friend istream& operator>>(istream &is, Vector &vector);  
};