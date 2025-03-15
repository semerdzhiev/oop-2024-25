#include "Sumator.hpp"

Sumator::Sumator() : size(0), capacity(10) {
    arr = new(std::nothrow) int[capacity];
    if (!arr) {
        std::cerr << "Memory allocation failed!" << std::endl;
    }
}

Sumator::Sumator(int capacity) : size(0), capacity(capacity) {
    arr = new(std::nothrow) int[capacity];
    if (!arr) {
        std::cerr << "Memory allocation failed!" << std::endl;
    }
}

Sumator::Sumator(const Sumator& other) {
    copyFrom(other);
}

Sumator& Sumator::operator=(const Sumator& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

Sumator::~Sumator() {
    free();
}

void Sumator::add(int num) {
    if (size >= capacity) {
        resize();
    }
    if (arr) {
        arr[size++] = num;
    }
}

void Sumator::removeLast() {
    if (size > 0) {
        size--;
    }
}

void Sumator::changeAt(int num, int index) {
    if (index >= 0 && index < size) {
        arr[index] = num;
    } else {
        std::cerr << "Index out of bounds!" << std::endl;
    }
}

int Sumator::getSum() const {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += std::pow(arr[i], i);
    }
    return sum;
}

void Sumator::print() const {
    std::cout << "Array: ";
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

void Sumator::resize() {
    int newCapacity = capacity * 2;
    int* newArr = new(std::nothrow) int[newCapacity];
    if (newArr) {
        for (int i = 0; i < size; i++) {
            newArr[i] = arr[i];
        }
        free();
        arr = newArr;
        capacity = newCapacity;
    } else {
        std::cerr << "Memory allocation failed during resizing!" << std::endl;
    }
}

void Sumator::copyFrom(const Sumator& other) {
    size = other.size;
    capacity = other.capacity;
    arr = new(std::nothrow) int[capacity];
    if (arr) {
        for (int i = 0; i < size; i++) {
            arr[i] = other.arr[i];
        }
    } else {
        std::cerr << "Memory allocation failed trying to copy data!" << std::endl;
    }
}

void Sumator::free() {
    delete[] arr;
}