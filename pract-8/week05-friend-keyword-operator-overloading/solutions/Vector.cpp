#include "Vector.hpp"

#include <iostream>
#include <algorithm>  
#include <stdexcept>   

const unsigned DEFAULT_CAPACITY = 16;

Vector::Vector() : size(0), capacity(DEFAULT_CAPACITY) {
    data = new int[capacity];
}

Vector::Vector(const Vector& other)
    : size(other.size), capacity(other.capacity) {
    data = new int[capacity];
    std::copy(other.data, other.data + size, data);
}

Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        delete[] data;
        size = other.size;
        capacity = other.capacity;
        data = new int[capacity];
        std::copy(other.data, other.data + size, data);
    }
    return *this;
}

Vector::~Vector() {
    delete[] data;
}

void Vector::resize(unsigned new_capacity) {

    if (new_capacity < size) {
        new_capacity = size;
    }
    int* new_data = new int[new_capacity];
    std::copy(data, data + size, new_data);
    delete[] data;
    data = new_data;
    capacity = new_capacity;
}

void Vector::push_back(int value) {
    if (size == capacity) {
        resize(capacity * 2);
    }
    data[size++] = value;
}

void Vector::pop_back() {
    if (size == 0) {
        throw std::out_of_range("pop_back() called on empty vector");
    }
    --size;

    if (size < capacity / 4 && capacity > 1) {
        resize(capacity / 2);
    }
}

int Vector::at(unsigned index) const {
    if (index >= size)
        throw std::out_of_range("Index out of range");
    return data[index];
}

void Vector::insert_at(unsigned index, int value) {
    if (index > size) {
        throw std::out_of_range("Index out of range for insert");
    }

    if (size == capacity) {
        resize(capacity * 2);
    }

    for (unsigned i = size; i > index; --i) {
        data[i] = data[i - 1];
    }

    data[index] = value;
    ++size;
}

void Vector::delete_at(unsigned index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range for delete");
    }

    for (unsigned i = index; i < size - 1; ++i) {
        data[i] = data[i + 1];
    }
    --size;

    if (size < capacity / 4 && capacity > 1) {
        resize(capacity / 2);
    }
}

void Vector::sort() {
    std::sort(data, data + size);
}

void Vector::concat(const Vector& other) {
    if (size + other.size > capacity) {
        resize((size + other.size) * 2);
    }

    for (unsigned i = 0; i < other.size; ++i) {
        data[size + i] = other.data[i];
    }

    size += other.size;
}

Vector Vector::slice(unsigned start, unsigned end) const {
    if (start > end || end > size) {
        throw std::out_of_range("Invalid slice indices");
    }

    Vector result;
    result.resize(end - start);
    result.size = end - start;

    for (unsigned i = start; i < end; ++i) {
        result.data[i - start] = data[i];
    }

    return result;
}

void Vector::reverse() {
    std::reverse(data, data + size);
}

int Vector::operator[](unsigned index) const {
    return data[index];
}


void Vector::operator+(const Vector& other) {
    concat(other);
}

bool Vector::operator==(const Vector& other) const {
    if (size != other.size) {
        return false;
    }

    for (unsigned i = 0; i < size; ++i) {
        if (data[i] != other.data[i])
            return false;
    }

    return true;
}


int Vector::operator*(const Vector& other) const {
    unsigned minSize = (size < other.size ? size : other.size);
    int sum = 0;

    for (unsigned i = 0; i < minSize; ++i) {
        sum += data[i] * other.data[i];
    }

    return sum;
}

std::ostream& operator<<(std::ostream& os, const Vector& vector) {
    os << "[";

    for (unsigned i = 0; i < vector.size; ++i) {
        os << vector.data[i];

        if (i != vector.size - 1) {
            os << ", ";
        }
    }

    os << "]";
    return os;
}
