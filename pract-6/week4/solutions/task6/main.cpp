#include "Matrix.hpp"

int main() {
    Matrix A(2, 2);
    Matrix B(2, 2);

    std::cout << "Enter values for Matrix A (2x2):\n";
    std::cin >> A;

    std::cout << "Enter values for Matrix B (2x2):\n";
    std::cin >> B;

    Matrix sum = A + B;
    Matrix diff = A - B;
    Matrix prod = A * B;

    std::cout << "A + B:\n" << sum;
    std::cout << "A - B:\n" << diff;
    std::cout << "A * B:\n" << prod;

    A.writeToFile("matrixA.txt");
    B.writeToFile("matrixB.txt");

    Matrix C(2, 2);
    C.readFromFile("matrixA.txt");
    std::cout << "Matrix C (loaded from file):\n" << C;
}
