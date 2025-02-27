#include "library.h"

// An iterative implementation of the factorial function
int factorial(int n)
{
    int result = 1;

    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    
    return result;
}

// An iterative implementation of the Fibonacci function
int fibonacci(int n)
{
    int current = 0;
    int next = 1;

    for(int i = 0; i < n; ++i) {
        int temp = current + next;
        current = next;
        next = temp;
    }

    return current;
}