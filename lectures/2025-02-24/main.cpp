#include "library.h"
#include <iostream>

int main()
{
    const int limit = 7;
    
    for(int i = 0; i <= limit; ++i)
        std::cout << "fibonacci(" << i << ") = " << fibonacci(i) << std::endl;

    std::cout << "--------" << std::endl;

    for(int i = 0; i <= limit; ++i)
        std::cout << i << "! = " << factorial(i) << std::endl;
}