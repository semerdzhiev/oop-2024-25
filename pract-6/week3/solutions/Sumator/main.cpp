#include <iostream>
#include "Sumator.hpp"

int main() {
    Sumator sumator;

    sumator.add(4);
    sumator.add(2);
    std::cout << "Sum: " << sumator.getSum() << std::endl; // 3

    sumator.add(5);
    std::cout << "Sum: " << sumator.getSum() << std::endl; // 28

    sumator.removeLast();
    std::cout << "Sum: " << sumator.getSum() << std::endl; // 3

    sumator.changeAt(5, 1);
    std::cout << "Sum: " << sumator.getSum() << std::endl; // 6
}
