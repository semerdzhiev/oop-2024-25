#include "vector.hpp"
#include <iostream>
#include <cmath>

size_t max(size_t first, size_t second)
{
    return first > second ? first : second;
}

void Vector::_resize(size_t new_capacity)
{
    int* new_data = new int[new_capacity];

    for (size_t i = 0; i < size; ++i)
    {
        new_data[i] = data[i];
    }

    delete[] data;
    data = new_data;

    capacity = new_capacity;
}

void Vector::copy(const Vector& other)
{
    int* new_data = new int[other.capacity];

    for (size_t i = 0; i < other.size; ++i)
    {
        new_data[i] = other.data[i];
    }

    delete[] data;
    data = new_data;

    capacity = other.capacity;
    size = other.size;
}

Vector::Vector()
{
    _resize(capacity);
}

Vector::Vector(size_t initial_capacity) : capacity(initial_capacity)
{
    _resize(capacity);
}

Vector::Vector(size_t initial_capacity, size_t _resize_factor)
    : capacity(initial_capacity), RESIZE_FACTOR(_resize_factor)
{
    _resize(initial_capacity);
}

Vector::Vector(const Vector& other) : RESIZE_FACTOR(other.RESIZE_FACTOR)
{
    copy(other);
}

Vector& Vector::operator=(const Vector& other)
{
    if (this != &other)
    {
        copy(other);
    }
    return *this;
}

Vector::~Vector()
{
    delete[] data;
}

size_t Vector::getSize() const
{
    return size;
}

size_t Vector::getCapacity() const
{
    return capacity;
}

float Vector::getResizeFactor() const
{
    return RESIZE_FACTOR;
}

void Vector::push_back(int value)
{
    if (size >= capacity)
    {
        _resize(capacity * RESIZE_FACTOR);
    }

    data[size++] = value;
}

void Vector::pop_back()
{
    if (size > 0)
    {
        --size;
    }
    else
    {
        std::cerr << "Error: Cannot pop from an empty vector." << std::endl;
    }
}

int& Vector::operator[](size_t index)
{
    return data[index];
}

const int& Vector::operator[](size_t index) const
{
    return data[index];
}

int& Vector::at(size_t index)
{
    if (index >= size)
    {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

const int& Vector::at(size_t index) const
{
    if (index >= size)
    {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

int& Vector::front()
{
    return data[0];
}

const int& Vector::front() const
{
    return data[0];
}

int& Vector::back()
{
    return data[size - 1];
}

const int& Vector::back() const
{
    return data[size - 1];
}

void Vector::resize(size_t new_capacity, int value)
{
    int* new_data = new int[new_capacity];

    for (size_t i = 0; i < size; ++i)
    {
        new_data[i] = data[i];
    }
    for (size_t i = size; i < new_capacity; i++)
    {
        new_data[i] = value;
    }

    delete[] data;
    data = new_data;

    capacity = new_capacity;
    size = size <= capacity ? size : capacity;
}

bool Vector::empty() const
{
    return size == 0;
}

void Vector::reserve(size_t new_capacity)
{
    if (new_capacity > capacity)
    {
        _resize(new_capacity);
    }
}

void Vector::shrink_to_fit()
{
    if (size < capacity)
    {
        _resize(size);
    }
}

void Vector::insert(int* list, size_t size)
{
    if (capacity - this->size < size)
    {
        size_t new_size = max(capacity * RESIZE_FACTOR, this->size + size);
        _resize(new_size);
    }

    for (size_t i = 0; i < size; ++i)
    {
        data[this->size + i] = list[i];
    }

    this->size += size;
}

void Vector::clear()
{
    size = 0;
}

istream& operator>>(istream& is, Vector& vector)
{
    int value;
    
    while (is >> value)
    {
        vector.push_back(value);
    }
    return is;
}

ostream& operator<<(ostream& os, const Vector& vector)
{
    os << vector.getSize() << " ";
    
    for (size_t i = 0; i < vector.size; ++i)
    {
        if (i != vector.size - 1)
            os << vector.data[i] << " ";
        else
            os << vector.data[i];   
    }

    return os;
}