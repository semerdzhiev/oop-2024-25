#include "Matrix.hpp"

void Matrix::allocateMemory() {
    data = new int* [rows];
    for (size_t i = 0; i < rows; ++i) {
        data[i] = new int[cols] {};
    }
}

void Matrix::copyData(const int* const* source) {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            data[i][j] = source[i][j];
        }
    }
}

Matrix::Matrix(size_t n, size_t m) : rows(n), cols(m) {
    allocateMemory();
}

Matrix::Matrix(size_t n, size_t m, const int* const* inputData) : rows(n), cols(m) {
    allocateMemory();
    copyData(inputData);
}

Matrix::Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
    allocateMemory();
    copyData(static_cast<const int* const*>(other.data));
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        for (size_t i = 0; i < rows; ++i)
            delete[] data[i];
        delete[] data;

        rows = other.rows;
        cols = other.cols;
        allocateMemory();
        copyData(static_cast<const int* const*>(other.data));
    }
    return *this;
}

Matrix::~Matrix() {
    for (size_t i = 0; i < rows; ++i)
        delete[] data[i];
    delete[] data;
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        std::cerr << "Matrix addition error: Sizes must match!" << std::endl;
        return *this;
    }
    Matrix result(rows, cols);
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            result.data[i][j] = data[i][j] + other.data[i][j];

    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        std::cerr << "Matrix subtraction error: Sizes must match!" << std::endl;
        return *this;
    }
    Matrix result(rows, cols);
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            result.data[i][j] = data[i][j] - other.data[i][j];

    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (cols != other.rows) {
        std::cerr << "Matrix multiplication error: Invalid sizes!" << std::endl;
        return *this;
    }
    Matrix result(rows, other.cols);
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < other.cols; ++j)
            for (size_t k = 0; k < cols; ++k)
                result.data[i][j] += data[i][k] * other.data[k][j];

    return result;
}

void Matrix::readFromFile(const char* fileName) {
    std::ifstream file(fileName);
    if (!file) {
        std::cerr << "Error! Couldn't open file for reading: " << fileName << std::endl;
        return;
    }
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            file >> data[i][j];
}

void Matrix::writeToFile(const char* fileName) const {
    std::ofstream file(fileName);
    if (!file) {
        std::cerr << "Error! Couldn't open file for writing: " << fileName << std::endl;
        return;
    }
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j)
            file << data[i][j] << " ";
        file << std::endl;
    }
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    for (size_t i = 0; i < matrix.rows; ++i) {
        for (size_t j = 0; j < matrix.cols; ++j)
            os << matrix.data[i][j] << " ";
        os << std::endl;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Matrix& matrix) {
    for (size_t i = 0; i < matrix.rows; ++i)
        for (size_t j = 0; j < matrix.cols; ++j)
            is >> matrix.data[i][j];
    return is;
}
