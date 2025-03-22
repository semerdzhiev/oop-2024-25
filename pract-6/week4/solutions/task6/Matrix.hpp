#pragma once

#include <iostream>
#include <fstream>

class Matrix {
private:
    size_t rows, cols;
    int** data;

    void allocateMemory();
    void copyData(const int* const* source);

public:
    Matrix(size_t n, size_t m);
    Matrix(size_t n, size_t m, const int* const* data);
    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);
    ~Matrix();

    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;

    void readFromFile(const char* fileName);
    void writeToFile(const char* fileName) const;

    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
    friend std::istream& operator>>(std::istream& is, Matrix& matrix);
};