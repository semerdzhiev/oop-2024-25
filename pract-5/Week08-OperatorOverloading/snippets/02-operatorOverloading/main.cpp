#include <iostream>
#include "money.h"

int main()
{
    int a = 5, b = 6;

    if (a == b)
    {
        // ...
    }

    Money m1(2, 40), m2(2, 40), m3(3, 80);

    std::cout << std::boolalpha << (m1 == m2) << std::endl;
    std::cout << std::boolalpha << (m1 != m3) << std::endl;
    std::cout << std::boolalpha << (m1 < m3) << std::endl;

    Money m(0, 0);
    std::cin >> m;
    std::cout << m << std::endl;

    return 0;
}