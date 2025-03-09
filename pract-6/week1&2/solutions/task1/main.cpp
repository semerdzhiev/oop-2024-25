#include <iostream>
#include "Interval.hpp"

int main() {
    Interval t1(3, 10); 
    Interval t2(4, 14); 
    Interval t3; 

    t1.print(); 
    t2.print(); 

    Interval result = t1.intersect(t2); 
    result.print();

    std::cout << "Is t2 a superinterval of result? " << t2.isSuperInterval(result) << std::endl;

    std::cout << "Prime numbers in t1: " << t1.calcPrimeNumbersInTheInterval() << std::endl;
    std::cout << "Palindrome numbers in t1: " << t1.calcPalindromeNumbersInTheInterval() << std::endl;
    std::cout << "Unique digit numbers in t1: " << t1.calcUniqueDigitNumbersInTheInterval() << std::endl;

    std::cout << "Is t1 power of two interval? " << t1.isPowerOfTwoInterval() << std::endl;

    return 0;
}
